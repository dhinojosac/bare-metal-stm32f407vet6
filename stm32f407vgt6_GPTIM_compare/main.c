//STM32F407VGT6
//LED PD15 blue
#include "stm32f4xx.h"                  // Device header

#define PORTD 3
#define PORTA 0

int main(void)
{
	//TODO: change pin PA5 to PD15
	RCC->AHB1ENR |= (1<<PORTA); 		// Enable clock to PortD
	GPIOA->MODER |= 0x800;					// Set PA5 to Alternate function TIM2
	GPIOA->AFR[0] |= 0x00100000;		// Set AFL to TIM2 CH1
	
	//TIM2 Config to 1Hz
	RCC->APB1ENR |= 1;							// Enable clock to TIM2 (32-bit)
	TIM2->PSC = 1600-1; 						// Prescaler 16Mhz/1600 = 10000
	TIM2->ARR = 10000-1;						// Auto-reload PSC/10000 = 1 Hz
	TIM2->CCMR1 = 0x30;							// Set output to toggle on match
	TIM2->CCR1  = 0 ;								// Set match mode
	TIM2->CCER  |= 1 ;							// Enable CH1 compare mode
	TIM2->CNT = 0;									// Clear counter
	TIM2->CR1 = 1;									// Enable TIM2
	
	while(1)
	{
	}

}
