CCPREFIX=../cross/bin/
ASM=../cross/bin/i686-elf-as
CXX:=../cross/bin/i686-elf-g++
CC:=i686-elf-gcc
ASL=iasl
BUILD := build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
INCLUDE:= -Iinclude
CXXFLAGS= --std=c++17 -ffreestanding -O3 -Wall -Wextra -fno-exceptions -fno-rtti -fshort-enums -Wno-attributes -w
SRC:=                      \
	$(wildcard src/*.s)\
	$(wildcard src/*.cpp)\
	$(wildcard src/buffers/*)\
	$(wildcard src/libk/*)\
	$(wildcard src/memory/*)\
	$(wildcard src/termutils/*)\
	$(wildcard src/asm_shims/*)\
	$(wildcard src/tests/*)\
	$(wildcard src/drivers/*)\
	$(wildcard src/disk_structure/*)\
	$(wildcard src/acpi/*)\
	$(wildcard src/smp/*)\
	$(wildcard src/interrupts/*)\

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.cpp.o)
OBJECTS := $(OBJECTS:%.s=$(OBJ_DIR)/%.s.o)


all: test

dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(APP_DIR)

boot: dir
	$(ASM) src/boot.s -o $(OBJ_DIR)/_boot.o

$(OBJ_DIR)/%.cpp.o: %.cpp dir
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJ_DIR)/%.s.o: %.s dir
	@mkdir -p $(@D)
	$(ASM) -o $@ -c $<

kernel: $(OBJECTS) boot
	@mkdir -p $(@D)
	$(CXX) -T linker.ld -nostdlib $(CXXFLAGS) $(INCLUDE) -o $(APP_DIR)/kernel.bin $(OBJECTS) -lgcc

clean:
	rm build -rf

image: kernel
	grub2-file --is-x86-multiboot $(APP_DIR)/kernel.bin
	mkdir -p $(APP_DIR)/isodir/boot/grub
	cp $(APP_DIR)/kernel.bin $(APP_DIR)/isodir/boot/kernel.bin
	cp grub.cfg $(APP_DIR)/isodir/boot/grub/grub.cfg
	grub2-mkrescue -o $(APP_DIR)/clinl.iso $(APP_DIR)/isodir

test: image
	qemu-system-x86_64 -hda $(APP_DIR)/clinl.iso

debug_run:
	qemu-system-i386 --cpu host -S -s -d guest_errors -cdrom $(APP_DIR)/clinl.iso &> $(BUILD)/klog &
	sleep 3
	gdb -w --eval-command="target remote localhost:1234" $(APP_DIR)/kernel.bin


