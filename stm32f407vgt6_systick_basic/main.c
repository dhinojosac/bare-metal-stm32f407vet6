//STM32F407VGT6
//LED PD15 blue
#include "stm32f4xx.h"                  // Device header

#define PORTD 3
int main(void)
{
	RCC->AHB1ENR |= (1<<PORTD); 		// Enable clock to PortD
	GPIOD->MODER |= 0x40000000;			// Set PD15 as output
	GPIOD->BSRR  |= 0x80000000; 		// Clear PD15 
	GPIOD->BSRR  |= 0x8000; 				// Set PD15 
	
	//Configure Systick to generate 200ms delay
	SysTick->LOAD = 3200000 - 1;  	// (1/16Mhz)*3200000 = 0.2
	SysTick->VAL  = 0;							// Set value
	SysTick->CTRL	= 5;  						//select processor clock and enable counter
	
	while(1)
	{
		if(SysTick->CTRL & 0x10000) 		// Check if count flag is set
		{
			GPIOD->ODR  ^= 0x8000; 				// Toggle LED PD15
		}
	}
	
}