/*
 * lab22.c
 *
 * Created: 2/7/2012 9:24:15 PM
 *  Author: omer
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
void pulse()
{
	PORTD|=0b00001000;
	_delay_ms(1);
	PORTD &=0b11110111;
	_delay_ms(1);
}
void writeLED(uint8_t num)
{
	PORTD &=0b11101111;
	int i = 0;
	while(num>=0){
		i++;
		int cur_bit = num%2;
		num=num/2;
		if(cur_bit){
			PORTD |=0b00000100;
		}
		else
			PORTD &=0b11111011;
		pulse();
		if(num==0)
			break;		
	}
	while (i<8) {
		i++;
		PORTD &= 0b11111011;
		pulse();
	}
	PORTD |=0b00010000;
}

void flash() {
	
	int i = 0;
	
	PORTD &=0b11101111;
	while (i<8) {
		i++;
		PORTD &= 0b11111011;
		pulse();
	}
	PORTD |=0b00010000;
	_delay_ms(500);
	
	i = 0;
	PORTD &=0b11101111;
	while (i<8) {
		i++;
		PORTD |= 0b00000100;
		pulse();
	}
	PORTD |=0b00010000;
	_delay_ms(500);
}
int main(void)
{
	PORTD=0b00000000;
	DDRD|=0b00011100;
	DDRB &=0b11011111;
	int i = 0;
	while (1) {
		if(PINB & 0b00100000)
			flash();
		else {
			writeLED(i);
			_delay_ms(250); 
			i = ++i % 256;
		}
	}
	//writeLED(5);
	//_delay_ms(2000);
}