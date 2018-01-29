/*
 * Copyright 2018 Eiji Yoshiya
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#define	VRAM	0x800100000a000000
#define	SCR_WIDTH 80
#define	SCR_HEIGHT 60

int cx = 0;
int cy = 0;
char *vram = 0;

void scroll(void)
{
	int i, j;
	char *dst, *src;

	for (i = 0; i < SCR_HEIGHT - 1; i++) {

		dst = (char *)VRAM + (i << 7);
		src = dst + (1 << 7);

		for (j = 0; j < SCR_WIDTH; j++)
			*dst++ = *src++;
	}

	dst = (char *)VRAM + (i << 7);
	for (j = 0; j < SCR_WIDTH; j++)
		*dst++ = 0;
}

void putc(char c)
{
	switch (c) {
	default:
		*vram++ = c;
		if (++cx == SCR_WIDTH) {
			cx = 0;
			if (cy == SCR_HEIGHT - 1) {
				scroll();
			} else {
				cy++;
			}
			vram = (char *)VRAM + (cy << 7);
		}
		break;
	case '\r':
		vram -= cx;
		cx = 0;
		break;
	case '\n':
		if (cy == SCR_HEIGHT - 1) {
			scroll();
		} else {
			cy++;
			// vram += SCR_WIDTH;
			vram += (1 << 7);
		}
		break;
	case '\b':
		if (cx > 0) {
			cx--;
			vram--;
		}
		break;
	}
}

void puts(char *s)
{
	char c;

	while (c = *s++) {
		if (c == '\n')
			putc('\r');
		putc(c);
	}
}

int gets(char *buf, int size)
{
	int	i;

	size--;		// for null terminator.
	i = 0;
	for (;;) {
		int ch;

		ch = getch(); 
		switch (ch) {
		default:
			if (i < size) {
				putc(ch);
				buf[i++] = ch;
			}
			break;
		case '\n':
			putc('\r');
			putc('\n');
			buf[i] = 0;
			return i;
		case '\003':
			puts("^C\n");
			return -1;
		case '\b':
			putc('\b');
			putc(' ');
			putc('\b');
			i--;
			break;
		}
	}
}

///////////
static void print_hex_one(unsigned char val)
{

	val &= 0xf;
	if (val < 10)
		putc('0' + val);
	else
		putc('a' + val - 10);
}

static void print_hex(unsigned long long val, int size)
{
	switch (size) {
	case 8:
		print_hex_one(val >> 60);
		print_hex_one(val >> 56);
		print_hex_one(val >> 52);
		print_hex_one(val >> 48);
		print_hex_one(val >> 44);
		print_hex_one(val >> 40);
		print_hex_one(val >> 36);
		print_hex_one(val >> 32);
	case 4:
		print_hex_one(val >> 28);
		print_hex_one(val >> 24);
		print_hex_one(val >> 20);
		print_hex_one(val >> 16);
	case 2:
		print_hex_one(val >> 12);
		print_hex_one(val >> 8);
	case 1:
		print_hex_one(val >> 4);
		print_hex_one(val >> 0);
	}
}

void eval(char *s)
{
	char cmd;
	char size;
	long long addr;
	long long val;

	cmd = *s++;
	switch (cmd) {
	case 'r':
	case 'w':
		break;
	case 'b':
		boot();
		puts("No SD Card.\n");
		return;
	default:
		return;
	}

	size = *s++;
	switch (size) {
	case 'b':	// byte
	case 'w':	// wyde
	case 't':	// tetra
	case 'o':	// octa
		break;
	default:
		return;
	}

	while (*s == ' ')
		s++;

	addr = 0;
	for (;;) {
		char ch;

		ch = *s++;
		if (('0' <= ch) && (ch <= '9')) {
			addr <<= 4;
			addr += ch - '0';
		} else if (('a' <= ch) && (ch <= 'f')) {
			addr <<= 4;
			addr += ch - 'a' + 10;
		} else if (('A' <= ch) && (ch <= 'F')) {
			addr <<= 4;
			addr += ch - 'A' + 10;
		} else {
			break;
		}
	}

	if (cmd == 'r') {
		switch (size) {
		case 'b':
			print_hex(*(unsigned char *)addr, 1);
			break;
		case 'w':
			print_hex(*(unsigned short *)addr, 2);
			break;
		case 't':
			print_hex(*(unsigned int *)addr, 4);
			break;
		case 'o':
			print_hex(*(unsigned long long *)addr, 8);
			break;
		}
	} else if (cmd = 'w') {
		while (*s == ' ')
			s++;

		val = 0;
		for (;;) {
			char ch;

			ch = *s++;
			if (('0' <= ch) && (ch <= '9')) {
				val <<= 4;
				val += ch - '0';
			} else if (('a' <= ch) && (ch <= 'f')) {
				val <<= 4;
				val += ch - 'a' + 10;
			} else if (('A' <= ch) && (ch <= 'F')) {
				val <<= 4;
				val += ch - 'A' + 10;
			} else {
				break;
			}
		}

		switch (size) {
		case 'b':
			*(unsigned char *)addr = val;
			break;
		case 'w':
			*(unsigned short *)addr = val;
			break;
		case 't':
			*(unsigned int *)addr = val;
			break;
		case 'o':
			*(unsigned long long *)addr = val;
			break;
		}
	}
}

int main(void)
{
	extern void ps2_init(void);

	cx = 0;
	cy = 0;
	vram = (char *)VRAM;

	puts("MMIX BIOS for DE0, Version 0.0\n");

	ps2_init();

	// try boot();
	boot();

	for (;;) {
		char buf[256];
		int ret;

		puts("> ");
		ret = gets(buf, sizeof(buf));
		if (ret) {
			eval(buf);
			puts("\n");
		}
	}

	return 0;
}
