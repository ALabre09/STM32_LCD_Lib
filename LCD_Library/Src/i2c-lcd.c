/*
 * 	Title: i2C-lcd.c.
 *	Description: This source file will contain the function related for using standard LCD with i²C communication bus.
 *  Review: April 18, 2023.
 *  Main Programmer: This library was created first by Controllers Tech and review by Axel Labre (axellabre3@gmail.com).
 */

/* **************************************************************************** i2c-lcd Start ******************************************************************************* */
#include "i2c-lcd.h"

/* ******************************************************************** Private Variables for i2c-lcd *********************************************************************** */
extern I2C_HandleTypeDef hi2c1;	// You may change this according to your set-up

/* ******************************************************************* Private functions  for i2c-lcd *********************************************************************** */
/*
 * @brief: this function will initialized the LCD
 * @param: None.
 * @retval: None.
 * @spec: Make sure your use the correct slave address (define under i2c-lcd.h).
 */
void lcd_init (void)
{
	// 4 bit initialization
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // Display initialization
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

/*
 * @brief: This function will send a commmand to the LCD.
 * @param: char cmd -> command to be send.
 * @retval: None.
 * @spec:  None.
 */
void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

/*
 * @brief: This function will clear the LCD.
 * @param: None.
 * @retval: None.
 * @spec:  None.
 */
void lcd_clear (void)
{
	lcd_send_cmd (0x80);
	for (int i=0; i<70; i++)
	{
		lcd_send_data (' ');
	}
}

/*
 * @brief: This function may be use to put the cursor of the LCD to a specific row and column.
 * @param: int row -> row number
 * 		   int col -> column number
 * @retval: None.
 * @spec:  None.
 */
void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}

/*
 * @brief: This function will print a data on the LCD.
 * @param: char data -> data to be send.
 * @retval: None.
 * @spec:  None.
 */
void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

/*
 * @brief: This function will print a string on the LCD.
 * @param: char* str -> string to print.
 * @retval: None.
 * @spec:  None.
 */
void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

/*
 * @brief: This function will print a number on the LCD.
 * @param: uint16_t Number -> number to print.
 * @retval: None.
 * @spec:  None.
 */
void lcd_send_number(uint16_t Number)
{
	  char String_Number[MAX_BUFFER_SIZE];
	  snprintf(String_Number, MAX_BUFFER_SIZE, "%u", Number);
	  lcd_send_string(String_Number);
}

/* **************************************************************************** i2c-lcd End ******************************************************************************* */
