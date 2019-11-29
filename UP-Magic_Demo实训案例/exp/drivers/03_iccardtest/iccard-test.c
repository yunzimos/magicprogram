#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int MAX_LEN=96;			/* �����д���ֽ��� */
int main()
{  int fd,i;			/* fdΪ��Ҫ�õ����ļ������� */
   char buf[MAX_LEN],readic[MAX_LEN];
   for(i=0;i<MAX_LEN;i++){	/* �����鸳ֵ */
     buf[i]=i+32;
   }
   
   if((fd=open("/dev/mcu/iccard24c16",O_RDWR))==-1){ /* ��IC���豸,�������*/
     fprintf(stderr,"Open error %d\n",errno);        /* ��ӡerrno������ֵ */
     exit(1);
   }
 
   printf("Write %d bytes data to /dev/mcu/iccard24c16 \n",MAX_LEN);
   if(write(fd,buf,MAX_LEN)==-1){                    /* ������д��IC�� */
     fprintf(stderr,"Write error %d\n",errno);
     exit(1);
   }
    
   if((lseek(fd,0,SEEK_SET))==-1){           /* ���ļ���дָ�붨λ����ʼλ�� */
     fprintf(stderr,"Lseek error %d\n",errno);
     exit(1);
   }
   
   printf("\nRead %d bytes data from /dev/mcu/iccard24c16 \n",MAX_LEN);
   if(read(fd,readic,MAX_LEN)==-1){       /* ��IC��,�������ݴ���readic[]���� */
     fprintf(stderr,"Read error %d\n",errno);
     exit(1);
   }
   
   if(close(fd)==-1){		/* �ر�IC���豸 */
     fprintf(stderr,"Close error%d\n",errno);
     exit(1);
   }
   
   for(i=0;i<MAX_LEN;i++){	/* �����ʾ���������� */
     if((i%8)==0)
       printf("\n");
     printf("%4c",readic[i]);
   }
   printf("\n");
   
   return 0;			/* �ɹ�����,������� */
}
