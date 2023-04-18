/*
 * 	Title: i2C-lcd.h.
 *	Description: This heather file will contain the function related for using standard LCD with i²C communication bus.
 *  Review: April 18, 2023.
 *  Main Programmer: This library was created first by Controllers Tech and review by Axel Labre (axellabre3@gmail.com).
 */

/* **************************************************************************** i2c-lcd Start ******************************************************************************* */
#include "stm32l1xx_hal.h"
#include "stdio.h"

/* ************************************************************************* Defines for i2c-lcd **************************************************************************** */
#define SLAVE_ADDRESS_LCD 	(0x27<<1)	// You may change this according to your set-up
#define MAX_BUFFER_SIZE 	20			// Max buffer size for snprintf function

/* **************************************************************** Private functions prototypes for i2c-lcd **************************************************************** */
/*
 * @brief: this function will initialized the LCD
 * @param: None.
 * @retval: None.
 * @spec: Make sure your use the correct slave address (define under i2c-lcd.h).
 */
void lcd_init (void);

/*
 * @brief: This function will send a commmand to the LCD.
 * @param: char cmd -> command to be send.
 * @retval: None.
 * @spec:  None.
 */
void lcd_send_cmd (char cmd);

/*
 * @brief: This function will clear the LCD.
 * @param: None.
 * @retval: None.
 * @spec:  None.
 */
void lcd_clear (void);

/*
 * @brief: This function may be use to put the cursor of the LCD to a specific row and column.
 * @param: int row -> row number
 * 		   int col -> column number
 * @retval: None.
 * @spec:  None.
 */
void lcd_put_cur(int row, int col);

/*
 * @brief: This function will print a data on the LCD.
 * @param: char data -> data to be send.
 * @retval: None.
 * @spec:  None.
 */
void lcd_send_data (char data);

/*
 * @brief: This function will print a string on the LCD.
 * @param: char* str -> string to print.
 * @retval: None.
 * @spec:  None.
 */
void lcd_send_string (char *str);

/*
 * @brief: This function will print a number on the LCD.
 * @param: uint16_t Number -> number to print.
 * @retval: None.
 * @spec:  None.
 */
void lcd_send_number(uint16_t Number);

/* **************************************************************************** i2c-lcd End ******************************************************************************* */
