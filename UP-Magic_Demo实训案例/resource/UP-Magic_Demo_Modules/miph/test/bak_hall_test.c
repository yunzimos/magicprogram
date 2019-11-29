#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
    int i;
    int ret;
    int fd;
    int press_cnt[2];
    
    fd = open("/dev/hall", 0);  
    if (fd < 0) {
        printf("Can't open /dev/hall\n");
        return -1;
    }

    while (1) {
        ret = read(fd, press_cnt, sizeof(press_cnt));
        if (ret < 0) {
            printf("read err!\n");
            continue;
        } 

        if (press_cnt[0])
        	printf("reed has closed %d times!\n", press_cnt[0]);
	else	printf("reed has open.");
	if (press_cnt[1])
                printf("hall has %d times!\n", press_cnt[1]);
	else	printf("hall is normal.");
    }
    
    close(fd);
    return 0;    
}

