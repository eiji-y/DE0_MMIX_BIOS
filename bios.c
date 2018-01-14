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

#define	VRAM	0x8001000002000000;
#define	SCR_WIDTH 80
#define	SCR_HEIGHT 40

int cx = 0;
int cy = 0;
char *vram = 0;

void scroll(void)
{
	char *dst = (char *)VRAM
	char *src = dst + SCR_WIDTH;
	int i;

	for (i = 0; i < SCR_WIDTH * (SCR_HEIGHT - 1); i++)
		*dst++ = *src++;
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
				vram -= SCR_WIDTH;
			} else {
				cy++;
			}
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
			vram += SCR_WIDTH;
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

int main(void)
{
	cx = 0;
	cy = 0;
	vram = (char *)VRAM;

	puts("MMIX BIOS for DE0, Version 0.0\n");

	return 0;
}
