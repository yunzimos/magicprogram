#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int ret;
    int fd;
    int irda_cnt;
    
    fd = open("/dev/irda", 0);  
    if (fd < 0) {
        printf("Can't open /dev/irda\n");
        return -1;
    }

    while (1) {
        ret = read(fd,&irda_cnt, sizeof(irda_cnt));
        if (ret < 0) {
            printf("read err!\n");
            continue;
        } 
        if (irda_cnt)
            printf("have people!\n");
    }
    close(fd);
    return 0;
}

