/**
 * @author  Tobias Schmalzried
 * @version v1.0
 * @ide     Notepad++, STM32CubeIDE
 * @brief   ST7066U LCD driver library for STM32Fxxx, STM32Gxxx
 *	
\verbatim
   ----------------------------------------------------------------------
    Copyright (c) 2020 Tobias Schmalzried

    This software is developed to drive a ST7066U, however it can be used 
	to drive a HD44780, but this was not tested and not intended to do.
	Furthermore the software may only be used for 8-Bit connection. 4-Bit 
	connection will be implemented in future versions.
	This library relays on the usage of the HAL.
	There is an option for you available which does not rely on the HAL but 
	may be not as functional and smooth.
   ----------------------------------------------------------------------
\endverbatim
 */





#ifdef __cplusplus
extern "C" {
#endif


#include "stdarg.h"
#include "settings.h"

#ifdef g0series
#include "stm32g0xx_it.h"
#endif 

#ifdef f0series 
#include "stm32f0xx_it.h"
#endif

#ifndef RS_PIN
#define RS_PORT				GPIOB
#define RS_PIN				GPIO_PIN_9
#endif

#ifndef E_PIN
#define E_PORT				GPIOC
#define E_PIN				GPIO_PIN_6
#endif

#ifndef RW_PIN
#define RW_PORT				GPIOB
#define RW_PIN				GPIO_PIN_8
#endif

#if bit4 == 0

	#ifndef D0_PIN
	#define D0_PORT				GPIOB
	#define D0_PIN				GPIO_PIN_0
	#endif

	#ifndef D1_PIN
	#define D1_PORT				GPIOB
	#define D1_PIN				GPIO_PIN_1
	#endif

	#ifndef D2_PIN
	#define D2_PORT				GPIOB
	#define D2_PIN				GPIO_PIN_2
	#endif

	#ifndef D3_PIN
	#define D3_PORT				GPIOB
	#define D3_PIN				GPIO_PIN_3
	#endif
	
#endif


#ifndef D4_PIN
#define D4_PORT				GPIOB
#define D4_PIN				GPIO_PIN_4
#endif

#ifndef D5_PIN
#define D5_PORT				GPIOB
#define D5_PIN				GPIO_PIN_5
#endif

#ifndef D6_PIN
#define D6_PORT				GPIOB
#define D6_PIN				GPIO_PIN_6
#endif

#ifndef D7_PIN
#define D7_PORT				GPIOB
#define D7_PIN				GPIO_PIN_7
#endif


/**
 * @brief  Initializes ST7066U.
 * @param  rows: Height of lcd, either 1 or 2. (!) Actual rows are the value *2 (!)
 * @retval None.
 */
 void display_Init(uint8_t rows);
 
 /**
 * @brief  Communicates commands to the display.
 * @param  i: the command as the value of the set bits.
 * @retval None.
 */
 void display_putCom(uint8_t i);
 
 /**
 * @brief  Set the state of the display.
 * @brief  off turns the display off, on turns it on. clear clears the display and home jumps to (0,0) no matter what.
 * @param  state: values are 0 = "off", 1="on", 2="clear", 3="home".
 * @retval None.
 */
 void display_state(int state);
 
 /**
 * @brief  set the mode of the cursor
 * @brief  off turns it off, on turns it on and blinking off/on controls the blinking of the cursor.
 * @param  option: 0 = off; 1= blinking on; 2 = blinking off/on
 * @retval None.
 */
 void display_cursor(uint8_t option);
 
 /**
 * @brief  Prints a string on the display beginning at the specified position.
 * @param  x: the x-location. can be anywhere between 1 and 20.
 * @param  y: the y-location, aka the row. value between 1 and 4.
 * @param  *str: Pointer to the string to display.
 * @retval None.
 */
 void display_puts(uint8_t x, uint8_t y, char* str);
 
 

#ifdef __cplusplus
}
#endif