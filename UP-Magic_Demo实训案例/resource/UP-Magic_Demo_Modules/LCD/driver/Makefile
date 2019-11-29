obj-m	:=magic_leds.o

KERNELDIR := /root/HOME/UP-Magic6410/kernel/linux-2.6.21_magic/
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod.* *.symvers
.PHONY: all clean
