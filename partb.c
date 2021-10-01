 // polling

/*
 * GccApplication1.c
 *
 * Created: 9/17/2021 11:18:38 AM
 * Author : adwayt
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void Initialize()
{
	// SET LED PIN OUTPUT MODE
	DDRB = 0b00000010; 
	
	// SET PIN INPUT MODE
	DDRD &= ~(1<<DDD7); 
}

int main(void)
{
	Initialize();
	while (1)
	{
		if (!(PIND & (1<<PIND7))  )
		{
			PORTB= 0b00000010;
		}
		else
		{
			PORTB = 0b00000000;
		}
	}
}
