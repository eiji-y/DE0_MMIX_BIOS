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
