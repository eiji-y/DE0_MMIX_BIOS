#define	PS2_BASE	0x0001000009000000
#define	EIO		1
#define	ETIMEDOUT	2

extern void putc(char);

static void print_hex_one(unsigned char val)
{

	val &= 0xf;
	if (val < 10)
		putc('0' + val);
	else
		putc('a' + val - 10);
}

static void print_hex(unsigned int val)
{
	print_hex_one(val >> 28);
	print_hex_one(val >> 24);
	print_hex_one(val >> 20);
	print_hex_one(val >> 16);
	print_hex_one(val >> 12);
	print_hex_one(val >> 8);
	print_hex_one(val >> 4);
	print_hex_one(val >> 0);
}

/*
"abcdefgh" 0x1C, 0x32, 0x21, 0x23, 0x24, 0x2B, 0x34, 0x33,
"ijklmnop" 0x43, 0x3B, 0x42, 0x4B, 0x3A, 0x31, 0x44, 0x4D,
"qrstuvwx" 0x15, 0x2D, 0x1B, 0x2C, 0x3C, 0x2A, 0x1D, 0x22,
"yz012345" 0x35, 0x1A, 0x45, 0x16, 0x1E, 0x26, 0x25, 0x2E,
"6789`-=\" 0x36, 0x3D, 0x3E, 0x46, 0x0E, 0x4E, 0x55, 0x5D,
            BS    SP   TAB   CAPS  LSHT  LCTR  LGUI  LALT
           0x66, 0x29, 0x0D, 0x58, 0x12, 0x14, 0x00, 0x11,
           RSHT  RCTL  RGUI  RALT  APPS  ENT   ESC    F1
           0x59, 0x00, 0x00, 0x00, 0x00, 0x5A, 0x76, 0x05,
            F2    F3    F4    F5    F6    F7    F8    F9
           0x06, 0x04, 0x0C, 0x03, 0x0B, 0x83, 0x0A, 0x01,
            F10   F11   F12  SCRL   [    INS   HOME  PU
           0x09, 0x78, 0x07, 0x7E, 0x54, 0x00, 0x00, 0x00,
           DEL   END   PD    UA    LA    DA     RA   NUM
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77,
           KP/   KP*   KP-   KP+   KPEN  KP.   KP0   KP1
           0x00, 0x7C, 0x7B, 0x79, 0x00, 0x71, 0x70, 0x69,
           KP2   KP3   KP4   KP5   KP6   KP7   KP8   KP9
           0x72, 0x7A, 0x6B, 0x73, 0x74, 0x6C, 0x75, 0x7D,
            ]     ;     '     ,      .    /
           0x5B, 0x4C, 0x52, 0x41, 0x49, 0x4A
 */

#define	Null	0x80
#define	SHFT	0x81
#define	CTRL	0x82
#define	KUP	0x83

const char normal_table[256] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x00
	0x00, 0x00, 0x00, 0x00, 0x00, '\t',  '`', 0x00,		// 0x08
	0x00, 0x00, SHFT, 0x00,  CTRL, 'q',  '1', 0x00,		// 0x10
	0x00, 0x00,  'z',  's',  'a',  'w',  '2', 0x00,		// 0x18
	0x00,  'c',  'x',  'd',  'e',  '4',  '3', 0x00,		// 0x20
	0x00,  ' ',  'v',  'f',  't',  'r',  '5', 0x00,		// 0x28
	0x00,  'n',  'b',  'h',  'g',  'y',  '6', 0x00,		// 0x30
	0x00, 0x00,  'm',  'j',  'u',  '7',  '8', 0x00,		// 0x38
	0x00,  ',',  'k',  'i',  'o',  '0',  '9', 0x00,		// 0x40
	0x00,  '.',  '/',  'l',  ';',  'p',  '-', 0x00,		// 0x48
	0x00, 0x00, '\'', 0x00,  '[',  '=', 0x00, 0x00,		// 0x50
	0x00, SHFT, '\n',  ']', 0x00, '\\', 0x00, 0x00,		// 0x58
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '\b', 0x00,		// 0x60
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x68
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00,		// 0x70
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x78
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x80
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x88
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x90
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x98
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xa0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xa8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xb0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xb8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xc0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xc8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xd0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xd8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xe0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xe8
	 KUP, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xf0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xf8
};

const char shift_table[256] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x00
	0x00, 0x00, 0x00, 0x00, 0x00, '\t',  '~', 0x00,		// 0x08
	0x00, 0x00, SHFT, 0x00,  CTRL, 'Q',  '!', 0x00,		// 0x10
	0x00, 0x00,  'Z',  'S',  'A',  'W',  '@', 0x00,		// 0x18
	0x00,  'C',  'X',  'D',  'E',  '$',  '#', 0x00,		// 0x20
	0x00,  ' ',  'V',  'F',  'T',  'R',  '%', 0x00,		// 0x28
	0x00,  'N',  'B',  'H',  'G',  'Y',  '^', 0x00,		// 0x30
	0x00, 0x00,  'M',  'J',  'U',  '&',  '*', 0x00,		// 0x38
	0x00,  '<',  'K',  'I',  'O',  ')',  '(', 0x00,		// 0x40
	0x00,  '>',  '?',  'L',  ':',  'P',  '_', 0x00,		// 0x48
	0x00, 0x00,  '"', 0x00,  '{',  '+', 0x00, 0x00,		// 0x50
	0x00, SHFT, '\n',  '}', 0x00,  '|', 0x00, 0x00,		// 0x58
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '\b', 0x00,		// 0x60
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x68
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00,		// 0x70
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x78
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x80
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x88
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x90
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x98
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xa0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xa8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xb0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xb8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xc0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xc8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xd0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xd8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xe0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xe8
	 KUP, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xf0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xf8
};

const char ctrl_table[256] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x00
	0x00, 0x00, 0x00, 0x00, 0x00, '\t',  '~', 0x00,		// 0x08
	0x00, 0x00, SHFT, 0x00, CTRL, 0x11,  '!', 0x00,		// 0x10
	0x00, 0x00, 0x1a, 0x13, 0x01, 0x17,  '@', 0x00,		// 0x18
	0x00, 0x03, 0x18, 0x04, 0x05,  '$',  '#', 0x00,		// 0x20
	0x00, Null, 0x16, 0x06, 0x14, 0x12,  '%', 0x00,		// 0x28
	0x00, 0x0e, 0x02, 0x08, 0x07, 0x19, 0x1f, 0x00,		// 0x30
	0x00, 0x00, 0x0d, 0x0a, 0x15,  '&',  '*', 0x00,		// 0x38
	0x00,  '<', 0x0b, 0x09, 0x0f,  ')',  '(', 0x00,		// 0x40
	0x00,  '>',  '?', 0x0c,  ':', 0x10,  '_', 0x00,		// 0x48
	0x00, 0x00,  '"', 0x00, 0x1b,  '+', 0x00, 0x00,		// 0x50
	0x00, SHFT, '\n', 0x1d, 0x00, 0x1c, 0x00, 0x00,		// 0x58
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '\b', 0x00,		// 0x60
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x68
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00,		// 0x70
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x78
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x80
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x88
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x90
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0x98
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xa0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xa8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xb0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xb8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xc0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xc8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xd0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xd8
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xe0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xe8
	 KUP, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xf0
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,		// 0xf8
};

static int get_scan_code()
{
	unsigned int scan_code;

	do {
		scan_code = *(int *)PS2_BASE;
	} while (!(scan_code & 0x00800000));

	return scan_code >> 24;
}

static int sht;
static int ctl;

int getch()
{
	unsigned int scan_code;
	unsigned int key_code;

	for (;;) {
		int kdown;

		scan_code = get_scan_code();

		kdown = 1;
		if (scan_code == 0xf0) {
			kdown = 0;
			scan_code = get_scan_code();
		}

		if (ctl) {
			key_code = ctrl_table[scan_code];
		} else if (sht) {
			key_code = shift_table[scan_code];
		} else {
			key_code = normal_table[scan_code];
		}

		if (key_code == CTRL) {
			if (kdown)
				ctl = 1;
			else
				ctl = 0;
		} else if (key_code == SHFT) {
			if (kdown)
				sht = 1;
			else
				sht = 0;
		} else if (kdown) {
			if (key_code == Null)
				return 0;
			if (key_code)
				return key_code;
		}
	}
}

void ps2_init()
{
	// reset
	*(char *)PS2_BASE = 0xff;

        sht = 0;
        ctl = 0;
}