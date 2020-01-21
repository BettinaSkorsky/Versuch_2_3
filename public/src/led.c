//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//
#include "led.h"
#include "usart.h"
//4.3.3 Virtueller Port
void virtual_led_init()
{
	configure_ports_output(8,0b111);			//8=I
	configure_ports_output(5,0b11111000000);	//5=F
}
// 4.3.5 Input Initialisierung
void init_port_input (int gpioNumber, int pinNumber){
	GPIO_TypeDef *gpio=GPIOI;
	RCC->AHB1ENR |= (1<<gpioNumber);
	gpio->MODER|=0b00<<(2*pinNumber);
	gpio->OTYPER|= 0b00;
	gpio->OSPEEDR|= 0b00;
	gpio->PUPDR|= 0b00;
}
void configure_ports_input (int gpioNumber, uint16_t PinMask)
{
	unsigned int pinPosition =0;
	while (PinMask)
	{
		if (1 & PinMask)
		{								//Test auf unterstes Bit gesetzt
			init_port_input (gpioNumber, pinPosition);		//Initialisierung mit init_port_input
		}
		PinMask = PinMask>>1;							//pinMask um eine Stelle nach rechts schieben
		pinPosition++;
	}
}
GPIO_TypeDef *get_gpio_adress(unsigned int gpioNumber)
{
	GPIO_TypeDef *gpio =AHB1PERIPH_BASE + gpioNumber*0x400;
	return gpio;
}
uint8_t virtual_switch_port(){
	GPIO_TypeDef *gpio=get_gpio_adress(1);
	uint16_t Schalter;
	Schalter = gpio->IDR;
	Schalter = ((Schalter & 0x300)>>8)|((Schalter & 0xc000)>>12);
	return Schalter;
}
//5.4.2
void display_LED(int number, uint32_t color)
{
	uint16_t rectSize = 50;
	uint16_t leftX= BSP_LCD_GetXSize()*number;
	uint16_t centerY= BSP_LCD_GetYSize()/4;
	uint16_t rectX= leftX-rectSize*number;
	uint16_t rectY= centerY-rectSize/2;
	BSP_LCD_SetTextColor(color);
	BSP_LCD_FillRect(rectX, rectY, rectSize, rectSize); //fill with textcolor

}

//5.4.5

/*void check_touch_panel() {
BSP_TS_INIT(480,276);
char formatString[] = "X=%3d, Y=%3d, S=%3d #=%3d";
const int bufSIZE = 100;
char outString[bufSIZE];
TS_StateTypeDef touchState;
if ((BSP_TS_GetState(&touchState) == TS_OK) && (touchState.touchDetected)){
draw_text_center("TOUCH");
char outString[100];
snprintf(outString, bufSIZE, formatString,
(int)touchState.touchX[0], (int)touchState.touchY[0],
(int)touchState.touchWeight[0], touchState.touchDetected);
draw_text_bottom(outString);
} else {
draw_text_center(" ");
snprintf(outString, bufSIZE, formatString, -1, -1, -1, 0);
draw_text_bottom(outString);
}
} */
