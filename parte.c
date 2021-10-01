// DOT DASH SPACE + ASCII - SEPARATE WITH TIME 

/*
 * GccApplication1.c
 *
 * Created: 9/17/2021 11:18:38 AM
 * Author : adwayt
 */


#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "uart.h"


unsigned long falling_edge = 0;
unsigned long falling_period = 0;

unsigned long total_time = 0;

int o_count = 0;
int temp = 0;
unsigned long temp1 = 0;

char Record[5];
int count=0;
int char2ascii =0; 

void Initialize()
{
	// CLEAR GLOBAL INTERRUPTS
	cli();
	
	// TIMER1 DIV BY 256
	TCCR1B &= ~(1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B |= (1 << CS12);
	
	//TIMER NORMAL MODE
	TCCR1A &= ~(1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	TCCR1B &= ~(1 << WGM12);
	TCCR1B &= ~(1 << WGM13);
	
	//TIFR = 1
	TIFR1 |= (1 << ICF1);
	
	//CHECK FOR FALLING EDGE
	TCCR1B &= ~(1 << ICES1);
	
	// SET INPUT CAPTURE
	TIMSK1 |= (1 << ICIE1);
	
	// IF OVERFLOW, INTERRUPT
	TIMSK1 |= (1 << TOIE1);
	
	// BEGIN INTERRUPT
	sei();
}

ISR(TIMER1_CAPT_vect)
{
	PORTB ^= (1 << PORTB5);
	
	temp = o_count;
	
	// END REACHED - NOW RESET
	o_count = 0;
	
	//edge = ICR1;
	if(TCCR1B & (1 << ICES1))
	{
		falling_edge = ICR1;
		total_time = (62500*temp + ICR1)-temp1;
		
		if(total_time>1875 && total_time<12500){
			
			UART_putstring(".\n");
			Record[count] = '.';
			count=count+1;
			PORTB = 0b00000100;
			_delay_ms(250);
			PORTB = 0b00000000;
			
		}
		
		else if(total_time > 12500 && total_time < 25000){
			UART_putstring("-\n");
			Record[count] = '-';
			count=count+1;
			PORTB = 0b00001000;
			_delay_ms(250);
			PORTB = 0b00000000;
			
		}
	}
	else
	{
		temp1 = ICR1;
		falling_period = (62500 * temp + ICR1) - falling_edge;
		if(falling_period > 25000)
		{
			//UART_putstring(" Displaying Record\n");
			//UART_putstring(Record);
			
			if (Record[0]=='.' && Record[1]== '-' && Record[2]=='x'){
				char2ascii = 'A';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR A"); 
				
			}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='.' && Record[3]=='.' && Record[4]=='x'){
				char2ascii = 'B';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR B");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='-' && Record[3]=='.' && Record[4]=='x'){
				char2ascii = 'C';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR C");

				}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='.' && Record[3]=='x' && Record[4]=='x'){
				char2ascii = 'D';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR D");

				}
			
			else if(Record[0]=='.' && Record[1]=='x' && Record[2]=='x' && Record[3]=='x' && Record[4]=='x'){
				char2ascii = 'E';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR E");
				
				}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='-' && Record[3]=='.' && Record[4]=='x'){
				
				char2ascii = 'F';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR F");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='.' && Record[3]=='x' && Record[4]=='x'){
				char2ascii = 'G';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR G");
				
				}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='.' && Record[3]=='x' && Record[4]=='x'){
				char2ascii = 'H';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR H");
				
				}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='x' && Record[3]=='x' && Record[4]=='x'){
				char2ascii = 'I';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR I");
				
				}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='-' && Record[3]=='-' && Record[4]=='x'){
				
				char2ascii = 'J';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR J");
				
				
				}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='-' && Record[3]=='x' && Record[4]=='x'){
				char2ascii = 'K';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR K");
				
				
				}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='.' && Record[3]=='.' && Record[4]=='x'){
				
				char2ascii = 'L';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR L");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='x' && Record[3]=='x' && Record[4]=='x'){
				
				char2ascii = 'M';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR M");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='x' && Record[3]=='x' && Record[4]=='x'){
				
				char2ascii = 'N';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR N");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='-' && Record[3]=='x' && Record[4]=='x'){
				
				char2ascii = 'O';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR O");
				
				}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='-' && Record[3]=='.' && Record[4]=='x'){
				char2ascii = 'P';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR P");
				
				
				}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='.' && Record[3]=='-' && Record[4]=='x'){
				
				char2ascii = 'Q';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR Q");
				
				
				}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='.' && Record[3]=='x' && Record[4]=='x'){
				
				char2ascii = 'R';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR R");
				
				
				}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='.' && Record[3]=='x' && Record[4]=='x'){
				
				char2ascii = 'S';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR S");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='x' && Record[2]=='x' && Record[3]=='x' && Record[4]=='x'){
				
				char2ascii = 'T';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR T");
				
				
				}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='-' && Record[3]=='x' && Record[4]=='x'){
				
				char2ascii = 'U';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR U");
				
				
				}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='-' && Record[3]=='x' && Record[4]=='x'){
				
				char2ascii = 'V';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR V");
				
				}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='-' && Record[3]=='x' && Record[4]=='x'){
				
				char2ascii = 'W';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR W");
				
				
				}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='.' && Record[3]=='-' && Record[4]=='x'){
				
				char2ascii = 'X';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR X");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='-' && Record[3]=='-' && Record[4]=='x'){
				
				char2ascii = 'Y';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR Y");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='.' && Record[3]=='.' && Record[4]=='x'){
				
				char2ascii = 'Z';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR Z");
				
				
				}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='-' && Record[3]=='-' && Record[4]=='-'){
				
				char2ascii = '1';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR 1");
				
				
				}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='-' && Record[3]=='-' && Record[4]=='-'){
				
				char2ascii = '2';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR 2");
				
				}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='.' && Record[3]=='-' && Record[4]=='-'){
				
				char2ascii = '3';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR 3");
				
				
				}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='.' && Record[3]=='.' && Record[4]=='-'){
				
				char2ascii = '4';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR 4");
				
				}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='.' && Record[3]=='.' && Record[4]=='.'){
				
				char2ascii = '5';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR 5");
				
				
				}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='.' && Record[3]=='.' && Record[4]=='.'){
				
				char2ascii = '6';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR 6");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='.' && Record[3]=='.' && Record[4]=='.'){
				
				char2ascii = '7';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR 7");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='-' && Record[3]=='.' && Record[4]=='.'){
				
				char2ascii = '8';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR 8");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='-' && Record[3]=='-' && Record[4]=='.'){
				
				char2ascii = '9';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR 9");
				
				}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='-' && Record[3]=='-' && Record[4]=='-'){
				
				char2ascii = '0';
				char snum[5];
				itoa(char2ascii, snum, 10);
				
				UART_putstring(snum);
				UART_putstring(" ASCII FOR 0");
				
				
				}
			
			else {}
			
			for (int i=0;i<5;i++){
				Record[i]='x';
			}
			count=0;
		}
		
	}
	
	
	TCCR1B ^= (1 << ICES1);
}

ISR(TIMER1_OVF_vect)
{
	if(o_count < 2)
	o_count++;
}

int main(void)
{
	DDRB = 0b00001100;
	for(int i=0; i<5;i++){Record[i]='x';}
	Initialize();
	UART_init(BAUD_PRESCALER);
	
	while(1);
}