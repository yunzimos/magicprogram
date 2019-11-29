obj-m	:=magic_smog.o

KERNELDIR ?= /root/HOME/UP-Magic6410/kernel/linux-2.6.21_magic/
PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
.PHYON:modules
