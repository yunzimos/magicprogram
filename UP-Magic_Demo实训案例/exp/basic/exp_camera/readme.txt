v4lcap_class_2410_270.tar.bz2  �������
jpeg-6b-mem.tar.bz2  ��Ҫ�Ŀ��ļ�
�ֱ��ѹ�����ļ�
�����ѹ���jpeg-6b
�޸����ɵ�Makefile�ļ�
 CC= gcc  �ó�  CC=/opt/host/armv4l/bin/armv4l-unknown-linux-gcc (�������Լ������������λ���޸�)
       # library (.a) file creation command
       AR= ar rc �ó�  AR= /opt/host/armv4l/bin/ar rc  (ͬ��)
       # second step in .a creation (use "touch" if not needed)
       AR2= ranlib �ó�  AR2= /opt/host/armv4l/bin/ranlib (ͬ��)

���п��ļ�����
[root@vm-dev jpeg-6b]# make clean
[root@vm-dev jpeg-6b]# make
[root@vm-dev jpeg-6b]# make install
��make install��ʱ�����
/usr/bin/install -c -m 644 jconfig.h /mnt/nfs/jpeg4arm/include/jconfig.h
/usr/bin/install: �޷�����һ���ļ� '/mnt/nfs/jpeg4arm/include/jconfig.h': û���Ǹ��ļ���Ŀ¼
make: *** [install-headers] ���� 1
�����ֶ�������Ŀ¼����make install
[root@vm-dev jpeg-6b]# mkdir /mnt/nfs/jpeg4arm
[root@vm-dev jpeg-6b]# mkdir /mnt/nfs/jpeg4arm/include

���������������Ŀ¼�޷������Կ����ֶ���������make install
/usr/bin/install: cannot create regular file '/mnt/nfs/jpeg4arm/bin/cjpeg': No such file or directory
make: *** [install] ����1
/usr/bin/install: �޷�����һ���ļ� '/mnt/nfs/jpeg4arm/man/man1/cjpeg.1': û���Ǹ��ļ���Ŀ¼
make: *** [install] ���� 1
�ڽ�ѹ��v4lcap_class_2410_270.tar.bz2�����v4lcap�ļ��У����������޸�Makefile�ļ�(���������ƣ�������������Ϊ���������������뼴�ɡ�

arm��ִ�г���
�ȼ�������  insmod videodev.o
            insmod spca5xx.o
���ִ��    ./v4lcap

�����е�nfs.tar.bz2Ϊ��װ�õĿ��ļ�������������⣬���Խ���ֱ�ӽ�ѹ��/mnt/����·��Ϊ��/mnt/nfs/nfs/jpeg4arm
����Դ�붼�Ѿ�����ã�����ֱ��ʹ�á�