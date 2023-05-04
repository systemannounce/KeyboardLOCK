#include <REGX51.H>
#include "AT24C02.h"
#include "keyboard.h"
#include "LCD1602.h"
#include <string.h>
#include "MatrixKey.h"
#include <intrins.h>
#include "Buzzer.h"
#include "IR.h"
#include "UART.h"


void Delay1(unsigned int s)
{
	while(s--)
	{
		unsigned char i, j;
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

unsigned char temp , command;
unsigned int key , current = 0 , correct = 0 , et = 1 , mode = 0 , open = 0 , ir = 0;
// unsigned char ;
unsigned int password , passwd[6] , number[6] = {2 , 3 , 5 , 7 , 11 , 13};
void main()
{
    unsigned int i;
    LCD_Init();
    IR_Init();
    UART_Init(0XFA);
    init_keyboard();
    current = 0;
    // AT24C02_WriteByte(0,41);
    // Delay1(100);
    password = AT24C02_ReadByte(0);
	while(1)
    {
        key = MatrixKey();
        command =0;
        command = IR_GetCommand();
        if(command == IR_START_STOP && ir != 99)ir = 99;
        if(command == IR_0 && ir != 10){key = 10;ir = 10;}
        if(command == IR_1 && ir != 1){key = 1;ir = 1;}
        if(command == IR_2 && ir != 2){key = 2;ir = 2;}
        if(command == IR_3 && ir != 3){key = 3;ir = 3;}
        if(command == IR_4 && ir != 4){key = 4;ir = 4;}
        if(command == IR_5 && ir != 5){key = 5;ir = 5;}
        if(command == IR_6 && ir != 6){key = 6;ir = 6;}
        if(command == IR_7 && ir != 7){key = 7;ir = 7;}
        if(command == IR_8 && ir != 8){key = 8;ir = 8;}
        if(command == IR_9 && ir != 9){key = 9;ir = 9;}
        if(command == IR_RPT && ir != 11){key = 11;ir = 11;}
        if(command == IR_USD && ir != 15){key = 12;ir = 12;}
        if(command == IR_PREVIOUS && ir != 14){key = 14;ir = 14;}
        if(command == IR_MUTE && ir != 24){key = 24;ir = 24;}
        if(command == IR_EQ && ir != 34){key = 34;ir = 34;}
        if(command == IR_POWER && ir != 44){key = 44;ir = 44;}

        if(key > 0 && key < 11 && current < 6)
        {
            passwd[current] = key;
            current++;
        }
        if(key>13 && key<50)
        {
            if(key == 14){current=current-1;if(current > 6)current = 0;passwd[current] = 0;open = 0;}
            if(key == 24){memset(passwd, 0, sizeof(passwd));current = 0;open = 0;}
            if(key == 34){if(open == 1){memset(passwd, 0, sizeof(passwd));current = 0;mode = !mode;}}
            if(key == 44)
            {
                if(mode == 0 && current == 6)
                {
                    correct = 0;
                    open = 0;
                    temp = 0;
                    for(i=0;i<6;i++)
                    {
                        temp = temp + passwd[i]*number[i];
                    }
                    if(temp == password)open = 1;
                    if(temp != password)open = 2;
                    if(open == 1)
                    {
                        //right
                        open = 1;
                        Buzzer_Time(200);
                    }
                    if(open == 2)
                    {
                        //wrong
                        open = 2;
                        Buzzer_Time(500);
                    }
                }
                if(mode == 1 && current == 6)
                {
                    password = 0;
                    open = 0;
                    mode = 0;
                    for(i=0;i<6;i++)
                    {
                        password = password + passwd[i]*number[i];
                    }
                    memset(passwd, 0, sizeof(passwd));
                    current = 0;
                    AT24C02_WriteByte(0,password);
                    LCD_ShowString(2,8,"pwHASchan");
                }
            }
        }
        //interface
        if(open == 0)LCD_ShowString(1,1,"PASSWORD:");
        if(open == 1)LCD_ShowString(1,1,"SUCCESS  ");
        if(open == 2)LCD_ShowString(1,1,"WRONG PW ");

        if(mode == 1)LCD_ShowString(1,12,"RESET");
        if(mode == 0)LCD_ShowString(1,12,"ENTER");
        
        if(current == 0)LCD_ShowString(2,1,"      ");
        else if(current == 1)LCD_ShowString(2,1,"*     ");
        else if(current == 2)LCD_ShowString(2,1,"**    ");
        else if(current == 3)LCD_ShowString(2,1,"***   ");
        else if(current == 4)LCD_ShowString(2,1,"****  ");
        else if(current == 5)LCD_ShowString(2,1,"***** ");
        else if(current == 6)LCD_ShowString(2,1,"******");

        if(P3_0 == 0)
        {
            UART_SendByte(0x99);
        }
    }
}