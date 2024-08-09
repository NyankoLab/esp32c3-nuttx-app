CC = /opt/homebrew/opt/llvm/bin/clang
CFLAGS = -c -Os --target=riscv32-esp-elf -march=rv32imc -mabi=ilp32
CINCLUDE = -Iinclude

LD = /opt/homebrew/opt/llvm/bin/ld.lld
LDFLAGS = --unresolved-symbols=ignore-all -r -T binfmt/libelf/gnu-elf.ld

SRCS = hello.c
OBJS = $(addprefix objs/,$(SRCS:.c=.o))
BINS = $(addprefix apps/,$(basename $(SRCS)))

all: apps objs $(BINS)

apps:
	mkdir apps

objs:
	mkdir objs

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(CINCLUDE) $< -o $@

$(BINS): $(OBJS)
	$(LD) $(LDFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f apps/*
	rm -f objs/*
