SECTIONS
{
 . = 0x80000000007f0000;
 .data :
  {
 *(COMMON .data .bss)
  }
 . = 0x8000ffffffc00000;
 .text : 
 {
 *(.text)
 *(.rodata)
 }
}
