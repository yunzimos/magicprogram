v4lcap_class_2410_270.tar.bz2  程序代码
jpeg-6b-mem.tar.bz2  需要的库文件
分别解压两个文件
进入解压后的jpeg-6b
修改生成的Makefile文件
 CC= gcc  该成  CC=/opt/host/armv4l/bin/armv4l-unknown-linux-gcc (根据你自己交叉编译器的位置修改)
       # library (.a) file creation command
       AR= ar rc 该成  AR= /opt/host/armv4l/bin/ar rc  (同上)
       # second step in .a creation (use "touch" if not needed)
       AR2= ranlib 该成  AR2= /opt/host/armv4l/bin/ranlib (同上)

进行库文件编译
[root@vm-dev jpeg-6b]# make clean
[root@vm-dev jpeg-6b]# make
[root@vm-dev jpeg-6b]# make install
在make install的时候出现
/usr/bin/install -c -m 644 jconfig.h /mnt/nfs/jpeg4arm/include/jconfig.h
/usr/bin/install: 无法创建一般文件 '/mnt/nfs/jpeg4arm/include/jconfig.h': 没有那个文件或目录
make: *** [install-headers] 错误 1
可以手动建立该目录，再make install
[root@vm-dev jpeg-6b]# mkdir /mnt/nfs/jpeg4arm
[root@vm-dev jpeg-6b]# mkdir /mnt/nfs/jpeg4arm/include

后续过程如果仍有目录无法创建仍可以手动创建后再make install
/usr/bin/install: cannot create regular file '/mnt/nfs/jpeg4arm/bin/cjpeg': No such file or directory
make: *** [install] 错误1
/usr/bin/install: 无法创建一般文件 '/mnt/nfs/jpeg4arm/man/man1/cjpeg.1': 没有那个文件或目录
make: *** [install] 错误 1
在解压的v4lcap_class_2410_270.tar.bz2后会有v4lcap文件夹，进入里面修改Makefile文件(编译器名称），将编译器改为环境编译器，编译即可。

arm下执行程序
先加载驱动  insmod videodev.o
            insmod spca5xx.o
最后执行    ./v4lcap

光盘中的nfs.tar.bz2为安装好的库文件，如果不想编译库，可以将其直接解压到/mnt/生成路径为：/mnt/nfs/nfs/jpeg4arm
所有源码都已经编译好，可以直接使用。