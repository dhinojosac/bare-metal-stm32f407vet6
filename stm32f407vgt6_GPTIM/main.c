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
	
	//TIM2 Config to 1Hz
	RCC->APB1ENR |= 1;							// Enable clock to TIM2 (32-bit)
	TIM2->PSC = 1600-1; 						// Prescaler 16Mhz/1600 = 10000
	TIM2->ARR = 10000-1;						// Auto-reload PSC/10000 = 1 Hz
	TIM2->CNT = 0;									// Set counter
	TIM2->CR1 = 1;									// Enable TIM2
	
	while(1)
	{
		while(!(TIM2->SR & 1)){}
		TIM2->SR &= ~1;
			GPIOD->ODR ^= 0x8000; //Toggle LED PD15
	}

}
