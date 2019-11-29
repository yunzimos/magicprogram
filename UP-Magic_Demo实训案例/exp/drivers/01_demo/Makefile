
#TOPDIR  := $(shell cd ..; pwd)
TOPDIR  := .


KERNELDIR = /arm2410cl/kernel/linux-2.4.18-2410cl
#KERNELDIR = /usr/src/linux

INCLUDEDIR = $(KERNELDIR)/include

CROSS_COMPILE = arm-linux-

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


TARGET = demo.o hello.o test_demo

all: $(TARGET)


demo.o: demo.c
	$(CC) -c $(CFLAGS) $^ -o $@

hello.o: hello.c
	$(CC) -c $(CFLAGS) $^ -o $@

test_demo: test_demo.o
	$(CC) $^ -o $@

install:
	install -d $(INSTALLDIR)
	install -c $(TARGET).o $(INSTALLDIR)

clean:
	rm -f *.o *~ core .depend test_demo
 
