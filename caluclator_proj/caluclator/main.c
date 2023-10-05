/**********************************************************************************************************
 * [FILE NAME]		:			main.c												                      *
 * [DESCRIPTION]	:			main applictaion for calculator project									  *
 * [DATE CREATED]	: 			october 2, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
#include "lcd.h"
#include "keypad.h"
#include <util\delay.h>
uint8 flag = 0;
int main(void){
	uint32 result;
	uint8 key_symbol ;
	uint8 i=0 ;
	/*two arrays one for operands and one for numbers*/
	uint8 arr1[100], arr2[100];
	/* Initialize the LCD */
	LCD_init();

	LCD_moveCursor(0,4);
	LCD_displayString("CaLculator");
	LCD_displayStringRowColumn(1, 4, "Project");
	_delay_ms(500);
	LCD_clearScreen();
	LCD_moveCursor(0,4);
	LCD_displayString("MT Embedded");
	LCD_displayStringRowColumn(1, 4, "Diploma");
	_delay_ms(500);

	LCD_clearScreen();
	while(1)
	{
		for(i=0 ; i<16 ; i++){
			key_symbol = KEYPAD_getPressedKey();
			if(key_symbol >= 0 && key_symbol<=9)
			{
				arr1[i] = key_symbol;
				LCD_integerToString(arr1[i]);
			}
			if(key_symbol == '+' || key_symbol == '-' || key_symbol == '%'||
					key_symbol == '*')
			{
				arr2[i] = key_symbol;
				LCD_displayCharacter(arr2[i]);
			}
			if(i == 3){
				switch(arr2[1]){
				case '*':
					result = (arr1[0] * arr1[2]);
					break;
				case '-':
					result = (arr1[0] - arr1[2]);
					break;
				case '+':
					result = (arr1[0] + arr1[2]);
					break;
				case '%':
					result = (arr1[0] / arr1[2]);
					break;
				}
			}
			if(key_symbol == '=')
			{
				if(i==3)
				{
					LCD_displayStringRowColumn(1, 0, "Result=");
					LCD_integerToString(result);
					break;
				}
				else
				{
					for(i=3 ; i<16 ; i+=2){

					switch(arr2[i]){
					case '*':
						result *= arr1[i+1];
						break;
					case '-':
						result -= arr1[i+1];
						break;
					case '+':
						result += arr1[i+1];
						break;
					case '%':
						result /= arr1[i+1];
						break;
					}
					}

				}
				LCD_displayStringRowColumn(1, 0, "Result=");
				LCD_integerToString(result);
				_delay_ms(500);
				result = 0;
				for(i=0 ;i<=15; i++){
					arr1[i] = arr2[i] = 0;
				}
				i=0;
				break;
			}

			if(key_symbol == 13)
			{
				LCD_clearScreen();
				break;
			}
			_delay_ms(500);
		}
	}
}

