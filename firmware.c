#define F_CPU 16e6

#include <avr/io.h>
#include <util/delay.h>

// Port B
#define LED 0b00100000

// Port C
#define POS 0b00000001
#define NEG 0b00001000

static const char *const data = "~PN\r";

static void transmit(unsigned long delay)
{
	register char c;

	for (const char *ptr = data; *ptr; ptr++) {
		c = *ptr;

		// start bit
		PORTC = POS;
		__builtin_avr_delay_cycles(delay);

		PORTC = (c & (1 << 0)) ? NEG : POS;
		__builtin_avr_delay_cycles(delay);
		PORTC = (c & (1 << 1)) ? NEG : POS;
		__builtin_avr_delay_cycles(delay);
		PORTC = (c & (1 << 2)) ? NEG : POS;
		__builtin_avr_delay_cycles(delay);
		PORTC = (c & (1 << 3)) ? NEG : POS;
		__builtin_avr_delay_cycles(delay);
		PORTC = (c & (1 << 4)) ? NEG : POS;
		__builtin_avr_delay_cycles(delay);
		PORTC = (c & (1 << 5)) ? NEG : POS;
		__builtin_avr_delay_cycles(delay);
		PORTC = (c & (1 << 6)) ? NEG : POS;
		__builtin_avr_delay_cycles(delay);
		PORTC = (c & (1 << 7)) ? NEG : POS;
		__builtin_avr_delay_cycles(delay);

		// two stop bits for good measure
		PORTC = NEG;
		__builtin_avr_delay_cycles(delay);
		__builtin_avr_delay_cycles(delay);
	}
}

int main(void)
{
	DDRB  = LED;

	DDRC  = POS | NEG;
	PORTC = NEG;

	while (1) {
		PORTB = LED;
		transmit(F_CPU / 9600);
		PORTB = 0;
		__builtin_avr_delay_cycles(F_CPU * 2);
	}
}
