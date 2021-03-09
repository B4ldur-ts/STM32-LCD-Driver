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
	RS_PORT -> ODR &= ~RS_PIN;			//set the r/s Pin = low, because a command is following
	RW_PORT -> ODR &= ~RW_PIN;
	uint8_t value = 0x0;
	#if bit4 == 0																//set rw pin to low, because we are writing a command
	value = i & 1;	
	if (value > 0){																	//set all databits to transmit signal
		D0_PORT -> ODR |= D0_PIN;
	else{ 
		D0_PORT -> ODR &= ~D0_PIN;
	}																		
	value = i & 2;
	if (value > 0){																	//set all databits to transmit signal
		D1_PORT -> ODR |= D1_PIN;}
	else{ 
		D1_PORT -> ODR &= ~D1_PIN;
	}
	value = i & 4;
	if (value > 0){																	//set all databits to transmit signal
		D2_PORT -> ODR |= D2_PIN;}
	else{ 
		D2_PORT -> ODR &= ~D2_PIN;
	}
	value = i & 8;
	if (value > 0){																	//set all databits to transmit signal
		D3_PORT -> ODR |= D3_PIN;}
	else{ 
		D3_PORT -> ODR &= ~D3_PIN;
	}
	#endif
	value = i & 16;
	if (value > 0){																	//set all databits to transmit signal
		D4_PORT -> ODR |= D4_PIN;}
	else{ 
		D4_PORT -> ODR &= ~D4_PIN;
	}
	value = i & 32;
	if (value > 0){																	//set all databits to transmit signal
		D5_PORT -> ODR |= D5_PIN;}
	else{ 
		D5_PORT -> ODR &= ~D5_PIN;
	}
	value = i & 64;
	if (value > 0){																	//set all databits to transmit signal
		D6_PORT -> ODR |= D6_PIN;}
	else{ 
		D6_PORT -> ODR &= ~D6_PIN;
	}
	value = i & 128;
	if (value > 0){																	//set all databits to transmit signal
		D7_PORT -> ODR |= D7_PIN;}
	else{ 
		D7_PORT -> ODR &= ~D7_PIN;
	}

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
	customDelayFine(4);
	D0_PORT -> ODR &= ~D0_PIN;
	D1_PORT -> ODR &= ~D1_PIN;
	D2_PORT -> ODR &= ~D2_PIN;
	D3_PORT -> ODR &= ~D3_PIN;
	D4_PORT -> ODR &= ~D4_PIN;
	D5_PORT -> ODR &= ~D5_PIN;
	D6_PORT -> ODR &= ~D6_PIN;
	D7_PORT -> ODR &= ~D7_PIN;
}


void display_Init(uint8_t rows){

	E_PORT -> ODR &= ~E_PIN;
	customDelay(75); 								//Delay according to the datasheet
	display_putCom(0x30);
	customDelayBig(75); 
	display_putCom(0x30); 						//command 0x30 = Wake up #2
	customDelayBig(75); 								//must wait 160us, busy flag not available
	display_putCom(0x30); 						//command 0x30 = Wake up #3
	customDelayBig(75); 								//must wait 160us, busy flag not available
	if (rows == 1){
		display_putCom(0x30);
	}
	if (rows == 2){								//double row intialization
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
	if bit4 == 0																//set rw pin to low, because we are writing a command
	value = i & 1;	
	if (value > 0){																	//set all databits to transmit signal
		D0_PORT -> ODR |= D0_PIN;
	else{ 
		D0_PORT -> ODR &= ~D0_PIN;
	}																		
	value = i & 2;
	if (value > 0){																	//set all databits to transmit signal
		D1_PORT -> ODR |= D1_PIN;}
	else{ 
		D1_PORT -> ODR &= ~D1_PIN;
	}
	value = i & 4;
	if (value > 0){																	//set all databits to transmit signal
		D2_PORT -> ODR |= D2_PIN;}
	else{ 
		D2_PORT -> ODR &= ~D2_PIN;
	}
	value = i & 8;
	if (value > 0){																	//set all databits to transmit signal
		D3_PORT -> ODR |= D3_PIN;}
	else{ 
		D3_PORT -> ODR &= ~D3_PIN;
	}
	#endif
	value = i & 16;
	if (value > 0){																	//set all databits to transmit signal
		D4_PORT -> ODR |= D4_PIN;}
	else{ 
		D4_PORT -> ODR &= ~D4_PIN;
	}
	value = i & 32;
	if (value > 0){																	//set all databits to transmit signal
		D5_PORT -> ODR |= D5_PIN;}
	else{ 
		D5_PORT -> ODR &= ~D5_PIN;
	}
	value = i & 64;
	if (value > 0){																	//set all databits to transmit signal
		D6_PORT -> ODR |= D6_PIN;}
	else{ 
		D6_PORT -> ODR &= ~D6_PIN;
	}
	value = i & 128;
	if (value > 0){																	//set all databits to transmit signal
		D7_PORT -> ODR |= D7_PIN;}
	else{ 
		D7_PORT -> ODR &= ~D7_PIN;
	}

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
	customDelayFine(1);
	
	D0_PORT -> ODR &= ~D0_PIN;
	D1_PORT -> ODR &= ~D1_PIN;
	D2_PORT -> ODR &= ~D2_PIN;
	D3_PORT -> ODR &= ~D3_PIN;
	D4_PORT -> ODR &= ~D4_PIN;
	D5_PORT -> ODR &= ~D5_PIN;
	D6_PORT -> ODR &= ~D6_PIN;
	D7_PORT -> ODR &= ~D7_PIN;

}



void display_state(int state){				// 0 = off; 1 = clear; 2= home, 3 = on

	if (state  == 0){
		display_putCom(0x8);
		customDelayFine(2);
	}
	if (state == 1){
		display_putCom(0x1);
		customDelayFine(2);
	}
	if (state == 2){
		display_putCom(0x2);
		customDelayFine(2);
	}
	if (state == 3){
		display_putCom(0xc);
		customDelayFine(2);
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


static void customDelayFine(int delay){						//for very small Delays (under 7 ms) this is pretty accurate, more accurate than the HAL_Delay() method
	uint32_t x = ((frequency/100000) * delay) * 2;		//Delay in ms
	x += 8;
	uint32_t i = 0;
	while (i<=x){
		i++;
	}
}


static void customDelayBig(int delay){					//for delays over 7ms more precise than the HAL
	uint32_t x = ((frequency/9750) * delay) / 5;		//Delay over 60 ms
	x -= 5;
	uint32_t i = 0;
	while (i<=x){
		i++;
	}	
}










