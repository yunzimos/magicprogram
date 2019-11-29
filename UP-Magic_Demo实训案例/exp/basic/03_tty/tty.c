#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>


int main()
{
    int fd,n;
	char buf[256];
    fd=open("/dev/ttyS1",O_NOCTTY|O_RDWR|O_NONBLOCK);
    if( fd < 0)
    {
        perror("Unable open /dev/ttyS0\r ");
		return 1;
    }
    n = write( fd, "hello\r", 6);
    if ( n < 0 )
		puts( "write() of 6 bytes failed!\r");
    puts( "write() of 6 bytes ok!\r");

    while(1)
    {
		read(fd,buf,256);
		puts(buf);
		if(strncmp(buf,"quit",4)==0)break;	
    }
return 0;
}

int set_port(int fd)
{
	struct termios opt;
	
	tcgetattr(fd,&opt);/*get current option setup*/
	show_option(&opt);

//	opt.c_cflags &= 
	tcsetattr(fd,&opt);/*get current option setup*/
	



}




