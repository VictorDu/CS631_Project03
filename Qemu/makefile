kernel.img : myos.elf
	arm-none-eabi-objcopy myos.elf -O binary kernel.img

myos.elf : kernel.o
	arm-none-eabi-gcc -T linker.ld -o myos.elf -ffreestanding -O2 -nostdlib boot.o kernel.o get32.o

kernel.o : kernel.c
	arm-none-eabi-gcc -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -c kernel.c -o kernel.o -O2 -Wall -Wextra > temp.txt

clean :
	rm kernel.o 
