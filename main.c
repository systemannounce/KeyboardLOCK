#include <REGX51.H>
#include "AT24C02.h"
#include "keyboard.h"
#include "LCD1602.h"
#include <string.h>

unsigned char temp;
unsigned int key , current , correct , et = 1 , mode = 0 , open = 0;
// unsigned char ;
unsigned int password[5] , passwd[5];
void main()
{
    unsigned int i;
    init_keyboard();
    current = 0;
    for(i = 0 ; i < 6 ; i++)
    {
        password[i] = AT24C02_ReadByte(i);
    }
	while(1)
    {
        temp = scan_keyboard();//不确定是不是要加delay
        if(temp == "1")key = 1;
        if(temp == "2")key = 2;
        if(temp == "3")key = 3;
        if(temp == "4")key = 4;
        if(temp == "5")key = 5;
        if(temp == "6")key = 6;
        if(temp == "7")key = 7;
        if(temp == "8")key = 8;
        if(temp == "9")key = 9;
        if(temp == "0")key = 0;
        if(temp == "*")key = 11;
        if(temp == "#")key = 12;
        if(temp == "A")key = 14;
        if(temp == "B")key = 24;
        if(temp == "C")key = 34;
        if(temp == "D")key = 44;
        if(temp == 0){key = 99;et = 1};

        if(key > 0 && key < 13 && et = 1 && current < 6)
        {
            passwd[current] = key;
            current++;
            et = 0;
        }
        if(key>13 && key<50 && et = 1)
        {
            if(key == 14){current=current-1;passwd[current] = 0;}
            if(key == 24){memset(passwd, 0, sizeof(passwd));current = 0;}
            if(key == 34){if(open == 1){memset(passwd, 0, sizeof(passwd));current = 0;mode = !mode;}}
            if(key == 44)
            {
                if(mode == 0 && current == 6)
                {
                    correct = 0;
                    for(i=0;i<6;i++)
                    {
                        if(passwd[i] == password[i])correct++;
                        else break;

                    }
                    if(correct == 6)
                    {
                        //right
                        open = 1;
                    }
                    if(correct < 6)
                    {
                        //wrong
                    }
                }
                if(mode == 1 && current == 6)
                {
                    for(i=0;i<6;i++)
                    {
                        password[i] = passwd[i];
                        passwd[i] = 0;
                        AT24C02_WriteByte(i , password[i]);
                    }
                }
            }
            et = 0;
        }
        //interface
        LCD_ShowString(1,1,"PASSWORD:");
        if(mode == 1)LCD_ShowString(1,11,"RESET");
        if(mode == 0)LCD_ShowString(1,11,"ENTER")
        if(current == 0)LCD_ShowString(2,1,"      ")
        else if(current == 1)LCD_ShowString(2,1,"*     ")
        else if(current == 2)LCD_ShowString(2,1,"**    ")
        else if(current == 3)LCD_ShowString(2,1,"***   ")
        else if(current == 4)LCD_ShowString(2,1,"****  ")
        else if(current == 5)LCD_ShowString(2,1,"***** ")
        else if(current == 3)LCD_ShowString(2,1,"******")

    }
}