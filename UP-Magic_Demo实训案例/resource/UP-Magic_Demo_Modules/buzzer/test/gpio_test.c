#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define IOCTL_LED_ON    0
#define IOCTL_LED_OFF   1
#define IOCTL_BUZZER_OFF  3
#define IOCTL_BUZZER_ON   4

int main(void)
{
    unsigned int led;
    unsigned int puzzer;
    int fd = -1;
        
    fd = open("/dev/gpio", 0);  
    if (fd < 0) {
        printf("Can't open /dev/gpio\n");
        return -1;
    }
    
    while(1)
    {
	ioctl(fd,IOCTL_LED_ON);
	sleep(1);
	ioctl(fd,IOCTL_LED_OFF);
	ioctl(fd,IOCTL_BUZZER_OFF);
	sleep(1);
	ioctl(fd,IOCTL_BUZZER_ON);
    }
       ioctl(fd,IOCTL_BUZZER_OFF);
    close(fd);
    return 0;
}

