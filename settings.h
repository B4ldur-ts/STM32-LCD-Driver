/**
*
* This file is associated with the HAL-Projects and serves as settings page.
* To make code as universal as possible this is used to enter your configuration.
*
**/


/**
*
*---------------------------------------------------------------------------------
*								ST7066U - Driver
*---------------------------------------------------------------------------------
*
**/


/*if you're using a f0 device, uncomment the line with the f0 device and comment the g0 line*/

//#define f0series		
#define g0series

/* If you're using a bit4it-Connection the value is "1". For 8Bit-Connection write "0".*/

#define bit4 0



/* Example on how to define your connections to the display. For bit4it-Connection dont define any values for D0 - D3. */
/*
#define RS_Port GPIOA
#define RS_Pin GPIO_PIN_0
#define RW_Port
#define RW_Pin
#define E_Port
#define E_Pin
#define D0_Port
#define D0_Pin
#define D1_Port
#define D1_Pin
#define D2_Port
#define D2_Pin
#define D3_Port
#define D3_Pin
#define D4_Port
#define D4_Pin
#define D5_Port
#define D5_Pin
#define D6_Port
#define D6_Pin
#define D7_Port
#define D7_Pin
*/


/**
*
*--------------------------------------------------------------------------------------------
*
* When not using the HAL please enter your operating frequency here.
* E.g. your frequency is 24 MHz, write frequency = 24000000;
*
*---------------------------------------------------------------------------------------------
*
**/



uint32_t frequency = 24000000;







