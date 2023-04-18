# STM32_LCD_Lib

This repositorie contain a C library to control a LCD screen using the i²C bus driving by a STM32 MCU. The base of the library come from controllers tech (https://controllerstech.com/i2c-lcd-in-stm32/) and I made some modifications.

This library was tested successfully on NUCLEO-L152RE (April 2023).

You will find a heather file and the related source file.
Please pay attention to the #define under i2c-lcd.h, and to the exported i²C handle in the i2c-lcd.c source file. You may change theses value according to your setup.

#How to use this library?
This library was built to use with STM32 HAL for STM32 devices.

Steps to use this library:

Configure the desired i²c pins you want to use with the LCD as GPIOs with internal pull-up resistors (you may use STM32CubeMX).
Import this library into your generated project and link to compilation the folder.


Call lcd_init() to initialize the LCD. Your are now good to go!
You can now use all the function according to your preferences. 

Hope these may help you for your project.
Regards, Axel.
