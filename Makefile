CC = ~/.espressif/tools/riscv32-esp-elf/esp-13.2.0_20240530/riscv32-esp-elf/bin/riscv32-esp-elf-gcc
#CC = /opt/homebrew/opt/llvm/bin/clang
CDEFINES = -DCONFIG_NSH_NETINIT
CDEFINES += -DCONFIG_EXAMPLES_MCUBOOT_UPDATE_AGENT_DL_BUFFER_SIZE=512
CDEFINES += -DCONFIG_EXAMPLES_MCUBOOT_UPDATE_AGENT_UPDATE_URL=\"\"
CDEFINES += -DCONFIG_MCUBOOT_PRIMARY_SLOT_PATH=\"/dev/ota0\"
CDEFINES += -DCONFIG_MCUBOOT_SECONDARY_SLOT_PATH=\"/dev/ota1\"
CDEFINES += -DCONFIG_MCUBOOT_SCRATCH_PATH=\"/dev/otascratch\"
CDEFINES += -DCONFIG_MCUBOOT_DEFAULT_FLASH_ERASE_STATE=0xff
CDEFINES += -DCONFIG_EXAMPLES_WGET_IPADDR
CDEFINES += -DCONFIG_EXAMPLES_WGET_DRIPADDR
CDEFINES += -DCONFIG_EXAMPLES_WGET_NETMASK
CDEFINES += -DCONFIG_EXAMPLES_WGET_URL=\"\"
CDEFINES += -DCONFIG_NET
CDEFINES += -DCONFIG_NET_TCP
CFLAGS = -Os -nostdlib -ffunction-sections -fdata-sections
#CFLAGS += --target=riscv32-esp-elf -march=rv32imc -mabi=ilp32 -fuse-ld=lld
CFLAGS += -Wl,-e,main,-r,-T,binfmt/libelf/gnu-elf.ld,--gc-sections
CINCLUDE = -I. -Iboot -Iinclude

SRCS = hello.c mcuboot_agent.c wget.c
BINS = $(addprefix apps/,$(basename $(SRCS)))

all: apps $(BINS)

apps:
	mkdir apps

apps/%: %.c
	$(CC) $(CDEFINES) $(CFLAGS) $(CINCLUDE) $< -o $@

apps/mcuboot_agent: boot/bootutil/bootutil_misc.c boot/bootutil/bootutil_public.c boot/flash_map_backend/flash_map_backend.c riscv/div.o mcuboot_agent.c
	$(CC) $(CDEFINES) $(CFLAGS) $(CINCLUDE) $^ -o $@ -Wl,-T,binfmt/libelf/esp32c3.rom.miniz.ld

riscv/div.o: riscv/div.S
	$(CC) $^ -o $@

clean:
	rm -f *.o
	rm -f apps/*.*
	rm -f riscv/div.o
