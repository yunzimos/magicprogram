#insmod magic_irda.ko
mknod /dev/irda c 232 0
./irda_test
