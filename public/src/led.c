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
// //5.4.2
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

/*
uint8_t Tast1(){		// diese 4 funktionen trennen die einzelnen Schalter wieder von dem virtual switch port und geben diese aus
	uint8_t Taster1 = virtual_switch_port()&tast1hold;
	return (Taster1);}

 uint8_t Tast2(){
	uint8_t Taster2 = virtual_switch_port()&tast2hold;
	return (Taster2);}

 uint8_t Tast3(){
	uint8_t Taster3 = virtual_switch_port()&tast3hold;
	return (Taster3);}

 uint8_t Tast4(){
	uint8_t Taster4 = virtual_switch_port()&tast4hold;
	return (Taster4);}

 void Lauflicht_interrupt(int bisLed, int time){
// lauflicht läuft so lange bis s4 gedrückt wird, beim loslassen läuft es an der gleichen stelle weiter

	 int8_t Leds=0b00000000;
	 	 	int i;
	 	 	 for(i=0;i<bisLed;i++){
	 	 	  if(Tast4()==tast4hold){i--;}
	 	 	  else
	 	 	 virtual_Led(Leds=0b10000000>>i);
	 	 	 HAL_Delay(time);
	 	 	 	 }
	 	 	 	 }
 
 void display_led(int number,uint32_t color){	//Zeichnet ein Rechteck auf das Display
	  	uint16_t rectSize = 40;					//größe ist 40Pixel
	 	uint16_t displayX  = BSP_LCD_GetXSize()/5;	//teilt das Display durch 5

	 	uint16_t rectX    =0 + number*displayX-(rectSize/2);	//anhand des wertes in "number" wird das rechteck an eine bestimmte position verschoben
	 	uint16_t rectY    =0+rectSize;							//rückt die rechtecke ein um den wert rectSize, nach unten
	 	BSP_LCD_SetTextColor(color);							//setzt die Farbe die in color übergeben wird
	 	BSP_LCD_FillRect(rectX, rectY, rectSize, rectSize); //fill with textcolor
	 	}

 void usart_command(int number){	//funtion gibt über die Usart schnittstelle eine entsprechende meldung aus

	if (number==1){outs("UP\n");}
	if (number==2){outs("DOWN\n");}
	if (number==3){outs("STEP\n");}
	if (number==4){outs("STOP\n");}

 }
 void step_variabel(int counter){	//gibt ebenfalls über die Usart schnittstelle aus. wird bei 5 zurück auf 1 gesetzt
	 outs("Step*");
	 outi(counter);
	 outs("\n");
 }

 void Taster_LED(uint32_t Color, uint32_t colorpush){	//Hauptfunktion von Versuch 2&3
	 int k=0,l=0,m=0,n=0,counter=1;
	 while(1){
		 //Erläuterung
		 //Wenn Tast1 oder das entsprechende Feld im Display betätigt wird, ändert sich die Farbe des Rechtecks auf
		 //die in "colorpush" entsprechende Farbe und gibt einmal über die USART Schnittstelle das Kommando aus
		 //dies ist bei allen gleich ausser bei Step Variabel, dieser verfügt über einen Counter und zählt bis 5
		if(Tast1()!=0||check_LED_area()==1){
			display_led(1,colorpush);
			if(k==0){
				usart_command(1);}
				k++;
			}
		else{
			display_led(1,Color);
			k=0;
		}
		if(Tast2()!=0||check_LED_area()==2){
			display_led(2,colorpush);
			if(l==0){
				usart_command(2);}
				l++;
			}
		else{
			display_led(2,Color);
			l=0;
		}
		if(Tast3()!=0||check_LED_area()==3){
			display_led(3,colorpush);
			if(m==0){
				step_variabel(counter);
				counter++;
			}
			if(counter>5){
				counter=1;}
				m++;
			}
			else{
				display_led(3,Color);
				m=0;
			}
			if(Tast4()!=0||check_LED_area()==4){
				display_led(4,colorpush);
				if(n==0){
					usart_command(4);
				}
				n++;
			}
			else{
				display_led(4,Color);
				n=0;
			}
		check_touch_panel();
	 }

 }
*/

//5.4.5 Touchpanel-------------------------------------------------------------------------------
/*int check_LED_area(){
		int TouchX; // X Position aller Beruehrungen
		int TouchY; // Y Postitioin aller Beruehrungen
		int i;                                                                   
		int Touch;
		TS_StateTypeDef touchState;
		BSP_TS_GetState(&touchState);
		TouchX=(int)touchState.touchX[0];		//wandelt die werte in Integer um
		TouchY=(int)touchState.touchY[0];		//wandelt die werte in Integer um
		if (TouchY>=40&&TouchY<=80){			//abfrage ob die Beruehrungen in einem 40Pixel breiten streifen von 40bis80 Pixel ist
			for(i=1;i<=4;i++){					//for Schleife um die einzelnen Leds abzufragen.
				uint16_t rectSize = 40;
				uint16_t displayX  = BSP_LCD_GetXSize()/5;
			 	uint16_t rectX    =0 + i*displayX-(rectSize/2);
			 	if(TouchX>=rectX && TouchX<=(rectX+rectSize)){return i;}
			 	else{Touch=0;}
			}
		}
return Touch;		//gibt die gedrückte LED als Zahl 1-4 aus, kein druck erzeugt eine 0
}       */

//void check_touch_panel()
//{	//testfunktion des Tochdisplays
//	char formatString[] = "X=%3d, Y=%3d, S=%3d #=%3d";
//	const int bufSIZE = 100;
//	char outString[bufSIZE];
//	TS_StateTypeDef touchState;
//
//	if ((BSP_TS_GetState(&touchState) == TS_OK) && (touchState.touchDetected))
//	{
//		draw_text_center("TOUCH");
//		char outString[100];
//		snprintf(outString, bufSIZE, formatString,
//				(int)touchState.touchX[0], (int)touchState.touchY[0],
//				(int)touchState.touchWeight[0], touchState.touchDetected);
//		draw_text_bottom(outString);
//	} else
//	{
//		draw_text_center("     ");
//		snprintf(outString, bufSIZE, formatString, -1, -1, -1, 0);
//		draw_text_bottom(outString);
//	}
//}


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

// ----------------------------------------------------------------------------
//Thema 6.3.1 ADC Initialisierung und Test

/*um boolsche Variablen (true und false)mit C zu nutzen wurde 
in led.h einen Typedef undsigned char bool, 
#define true 1 und #define false 0 eingeführt */

//6.3.1.1 Initialisierung und Start-----------------
/*
void init_adc(bool single_shot) //noch in die led.h rein
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 						// GPIOA clock an
	GPIOA->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1; 	// Analog Mode

	RCC->APB2ENR |= RCC_APB2ENR_ADC3EN; 						//clock ADC3 an
	ADC->CCR  |= ADC_CCR_ADCPRE_0; 								// Clock auf Teiler vier
	ADC3->CR2 |= ADC_CR2_ADON;    								// ADC an, dauert bis aktiv.
	ADC3->CR1 |= ADC_CR1_RES_1;   								// 0b10 -> 8 Bit Aufloesung
	//ADC3->CR2 |= ADC_CR2_ALIGN;								// Linksbuendig abspeichern
	if(single_shot==false)
	{
		ADC3->CR2 |= ADC_CR2_CONT;    
	}	// Staendig wandeln
	else
	{
		ADC3->CR2|=ADC_CR2_DDS;
	}	//Single shot mode

}

void start_adc() //noch in die led.h rein
{
	ADC3->CR2 |= ADC_CR2_SWSTART; 			// Start der Wandlung(en)
}
//--------------------------------------------------
//6.3.1.2 Umrechnung in mV--------------------------
uint16_t adc_get() //noch in die led.h rein
{	// mit dieser funktion wird der aktuelle wert des adc in einen integer 
	//geschrieben und mit return ausgegeben
	int adress = (ADC3->DR&0xff);
	return adress;
}

int adc_in_millivolt(uint16_t adc_value){	//nutzt die adc_get um dann den wert in mV auszugeben
	uint16_t value=3300*adc_value/255;	// adc_value wird mit 3300 multipliziert und durch 255 geteilt
	return value;
}//noch in die led.h rein
//--------------------------------------------------

//6.3.4 Abtastung
//6.3.4.4 Bildung des gleitenden Mittelwerts
void init_Timer2() //noch in die led.h rein
{											// Enable Timer 5
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 	// Timer Clock an
	TIM2->PSC = 10000; 						// Vorteiler an
	TIM2->ARR = 5000; 						// Obere Grenze
}
//--------------------------------------------------
*/
