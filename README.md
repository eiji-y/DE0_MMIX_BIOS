# DE0_MMIX_BIOS
BIOS for DE0 MMIX

Boot from SD-Card.

Usage:
* Write bios.img to FLASH using DE0_ControlPanel.exe.
* Write 0xf0f1 to FLASH address 0x1ffffe.
* Write 0x0100 to FLASH address 0x1fffff.
* Start [DE0_MMIX.sof](http://github.com/eiji-y/DE0_MMIX). 

Compiler(patch for gcc 4.3.1) is available [here](http://www007.upp.so-net.ne.jp/eiji-y/vmmmix/vmmmix.html).
