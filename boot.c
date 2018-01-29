#define	SD_BASE	0x800100000b000000

unsigned int swap4(unsigned int val)
{
	unsigned int ret;

	ret = (val & 0xff) << 24;
	ret |= (val & 0xff00) << 8;
	ret |= (val >> 8) & 0xff00;
	ret |= (val >> 24) & 0xff;
	return ret;
}

void read_block(unsigned int block)
{
	unsigned short asr;

	*(unsigned int *)(SD_BASE + 0x22c) = swap4(block << 9);
	*(unsigned short *)(SD_BASE + 0x230) = 0x1100;
	do {
		asr = *(unsigned short *)(SD_BASE + 0x234);
	} while (asr & 0x0400);
}

void boot()
{
	unsigned int start;
	unsigned int count;
	unsigned short asr;
	unsigned long long *dst;

	asr = *(unsigned short *)(SD_BASE + 0x234);
	if ((asr & 0x0200) == 0)
		return;

	read_block(0);

	start = *(unsigned int *)(SD_BASE + 0);
	count = *(unsigned int *)(SD_BASE + 4);

	dst = (unsigned long long *)0x8000000000000000;
	while (count--) {
		unsigned long long *src;
		int i;

		read_block(start++);

		src = (unsigned long long *)SD_BASE;	
		for (i = 0; i < 512/sizeof(long long); i++)
			*dst++ = *src++;
	}

	((void (*)())0x8000000000000000)();
}
