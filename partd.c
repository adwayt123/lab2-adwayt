// DOT DASH SPACE CHARACTER


#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "uart.h"

unsigned long edge = 0;
unsigned long falling_edge = 0;
unsigned long falling_period = 0;

unsigned long total_time = 0;

int seq_end = 0;
int overflow_count = 0;
int temp = 0;


char Record[5];
int count=0;


void Initialize()
{
	// CLEAR GLOBAL INTERRUPTS
	cli();
	
	DDRB &= ~(1 << DDB0);
	DDRB |= (1 << DDB5);
	
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
	
	temp = overflow_count;
	
	// END REACHED - NOW RESET
	overflow_count = 0;
	
	//edge = ICR1;
	
	if(TCCR1B & (1 << ICES1))
	{
		falling_edge = ICR1;
		total_time = (62500 * temp + ICR1) - edge;
		
		if(total_time > 1875 && total_time < 12500){
			
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
		edge = ICR1;
		falling_period = (62500 * temp + ICR1) - falling_edge;
		if(falling_period > 25000)
		{
			//UART_putstring(" Displaying Record\n");
			//UART_putstring(Record);
			
			if (Record[0]=='.' && Record[1]== '-' && Record[2]=='x'){
				UART_putstring("A"); 
				
			}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='.' && Record[3]=='.' && Record[4]=='x'){UART_putstring("B");}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='-' && Record[3]=='.' && Record[4]=='x'){UART_putstring("C");}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='.' && Record[3]=='x' && Record[4]=='x'){UART_putstring("D");}
			
			else if(Record[0]=='.' && Record[1]=='x' && Record[2]=='x' && Record[3]=='x' && Record[4]=='x'){UART_putstring("E");}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='-' && Record[3]=='.' && Record[4]=='x'){UART_putstring("F");}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='.' && Record[3]=='x' && Record[4]=='x'){UART_putstring("G");}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='.' && Record[3]=='x' && Record[4]=='x'){UART_putstring("H");}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='x' && Record[3]=='x' && Record[4]=='x'){UART_putstring("I");}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='-' && Record[3]=='-' && Record[4]=='x'){UART_putstring("J");}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='-' && Record[3]=='x' && Record[4]=='x'){UART_putstring("K");}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='.' && Record[3]=='.' && Record[4]=='x'){UART_putstring("L");}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='x' && Record[3]=='x' && Record[4]=='x'){UART_putstring("M");}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='x' && Record[3]=='x' && Record[4]=='x'){UART_putstring("N");}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='-' && Record[3]=='x' && Record[4]=='x'){UART_putstring("O");}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='-' && Record[3]=='.' && Record[4]=='x'){UART_putstring("P");}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='.' && Record[3]=='-' && Record[4]=='x'){UART_putstring("Q");}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='.' && Record[3]=='x' && Record[4]=='x'){UART_putstring("R");}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='.' && Record[3]=='x' && Record[4]=='x'){UART_putstring("S");}
			
			else if(Record[0]=='-' && Record[1]=='x' && Record[2]=='x' && Record[3]=='x' && Record[4]=='x'){UART_putstring("T");}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='-' && Record[3]=='x' && Record[4]=='x'){UART_putstring("U");}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='-' && Record[3]=='x' && Record[4]=='x'){UART_putstring("V");}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='-' && Record[3]=='x' && Record[4]=='x'){UART_putstring("W");}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='.' && Record[3]=='-' && Record[4]=='x'){UART_putstring("X");}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='-' && Record[3]=='-' && Record[4]=='x'){UART_putstring("Y");}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='.' && Record[3]=='.' && Record[4]=='x'){UART_putstring("Z");}
			
			else if(Record[0]=='.' && Record[1]=='-' && Record[2]=='-' && Record[3]=='-' && Record[4]=='-'){UART_putstring("1");}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='-' && Record[3]=='-' && Record[4]=='-'){UART_putstring("2");}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='.' && Record[3]=='-' && Record[4]=='-'){UART_putstring("3");}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='.' && Record[3]=='.' && Record[4]=='-'){UART_putstring("4");}
			
			else if(Record[0]=='.' && Record[1]=='.' && Record[2]=='.' && Record[3]=='.' && Record[4]=='.'){UART_putstring("5");}
			
			else if(Record[0]=='-' && Record[1]=='.' && Record[2]=='.' && Record[3]=='.' && Record[4]=='.'){UART_putstring("6");}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='.' && Record[3]=='.' && Record[4]=='.'){UART_putstring("7");}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='-' && Record[3]=='.' && Record[4]=='.'){UART_putstring("8");}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='-' && Record[3]=='-' && Record[4]=='.'){UART_putstring("9");}
			
			else if(Record[0]=='-' && Record[1]=='-' && Record[2]=='-' && Record[3]=='-' && Record[4]=='-'){UART_putstring("0");}
			
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
	if(overflow_count < 2)
	overflow_count++;
}

int main(void)
{
	DDRB = 0b00001100;
	for(int i=0; i<5;i++){Record[i]='x';}
	Initialize();
	UART_init(BAUD_PRESCALER);
	
	while(1);
}