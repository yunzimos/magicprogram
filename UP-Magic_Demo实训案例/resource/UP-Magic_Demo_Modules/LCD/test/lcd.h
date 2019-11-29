#ifndef __LCD_H
#define __LCD_H

#define Gary_LCD_E1            0X00
#define Gary_LCD_E2            0X01
#define Gary_LCD_Page0         0X00
#define Gary_LCD_Page1         0X01
#define Gary_LCD_Page2         0X02
#define Gary_LCD_Page3         0X03

/*lcd registers*/
#define Display_ON        0xAF
#define Display_OFF 	  0xAE
#define Page_Base   	  0xB8
#define Column_Base 	  0x00

#define	Line_Base   	  0xC0
#define Read_modify_write 0xE0
#define End_Gray_LCD      0xEE
#define	Reset_Gray_LCD    0xE2

#define Static_drive_ON   0xA5
#define Static_drive_OFF  0xA4
#define Select_ADC_forward 0xA0
#define Select_ADC_reverse 0xA1


#define Select_DUTY_16	  0xA8
#define Select_DUTY_32    0xA9
#define Gray_LCD_Reset    0xE2
void Gray_LCD_Init(int fd);
void Gray_LCD_WriteReg_all(int fd,unsigned char Gray_LCD_RegValue);
void Gray_LCD_Signal_Column(int fd,unsigned short int Column,unsigned short int  Group,unsigned char Word_Value[]);
void Gray_LCD_Standard_Signal_Word(int fd,unsigned short int Column , unsigned short int Group , unsigned char Word_Value[]);
void Gray_LCD_WriteReg_E1(int fd,unsigned char Gray_LCD_RegValue);
void Gray_LCD_WriteReg_E2(int fd,unsigned char Gray_LCD_RegValue);
void Gray_LCD_WriteRam_E1(int fd,unsigned char Gray_LCD_RegValue);
void Gray_LCD_WriteRam_E2(int fd,unsigned char Gray_LCD_RegValue);
void Gray_LCD_Clear(int fd);
#endif
