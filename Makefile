
GCCPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = loader.o gdt.o port.o interruptstubs.o interrupts.o kernel.o

%.o: %.cpp
	gcc $(GCCPARAMS) -c -o $@ $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

mario.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

mario.iso: mario.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp mario.bin iso/boot/mario.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "MarioOS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/mario.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=mario.iso iso
	rm -rf iso

install: mario.bin
	sudo cp $< /boot/mario.bin

.PHONY: clean
clean:
	rm -f $(objects) mario.bin 
	# sweep sweep
