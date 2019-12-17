#include "main.h"
#include "led.h"
#include "usart.h"
#define MYTXPIN 6
#define MYRXPIN 7

//Versuch 2 Code Vorbereitung
//Info
/*void outc(char c)
{
	putchar(c);
}*/

//5.3.1 initUsart
void initUsart(uint32_t baudrate)
{
	GPIO_TypeDef *gpioc = GPIOC; 				// Zeiger auf GPIOx Register
	USART_TypeDef *usart6 = USART6; 			// Zeiger auf USART6 Register

	// USART /Port Clocks
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; 		// GPIOC Clock enable
	RCC->APB2ENR |= RCC_APB2ENR_USART6EN;		// Usart6 Clock on

	//USART Sendeteil Konfiguration
	gpioc->MODER |= 0b10<<(2*MYTXPIN);			// Alternate Function enable
	gpioc->OSPEEDR |= 0b10<<(2*MYTXPIN); 		// I/O High Speed
	gpioc->PUPDR |= 0b00<<(2*MYTXPIN); 			// No PullUp/PullDown 3
	gpioc->AFR[0] |= 0b1000<<(4*MYTXPIN); 		// AF8 -> USART6/TX an PC6

	// USART Empfangsteil Konfiguration
	gpioc->PUPDR |= 0b01 << (2*MYRXPIN); 		// PullUp an
	gpioc->MODER |= 0b10<<(2*MYRXPIN); 			// Alternate function
	gpioc->AFR[0] |= 0b1000<<(4*MYRXPIN);		// AF8 -> USART6/RX an PC7
	// USART allgemein
	usart6->BRR = (SystemCoreClock/2)/baudrate; // ABP2 Clock base
	usart6->CR1 |= USART_CR1_TE| 				// Sendeteil einschalten
	USART_CR1_RE| 								// Empfangsteil einschalten
	USART_CR1_UE; 								// USART einschalten
}

//5.3.2 outc
void outc(char c) {
	USART_TypeDef *usart6 = USART6;
	while(!(USART6->ISR & USART_ISR_TXE)) { //wenn ISR und Senderegister ungleich null
	}
	usart6->TDR = c;		//
}

void outc_test()
{
	initUsart(9600);
	outc('H');
	outc('a');
	outc('l');
	outc('l');
	outc('o');
	outc('\n');
}

void newline()
{
	outc('\n');
	outc('\r');
}

//5.3.3 outs
void outs(char *s)  //siehe Skript Seite 5-7 Tabelle
{
	int i=0;
	while(1)
	{
		outc(s[i]);
		i++;
		if (s[i]=='\0')
		{
			break;
		}
	}
}

void outs_test()
{
	initUsart(9600);
	outs("Hello World!\n");
}

//5.3.5 outx4
void outx4(uint8_t n)
{
	n = n & 0x0f;
	if (n <= 9)
		n=n+48;
	else
		n=n+55;
	outc(n);
}

void outx4_test()
{
	initUsart(9600);
	uint8_t nibble = 0xF0;
	for (int i = 0; i<16; i++)
	{
		outx4(nibble+i);
	}
	outc('\n');
}

//5.3.6 outx8
void outx8(uint8_t b)
{
	uint8_t b1,b2;

	b1=(b & 0xF0)>>4;
	outx4(b1);

	b2=(b & 0x0F);
	outx4(b2);

}
void outx8_test()
{
	initUsart(9600);
	uint8_t byte = 0x90;
	for (int i = 0; i<32; i++)
	{
		outx8(byte+i);
		outc(' ');
	}
	outc('\n');
	outc('\r');
	for (int i = 0; i<16; i++)
	{
		outx8(15-i+(i<<4));
		outc(' ');
	}
	outc('\n');
	outc('\r');
}

//5.3.7 outx16

//	b= b & 0xF000;
//	b=b>>12;
//	outx4(b);
//
//	b= b & 0x0F00;
//	b=b>>8;
//	outx4(b);

void outx16_test()
{
	initUsart(9600);
	uint16_t word = 0xaa55;
	for (int i = 0; i<32; i++)
	{
		outx16(word+0x1111*i);
	}
	outc('\n');
}

//5.3.8 outi
void outi_test()
{
	initUsart(9600);
	for (int i = -10; i<=10; i++)
	{
		outi(i);
		outc(' ');
	}
	outc('\n');
	for (int i = -10; i<=10; i++)
	{
		outi(i);
		outc(' ');
		outi(i*i);
		outc(' ');
		outi(i*i*i);
		outc('\n');
	}
}

//Ende Versuch 2
