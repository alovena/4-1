//Proteus 8 전구 깜빡이는 코드 * 카페 참조가능
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL
#include <util/delay.h>

unsigned char cnt = 0;
int main()
{
	// Write your code here
	DDRD = 0xff;
	DDRA = 0xff;
	char k;
	while (1)
	{
		if (cnt % 2 == 0) {
			PORTD = cnt;
			cnt++;
			_delay_ms(1000);
			//짝수 
		}
		else {
			PORTA = 255 - cnt;
			cnt++;
			_delay_ms(1000);
			//홀수 dn
		}
		/*
		PORTA = ~PORTA;
		_delay_ms(200);

		PORTD = 0x55;
		_delay_ms(200);
		PORTD = 0xaa;
		_delay_ms(200); //밀리터리 세컨드
		_delay_us(500); //마이크로 세컨드
		*/

	}
	return 0;
}
