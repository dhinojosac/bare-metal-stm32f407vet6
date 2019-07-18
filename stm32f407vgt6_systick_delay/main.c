//STM32F407VGT6
//LED PD15 blue
#include "stm32f4xx.h"                  // Device header

#define PORTD 3

void systickDelayMs(int n);

int main(void)
{
	RCC->AHB1ENR |= (1<<PORTD); 		// Enable clock to PortD
	GPIOD->MODER |= 0x40000000;			// Set PD15 as output
	GPIOD->BSRR  |= 0x80000000; 		// Clear PD15 
	GPIOD->BSRR  |= 0x8000; 				// Set PD15 
	
	while(1)
	{
		systickDelayMs(500);					// SysTick delay
		GPIOD->ODR  ^= 0x8000; 				// Toggle LED PD15
	}
}

void systickDelayMs(int n)
{
	//Configure Systick 
	SysTick->LOAD = 16000 - 1;  	// (1/16Mhz)*16000 = 0.001 ms
	SysTick->VAL 	= 0;						// Clear current value register
	SysTick->CTRL	= 5;  					//select processor clock and enable counter
	
	for(int i=0; i<n; i++)				// 1 ms for cycle
	{
		while((SysTick->CTRL & 0x10000)==0){}; //wait until the COUNT flag is set
	}
	SysTick->CTRL = 0;
}