bios.img: bios
	mmix-objcopy -O binary -j .text \
		--change-section-lma .text-0x8000ffffffc00000 \
		bios bios.img
	mmix-objdump -d bios > bios.dis

bios: start.o bios.o
	mmix-ld -o bios start.o bios.o -T bios.lds -e __start

start.o: start.S
	mmix-gcc -c start.S

bios.o: bios.c
	mmix-gcc -fno-builtin -mno-base-addresses -c bios.c

clean:
	-rm -f *.o 
	-rm -f bios bios.img bios.dis
