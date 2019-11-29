#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    int smog_cnt;
    char normal_buf[] = {"smog=normal"};
    char fire_buf[] = {"smog=firing"};    

    fd = open("/dev/smog", 0);  
    if (fd < 0) {
        printf("Can't open /dev/smog\n");
        return -1;
    }

    while (1) {
        int file_fd = open("/mnt/yaffs/smog/smog.txt", O_WRONLY|/*O_APPEND*/O_CREAT|O_TRUNC);
        fcntl(file_fd, F_SETLKW, file_lock(F_WRLCK, SEEK_SET));
 
        write(file_fd, normal_buf, strlen(normal_buf));
        printf("write smog normal.\n");


        ret = read(fd,&smog_cnt, sizeof(smog_cnt));
        if (ret < 0) {
            printf("read err!\n");
            continue;
        } 
        if (smog_cnt){
            printf("fire!\n");
	    lseek(file_fd, 0, SEEK_SET);
            write(file_fd, fire_buf, strlen(fire_buf));
	}
	fcntl(file_fd, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
        sleep(1);
    }
    close(fd);
    return 0;
}

