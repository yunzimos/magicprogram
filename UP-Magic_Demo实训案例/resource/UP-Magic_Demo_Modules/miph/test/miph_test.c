#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <fcntl.h>

struct flock* file_lock(short type, short whence)
{
    static struct flock ret;
    ret.l_type = type ;
    ret.l_start = 0;
    ret.l_whence = whence;
    ret.l_len = 0;
    ret.l_pid = getpid();
    return &ret;
}


int main(int argc, char **argv)
{
    int i;
    int ret;
    int fd;
    int press_cnt[2];
    char normal_buf[] = {"miph=normal"};
    char noise_buf[] = {"miph=noised"};

    fd = open("/dev/miph", 0);  
    if (fd < 0) {
        printf("Can't open /dev/miph\n");
        return -1;
    }

    while (1) {

	int file_fd = open("/root/miph/miph.txt", O_WRONLY|/*O_APPEND*/O_CREAT|O_TRUNC);
	fcntl(file_fd, F_SETLKW, file_lock(F_WRLCK, SEEK_SET));

	write(file_fd, normal_buf, strlen(normal_buf));
	//printf("write miph normal.\n");
        ret = read(fd, press_cnt, sizeof(press_cnt));
        if (ret < 0) {
            printf("read err!\n");
            continue;
        } 
	printf("---------cnt=%d-----------\n",press_cnt[0]);
        if (!press_cnt[0]){
        	printf("noise.\n");
		lseek(file_fd, 0, SEEK_SET);
		write(file_fd, noise_buf, strlen(noise_buf));
	}
	else	printf("no noise.");
/*
	if (press_cnt[1])
                printf("hall has %d times!\n", press_cnt[1]);
	else	printf("hall is normal.");
*/

	fcntl(file_fd, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
        sleep(1);



    }
    
    close(fd);
    return 0;    
}

