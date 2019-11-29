#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void Gray_LCD_Init(int fd)
{
	unsigned char reset_E1E2_buf[2]={0xfc,0xff};//set E1 E2
	write(fd,reset_E1E2_buf,2);
	//usleep(5);
	Gray_LCD_WriteReg_all(fd,Display_OFF);
	Gray_LCD_WriteReg_all(fd,Static_drive_OFF);
	Gray_LCD_WriteReg_all(fd,Select_DUTY_32);
	Gray_LCD_WriteReg_all(fd,Select_ADC_forward);
	Gray_LCD_WriteReg_all(fd,Display_OFF);
	Gray_LCD_WriteReg_all(fd,Gray_LCD_Reset);
	Gray_LCD_WriteReg_all(fd,Display_ON);
	Gray_LCD_WriteReg_all(fd,Line_Base);
}

void Gray_LCD_WriteReg_all(int fd,unsigned char Gray_LCD_RegValue)
{
	int i;
	unsigned char RegValue;
	unsigned short int Value;
	RegValue=Gray_LCD_RegValue;
	unsigned char reset_RWDI_buf[2]={0xf0,RegValue};
	write(fd,reset_RWDI_buf,2);
	unsigned char set_E1E2_buf[2]={0xf3,RegValue};
	write(fd,set_E1E2_buf,2);
	
	Value=((RegValue<<8)|0xf3);
	write(fd,&Value,2);
	//usleep(10);

	Value=((RegValue<<8)|0xf0);
	write(fd,&Value,2);

	//usleep(5);
}

void Gray_LCD_WriteReg_E2(int fd,unsigned char Gray_LCD_RegValue)
{
  int i;
  unsigned char RegValue;
  unsigned short int Value;
  RegValue=Gray_LCD_RegValue;

  Value=(RegValue<<8)|0xf0;
  write(fd,&Value,2);
 // usleep(5);
  
  Value=(RegValue<<8)|0xf0;
  write(fd,&Value,2);
//usleep(5);
  
    Value=(RegValue<<8)|0x12;
   write(fd,&Value,2);
//usleep(5);

  Value=((RegValue<<8)|0x12);
	write(fd,&Value,2);
  //usleep(5);

    Value=(RegValue<<8)|0x10;
  write(fd,&Value,2);
 // usleep(5);
}

void Gray_LCD_WriteRAM_E2(int fd,unsigned char Gray_LCD_RAMValue)
{
  int i;
  unsigned short int Value;
  unsigned char RegValue;
  RegValue=Gray_LCD_RAMValue;

  Value=(RegValue<<8)|0xf8;
  write(fd,&Value,2);
//usleep(5);

  Value=(RegValue<<8)|0xfa;
  write(fd,&Value,2);
//usleep(5);

  Value=((RegValue<<8)|0xfa); 
  write(fd,&Value,2);
//usleep(5);
  for(i=0;i<=15;i++);

   Value=(RegValue<<8)|0xf8;
  write(fd,&Value,2);
//usleep(5);
  for(i=0;i<=5;i++);
}

void Gray_LCD_WriteRAM_E1(int fd,unsigned char Gray_LCD_RAMValue)
{
  int i;
  unsigned short int Value;
  unsigned char RegValue;
  RegValue=Gray_LCD_RAMValue; 
  Value=(RegValue<<8)|0xf8;
  write(fd,&Value,2);

  //usleep(5);
   Value=(RegValue<<8)|0xf9;
  write(fd,&Value,2);
//usleep(5);
 
  Value=((RegValue<<8)|0xf9); 
  write(fd,&Value,2);
//usleep(5);
  for(i=0;i<=15;i++);
  Value=(RegValue<<8)|0xf8;
  write(fd,&Value,2);
  for(i=0;i<=15;i++);
//usleep(5);
}

void Gray_LCD_Signal_Column(int fd,unsigned short int Column,unsigned short int  Group,unsigned char Word_Value[])
{
	unsigned short int NUM_Column,Gary_LCD_Part,Store_Column,j,k;
        j=0;
	NUM_Column=Column-1;
        if(NUM_Column>60)
        {
           NUM_Column=NUM_Column-61;
           Gary_LCD_Part=Gary_LCD_E2;
        }else
        {
            Gary_LCD_Part=Gary_LCD_E1;
        }
        Store_Column=NUM_Column;
  
      for(k=0;k<2;k++)
      {
         NUM_Column=Store_Column;
         Gray_LCD_WriteReg_all(fd,Page_Base+Group+k);
         Gray_LCD_WriteReg_all(fd,Column_Base+NUM_Column);
        if(Gary_LCD_Part==Gary_LCD_E1)
        {         
           Gray_LCD_WriteRAM_E1(fd,Word_Value[j]);
         }
       else
        {    
           Gray_LCD_WriteRAM_E2(fd,Word_Value[j]);

         }
          j=j+16;
       }
}

void Gray_LCD_Standard_Signal_Word(int fd,unsigned short int Column , unsigned short int Group , unsigned char Word_Value[])
{
  unsigned short int NUM_Column , Gary_LCD_Part , Store_Column , i , j , k;
  j=0;
  Gary_LCD_Part=Gary_LCD_E1;
  NUM_Column=Column;
  if(NUM_Column>60)
  {
    NUM_Column=NUM_Column-61;
    Gary_LCD_Part=Gary_LCD_E2;
  }
  Store_Column=NUM_Column;
  
  for(k=0;k<2;k++)
  {
    NUM_Column=Store_Column;
    Gray_LCD_WriteReg_all(fd,Page_Base+Group+k);
    Gray_LCD_WriteReg_all(fd,Column_Base+NUM_Column);
    if(Gary_LCD_Part==Gary_LCD_E1)
    {
      for(i=0;i<16;i++)
      {     
        if(NUM_Column>60) 
        {
          Gray_LCD_WriteReg_E2(fd,Column_Base+NUM_Column-61);
          Gray_LCD_WriteRAM_E2(fd,Word_Value[j]); 
        }
        else
        {
          Gray_LCD_WriteRAM_E1(fd,Word_Value[j]);
        }
        NUM_Column++;
        j++;
      }
    }
    else
    {
      for(i=0;i<16;i++)
      {
        Gray_LCD_WriteRAM_E2(fd,Word_Value[j]);
       j++;
      }
    }
  }
}

void Gray_LCD_Clear(int fd)
{
  int i;
  Gray_LCD_WriteReg_all(fd,Page_Base+Gary_LCD_Page0);
  Gray_LCD_WriteReg_all(fd,Column_Base+0x00);
  Gray_LCD_WriteReg_all(fd,Read_modify_write);
  for(i=0;i<61;i++)
    {
      Gray_LCD_WriteRAM_E1(fd,0x00);
      Gray_LCD_WriteRAM_E2(fd,0x00);
    }
  Gray_LCD_WriteReg_all(fd,End_Gray_LCD);
  
  Gray_LCD_WriteReg_all(fd,Page_Base+Gary_LCD_Page1);
  Gray_LCD_WriteReg_all(fd,Column_Base+0x00);
  Gray_LCD_WriteReg_all(fd,Read_modify_write);
  for(i=0;i<61;i++)
    {
      Gray_LCD_WriteRAM_E1(fd,0x00);
      Gray_LCD_WriteRAM_E2(fd,0x00);
    }
  Gray_LCD_WriteReg_all(fd,End_Gray_LCD);
  
  Gray_LCD_WriteReg_all(fd,Page_Base+Gary_LCD_Page2);
  Gray_LCD_WriteReg_all(fd,Column_Base+0x00);
  Gray_LCD_WriteReg_all(fd,Read_modify_write);
  for(i=0;i<61;i++)
    {
      Gray_LCD_WriteRAM_E1(fd,0x00);
      Gray_LCD_WriteRAM_E2(fd,0x00);
    }
  Gray_LCD_WriteReg_all(fd,End_Gray_LCD);
  
  Gray_LCD_WriteReg_all(fd,Page_Base+Gary_LCD_Page3);
  Gray_LCD_WriteReg_all(fd,Column_Base+0x00);
  Gray_LCD_WriteReg_all(fd,Read_modify_write);
  for(i=0;i<61;i++)
    {
      Gray_LCD_WriteRAM_E1(fd,0x00);
      Gray_LCD_WriteRAM_E2(fd,0x00);
    }
  Gray_LCD_WriteReg_all(fd,End_Gray_LCD);
}
