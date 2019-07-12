// led D2(PA6) and D3(PA7)
// button K0(PE4) and K1(PE3)

#include "stm32f4xx.h"                  // Device header

void delay_ms(int delay);

int main(void)
{
  RCC->AHB1ENR |= 0x01;                     // enable GPIOA clock
	RCC->AHB1ENR |= 0x10;                     // enable GPIOE clock
	
  GPIOA->MODER |= 0x4000;                		// set GPIO PA7 as output;
	// 0b 0100 0000 0000 0000
	GPIOA->MODER |= 0x1000;                		// set GPIO PA6 as output;
	// 0b 0001 0000 0000 0000
	
  while(1)
  {
		
		if(GPIOE->IDR & 0x10) //if K0 button is high 
		{
			GPIOA->BSRR |=  0x400000;        			// set PA6  (BR7 of BSRR) HIGH
		}else{
			GPIOA->BSRR |=  0x40;             		// set PA6  (BS7 of BSRR) LOW
		}
		
		
		/*
    GPIOA->BSRR |=  0x800000;        			// reset PA7 (BR7 of BSRR) (on STM32F4VE board is HIGH)
		delay_ms(500);
    GPIOA->BSRR |=  0x80;             		// set PA7 (BS7 of BSRR) (on STM32F4VE board is LOW)
    delay_ms(100);
		*/
		
  }
}

void delay_ms(int delay)
{
  int i;
  for(; delay>0; delay--)
  {
    for(i=0; i<3195; i++);
  }
}
