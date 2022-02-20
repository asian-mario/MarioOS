GCCARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fpermissive
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = loader.o gdt.o port.o interruptstubs.o interrupts.o kernel.o

%.o: %.cpp
		gcc $(GCCARAMS) -c -o $@ -c $<

%.o: %.s
		as $(ASPARAMS) -o $@ $<


kernel.bin: linker.ld $(objects)
		ld $(LDPARAMS) -T $< -o $@ $(objects)

install: kernel.bin 
		sudo cp $< /boot/kernel.bin


mario.iso: kernel.bin
		mkdir iso
		mkdir iso/boot
		mkdir iso/boot/grub
		cp $< iso/boot/
		echo 'set timeout=0' >> iso/boot/grub/grub.cfg
		echo 'set default=0' >> iso/boot/grub/grub.cfg
		echo '' >> iso/boot/grub/grub.cfg
		echo 'menuentry "MarioOS" {' >> iso/boot/grub/grub.cfg
		echo '	multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
		echo '	boot' >> iso/boot/grub/grub.cfg
		echo '}' >> iso/boot/grub/grub.cfg
		echo '' >> iso/boot/grub/grub.cfg
		grub-mkrescue --output=$@ iso
		rm -rf iso 

.PHONY: clean
clean:
		rm -f $(objects) kernel.bin  
		# sweep sweep

	