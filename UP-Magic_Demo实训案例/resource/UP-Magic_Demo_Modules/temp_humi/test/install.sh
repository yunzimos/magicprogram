#insmod /root/sht11/magic_sht11_driver.ko
mknod /dev/sht11 c 238 0
./sht11_test
