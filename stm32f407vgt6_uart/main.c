//STM32F407VGT6  
//APB1ENR bit 17 : USART2
//USART connected to TX PA2 and RX PA3
//LED LD4 PD12 green
//		LD3 PD13 orange
//		LD5 PD14 red
//		LD6 PD15 blue


#include "stm32f4xx.h"                  // Device header
#include <stdio.h>

void USART2_Init(void);
int USART2_write(int ch);
char USART2_read(void);
void delayMs(int delay);
void LED_play(int value);

// Wrapping to use printf
struct __FILE
{
	int handle;
};

FILE __stdin  = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f)
{
	int c;
	c = USART2_read();
	/*
	if(c == '\r')
	{
		USART2_write(c);
		c='\n';
	}
	USART2_write(c);
	*/
	
	return c;
}

int fputc(int c, FILE *f)
{
	return USART2_write(c);
}

// end wrapping printf

int main(void)
{
	RCC->AHB1ENR |= (1<<3); 			// Enable clock to PortD
	GPIOD->MODER |= 0x40000000; 	// Set pin PD15 as output
	
	GPIOD->BSRR = 0x8000; 				// Turn on LED PD15 
	delayMs(100);
	GPIOD->BSRR = 0x80000000; 		// Turn off LED PD15 
	
	USART2_Init();								// Init USART2
	
	char ch;	
	
	int n;
	char str[100];
	
	printf("Hello world printf\r\n");
	fprintf(stdout, "test for stdout\r\n");
	fprintf(stderr, "test for stderr\r\n");
	
	while(1)
	{
		printf("How old are you?\r\n");
		scanf("%d",&n);
		printf("You age is: %d\r\n",n);
		printf("Enter your first name:");
		gets(str);
		printf("I like your style ");
		puts(str);
		printf("\r\n");
	}
	
	/*
	while(1)	
	{
		ch = USART2_read();
		USART2_write(ch);
		
		if(ch=='\n')
		{
			LED_play(ch);
		}
	}
	*/

	return 0;
}

	
void USART2_Init(void)
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
	GPIOA->AFR[0] |= (0x7 << 8); 	// for pin 2
	GPIOA->AFR[0] |= (0x7 << 12); // for pin 3

	
	USART2->CR1 |= (1 << 3);	// usart2 tx enable, TE bit 3
	USART2->CR1 |= (1 << 2);	// usart2 rx enable, RE bit 2

	USART2->BRR = 0x008B;  		//115200 baudrate @16Mhz

	// enable usart2 - UE, bit 13
	USART2->CR1 |= (1 << 13);
}

char USART2_read(void)
{
	while(!(USART2->SR & 0x0020)){} // wait until char arrives
	return USART2->DR;
}

int USART2_write(int ch)
{
	while(!(USART2->SR & 0x0080)){} // wait while TX buffer is empty
	USART2->DR = (ch & 0xFF);
	return ch;
}

void LED_play(int value)
{
	GPIOD->BSRR = 0x8000; 		//Turn LED on
	delayMs(10);
	GPIOD->BSRR = 0x80000000; //Turn LED off
	delayMs(10);
}

void delayMs(int delay)
{
	int i;
	for(;delay>0;delay--)
	{
		for(i=0;i<3195;i++);
	}
}
