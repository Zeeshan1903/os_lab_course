run:
	riscv64-unknown-elf-gcc -O -I. -nostdlib -mcmodel=medany -o kernel.o -c kernel.c
	riscv64-unknown-elf-gcc -O -I. -nostdlib -mcmodel=medany -o entry.o -c entry.S

	riscv64-unknown-elf-ld -T linker.ld -o kernel.elf kernel.o entry.o 

	riscv64-unknown-elf-objcopy -O binary kernel.elf kernel.bin  

	qemu-system-riscv64 -machine virt -bios none -kernel kernel.bin -nographic

clean:
	rm -rf kernel.o entry.o kernel.elf kernel.bin 