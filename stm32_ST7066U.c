/***
v1.0
(c) Tobias Schmalzried
***/

#include "stm32_ST7066U.h"

uint8_t row = 0x0;
uint8_t rowStart[]={0x0, 0x40, 0x14, 0x50};

static void display_putChar(char);
static void setCursor(uint8_t, uint8_t);



void display_putCom(uint8_t i){

	static uint8_t check = 0x1;
	HAL_GPIO_WritePin(RS_PORT, RS_PIN, GPIO_PIN_RESET);				//set the r/s Pin = low, because a command is following
	HAL_GPIO_WritePin(RW_PORT, RW_PIN, GPIO_PIN_RESET);
	uint8_t value = 0x0;
	#if bit4 == 0																//set rw pin to low, because we are writing a command
	value = i & 1;											//set all databits to transmit signal
	HAL_GPIO_WritePin(D0_PORT, D0_PIN, value);
	value = i & 2;
	HAL_GPIO_WritePin(D1_PORT, D1_PIN, value);
	value = i & 4;
	HAL_GPIO_WritePin(D2_PORT, D2_PIN, value);
	value = i & 8;
	HAL_GPIO_WritePin(D3_PORT, D3_PIN, value);
	#endif
	value = i & 16;
	HAL_GPIO_WritePin(D4_PORT, D4_PIN, value);
	value = i & 32;
	HAL_GPIO_WritePin(D5_PORT, D5_PIN, value);
	value = i & 64;
	HAL_GPIO_WritePin(D6_PORT, D6_PIN, value);
	value = i & 128;
	HAL_GPIO_WritePin(D7_PORT, D7_PIN, value);

	E_PORT -> ODR |= E_PIN;								//blink the enable pin to send a signal
	E_PORT -> ODR &= ~E_PIN;

	#if bit4==1										//when bit4 mode is used, first the high nybble is transfered. After that the low nybble is transfered, by making it in
	i = i << 4;											//the exact same format. To prevent an endless loop of calling the function, an alternating variable has been put in place.
	if((check % 2) == 0){
		display_putCom(i);
		check++;
	}
	if (check == 255){
		check = 1;
	}

	#endif
	HAL_Delay(4);
	HAL_GPIO_WritePin(D0_PORT, D0_PIN, 0);
	HAL_GPIO_WritePin(D1_PORT, D1_PIN, 0);
	HAL_GPIO_WritePin(D2_PORT, D2_PIN, 0);
	HAL_GPIO_WritePin(D3_PORT, D3_PIN, 0);
	HAL_GPIO_WritePin(D4_PORT, D4_PIN, 0);
	HAL_GPIO_WritePin(D5_PORT, D5_PIN, 0);
	HAL_GPIO_WritePin(D6_PORT, D6_PIN, 0);
	HAL_GPIO_WritePin(D7_PORT, D7_PIN, 0);
}


void display_Init(uint8_t rows){

	E_PORT -> ODR &= ~E_PIN;
	HAL_Delay(75); 								//Delay according to the datasheet
	display_putCom(0x30);
	HAL_Delay(30);
	display_putCom(0x30); 						//command 0x30 = Wake up #2
	HAL_Delay(10); 								//must wait 160us, busy flag not available
	display_putCom(0x30); 						//command 0x30 = Wake up #3
	HAL_Delay(10);								//must wait 160us, busy flag not available
	row = rows;
	if (row == 1){
		display_putCom(0x30);
	}
	if (row == 2){								//double row intialization
		display_putCom(0x38);
	}
	display_putCom(0x10); 						//Set cursor
	display_putCom(0x0c);						//Display ON; Cursor ON
	display_putCom(0x1);						// Clear the display
	display_putCom(0x06);						//Entry mode set

}

static void display_putChar(char c){

	HAL_GPIO_WritePin(RS_PORT, RS_PIN, GPIO_PIN_SET);				//set the r/s Pin = high, because data is following
	HAL_GPIO_WritePin(RW_PORT, RW_PIN, GPIO_PIN_RESET);				//set rw pin to low, because we are writing sth
	static uint8_t check = 0x1;
	uint8_t value = 0x0;
	#if bit4 == 0
	value = c & 1;											//set all databits to transmit signal
	HAL_GPIO_WritePin(D0_PORT, D0_PIN, value);
	value = c & 2;
	HAL_GPIO_WritePin(D1_PORT, D1_PIN, value);
	value = c & 4;
	HAL_GPIO_WritePin(D2_PORT, D2_PIN, value);
	value = c & 8;
	HAL_GPIO_WritePin(D3_PORT, D3_PIN, value);
	#endif
	value = c & 16;
	HAL_GPIO_WritePin(D4_PORT, D4_PIN, value);
	value = c & 32;
	HAL_GPIO_WritePin(D5_PORT, D5_PIN, value);
	value = c & 64;
	HAL_GPIO_WritePin(D6_PORT, D6_PIN, value);
	value = c & 128;
	HAL_GPIO_WritePin(D7_PORT, D7_PIN, value);

	E_PORT -> ODR |= E_PIN;								//blink the enable pin to send a signal
	E_PORT -> ODR &= ~E_PIN;
	#if bit4 == 1										//when bit4 mode is used, first the high nybble is transfered. After that the low nybble is transfered, by making it in
	i = i << 4;											//the exact same format. To prevent an endless loop of calling the function, an alternating variable has been put in place.
	if((check % 2) == 0){
		display_putChar(c);
		check++;
	}
	if (check == 255){
		check = 1;
	}

	#endif
	HAL_Delay(1);
	HAL_GPIO_WritePin(D0_PORT, D0_PIN, 0);
	HAL_GPIO_WritePin(D1_PORT, D1_PIN, 0);
	HAL_GPIO_WritePin(D2_PORT, D2_PIN, 0);
	HAL_GPIO_WritePin(D3_PORT, D3_PIN, 0);
	HAL_GPIO_WritePin(D4_PORT, D4_PIN, 0);
	HAL_GPIO_WritePin(D5_PORT, D5_PIN, 0);
	HAL_GPIO_WritePin(D6_PORT, D6_PIN, 0);
	HAL_GPIO_WritePin(D7_PORT, D7_PIN, 0);

}



void display_state(int state){				// 0 = off; 1 = clear; 2= home, 3 = on

	if (state  == 0){
		display_putCom(0x8);
		HAL_Delay(2);
	}
	if (state == 1){
		display_putCom(0x1);
		HAL_Delay(2);
	}
	if (state == 2){
		display_putCom(0x2);
		HAL_Delay(2);
	}
	if (state == 3){
		display_putCom(0xc);
		HAL_Delay(2);
	}

}

void display_cursor(uint8_t option){

	if (option == 0){
		display_putCom(0xC);
	}
	if (option == 2 || option == 3){
		display_putCom(0xE);
	}
	if (option == 1){
		display_putCom(0xF);
	}

}

static void setCursor(uint8_t x, uint8_t y){

	if (y < 1){
		y = 0;
	}

	if (x < 0){
		x = 0;
	}
	if (y > (row*2)){
		y = 0;
	}
	if (x > 20){
		x = 0;
	}
	uint8_t pos = x + rowStart[y-1];
	pos += 0x40; 											//adding offset, becaus DB7 always is 1 by setting the ddram, see datasheet
	display_putCom(pos);

}


void display_puts(uint8_t x, uint8_t y, char* str){				//enter the starting position and the string to be printed
																// 3 style codes are available \n = newline  \r = go back to the beginning of the line  \t = jump to the fourth last position
	display_cursor(0);
	if (y < 1){
		y = 1;
	}

	if (x < 0){
		x = 0;
	}

	while (*str){
		setCursor(x,y);
		if(x>20){
			x = 0;
			y++;
		}
		else if (*str == '\n'){
			y++;
		}
		else if (*str == '\r'){
			x = 0;
		}
		else if (*str == '\t'){
			x = 17 + rowStart[y-1];
		}
		else {
			display_putChar(*str);
			x++;
		}
		str++;
	}
}
















