//APB1ENR bit 17 : USART2
//USART connected to PA2

#include "stm32f4xx.h"                  // Device header

void USART2_Init(void);
void USART_write(int ch);
void delayMs(int delay);
	

int main(void)
{
	// enable USART2 clock, bit 17 on APB1ENR
	RCC->APB1ENR |= (1 << 17);

	// enable GPIOA clock, bit 0 on AHB1ENR
	RCC->AHB1ENR |= (1 << 0);

	// set pin modes as alternate mode 7 (pins 2 and 3)
	GPIOA->MODER &= 0xFFFFFF0F; // Reset bits 10-15 to clear old values
	GPIOA->MODER |= 0x000000A0; // Set pin 2/3 to alternate func. mode (0b10)

	// set pin modes as high speed
	GPIOA->OSPEEDR |= 0x000000A0; // Set pin 2/3 to high speed mode (0b10)

	// choose AF7 for USART2 in Alternate Function registers
	GPIOA->AFR[0] |= (0x7 << 8); // for pin 2
	GPIOA->AFR[0] |= (0x7 << 12); // for pin 3

	// usart2 word length M, bit 12
	//USART2->CR1 |= (0 << 12); // 0 - 1,8,n

	// usart2 parity control, bit 9
	//USART2->CR1 |= (0 << 9); // 0 - no parity

	// usart2 tx enable, TE bit 3
	USART2->CR1 |= (1 << 3);

	// usart2 rx enable, RE bit 2
	USART2->CR1 |= (1 << 2);


	USART2->BRR = 0x008B;

	// enable usart2 - UE, bit 13
	USART2->CR1 |= (1 << 13);

	const uint8_t brand[] = "testing uart\n\r";

	while(1)
	{
		for (uint32_t i=0; i<sizeof(brand); i++){
			// send character
			USART2->DR = brand[i];
			// wait for transmit complete
			while(!(USART2->SR & (1 << 6)));
			// slow down
			for(int i=0; i<1000000; i++);
		}
	}

	return 0;
}