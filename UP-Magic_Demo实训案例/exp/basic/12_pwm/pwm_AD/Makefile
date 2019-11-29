
#TOPDIR  := $(shell cd ..; pwd)
TOPDIR  := .


KERNELDIR =/arm2410cl/kernel-2410classic
#KERNELDIR =/usr/src/kernels/2.6.9-22.EL-x86_64
#KERNELDIR = /opt/host/armv4l/src/linux
#KERNELDIR = /data/arm2410/kernel
INCLUDEDIR = $(KERNELDIR)/include

CROSS_COMPILE=/home/qianzg/buildtools/armv4l/host/armv4l/bin/armv4l-unknown-linux-

AS      =$(CROSS_COMPILE)as
LD      =$(CROSS_COMPILE)ld
CC      =$(CROSS_COMPILE)gcc
CPP     =$(CC) -E
AR      =$(CROSS_COMPILE)ar
NM      =$(CROSS_COMPILE)nm
STRIP   =$(CROSS_COMPILE)strip
OBJCOPY =$(CROSS_COMPILE)objcopy
OBJDUMP =$(CROSS_COMPILE)objdump



CFLAGS += -I..
CFLAGS += -Wall -O -D__KERNEL__ -DMODULE -I$(INCLUDEDIR)


TARGET = pwm_ad.o    
# tube_test

all: $(TARGET)


pwm_ad.o: pwm_ad.c
	$(CC) -c $(CFLAGS) $^ -o $@

#tube_test: tube_test.o
#	$(CC) $^ -o $@

install:
	install -d $(INSTALLDIR)
	install -c $(TARGET).o $(INSTALLDIR)

clean:
	rm -f *.o    *~ core .depend
