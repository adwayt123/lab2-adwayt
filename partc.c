// INTERRUPT

/*
 * GccApplication1.c
 *
 * Created: 9/17/2021 11:18:38 AM
 * Author : adwayt
 */

#include <avr/io.h>
#include <avr/interrupt.h>

void Initialize(){
cli(); //disable global interrupts

DDRB |= (1<<DDB5);
DDRB &= ~(1<<DDB0);

TCCR1B &= ~(1<<CS10);
TCCR1B |= ~(1<<CS11);
TCCR1B &= ~(1<<CS12);

TCCR1B &= ~(1<<ICES1); //looking for rising edge
TIFR1 |= (1<<ICF1); //clear interrupt flag

TIMSK1 |= (1<<ICIE1); //enable input capture interrupt

sei(); //enable global interrupts
}

ISR(TIMER1_CAPT_vect)
{
if (PINB & (1<<PINB0))
{
PORTB &= ~(1<<PORTB5);
}
else
{
PORTB |= (1<<PORTB5);
}
TIFR1 |= (1<<ICF1); //clear interrupt flag
}

int main()
{
Initialize();
while(1);
}
