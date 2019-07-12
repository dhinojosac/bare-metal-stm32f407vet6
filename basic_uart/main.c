//APB1ENR bit 17 : USART2
//USART connected to PA2

#include "stm32f4xx.h"                  // Device header

void USART2_Init(void);
void USART_write(int ch);
void delayMs(int delay);
	

int main(void)
{
	USART2_Init();
	
	while(1)
	{
		USART_write('H');
		USART_write('i');
		USART_write('\r');
		USART_write('\n');
		delayMs(1000);
	}
	
}

void USART2_Init(void)
{
	RCC->APB1ENR |= 0x20000; 	// Enable clock usart 2 in APB1
	RCC->AHB1ENR |= 1;    		// Enable clock fot PA
	
	GPIOA->AFR[0] = 0x0700;		// In AFRL set PA2 as AF7
	GPIOA->MODER  |= 0x0020; 	// Set PA2 to alternate function
	
	USART2->BRR = 0x0683;			// 9600 @16mHZ
	USART2->CR1 = 0x0008;			// Enable Tx
	USART2->CR1 |= 0x2000;		// Enable UART
}

void USART_write(int ch)
{
	// Wait while Tx buffer is empty
	while(!(USART2->SR & 0x0080))  
	{
		USART2->DR = (ch & 0xFF);
	}
}

void delayMs(int delay)
{
	int i;
	for(;delay>0;delay--)
	{
		for(i=0;i<3195;i++);
	}
}