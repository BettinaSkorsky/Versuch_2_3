
#include "main.h"
#include "led.h"
#include "usart.h"
//5.4.1
void draw_rect_center()
{
	uint16_t rectSize = 100;
	uint16_t centerX  = BSP_LCD_GetXSize()/2;
	uint16_t centerY  = BSP_LCD_GetYSize()/2;
	uint16_t rectX    = centerX-rectSize/2;
	uint16_t rectY    = centerY-rectSize/2;
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_FillRect(rectX, rectY, rectSize, rectSize); //fill with textcolor
}
void draw_text_center(char *text)
{
	uint16_t centerX  = BSP_LCD_GetXSize()/2;
	uint16_t centerY  = BSP_LCD_GetYSize()/2;
	sFONT *textFont   = &Font16;
	uint16_t textH    = textFont->Height;
	uint16_t textW    = textFont->Width*strlen(text);
	BSP_LCD_SetFont(textFont);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
	BSP_LCD_DisplayStringAt(centerX-textW/2,centerY-textH/2, (uint8_t *)text, LEFT_MODE);
}
void draw_text_2(int number, char *text)
{
	uint16_t centerX  = BSP_LCD_GetXSize()*number;
	uint16_t centerY  = BSP_LCD_GetYSize()/2;
	sFONT *textFont   = &Font16;
	uint16_t textH    = textFont->Height;
	uint16_t textW    = textFont->Width*strlen(text);
	BSP_LCD_SetFont(textFont);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
	BSP_LCD_DisplayStringAt(centerX-textW*number,centerY-textH/2, (uint8_t *)text, LEFT_MODE);
}

/*
//Thema 6.3.1 ADC Initialisierung und Test

//6.3.1.1 Initialisierung und Start
void init_ADC()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 						// GPIOA clock an
	GPIOA->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1; 	// Analog Mode

	RCC->APB2ENR |= RCC_APB2ENR_ADC3EN; 						//clock ADC3 an
	ADC->CCR  |= ADC_CCR_ADCPRE_0; 								// Clock auf Teiler vier
	ADC3->CR2 |= ADC_CR2_ADON;    								// ADC an, dauert bis aktiv.
	ADC3->CR1 |= ADC_CR1_RES_1;   								// 0b10 -> 8 Bit Aufloesung
	ADC3->CR2 |= ADC_CR2_ALIGN;							  		// Linksbuendig abspeichern
	ADC3->CR2 |= ADC_CR2_CONT;    								// Staendig wandeln
	ADC3->CR2 |= ADC_CR2_SWSTART; 								// Start der Wandlung(en)
}
*/

int main(void)
{
	configure_ports_input(1, 0xc300);
//5.4.1
	LCD_LOG_DeInit();
	BSP_LCD_Init();
	BSP_LCD_Clear(LCD_COLOR_YELLOW);
//    outs("UP");
//    outs("DOWN");
//    outs("STEP n");
//    outs("STOP");
    //draw_rect_center();
    //draw_text_center("Hallo MIT Labor!");
	display_LED(2, LCD_COLOR_GREEN);
	display_LED(4, LCD_COLOR_GREEN);
	display_LED(6, LCD_COLOR_GREEN);
	display_LED(8, LCD_COLOR_GREEN);
	draw_text_2(2, "STOP");
	draw_text_2(8, "STEP n ="); //n ausgeben fehlt
	draw_text_2(18,"UP");
	draw_text_2(7, "DOWN");
//    outc_test();
//    outc('\r');
//    newline();
//    outs_test();
//    outx4_test();
//    outx8_test();
//    outx16_test();
//    outi_test();

/*
//6.3.1.1 Initialisierung und Start-----------
	init_adc(false);
	//initialisiert den adc, false bedeutet er befindet sich im continius...
	//...mode und true bedeutet er ist im single shot modus
	start_adc();
	//startet die wandlung, im Single shot modus bedeutet das das nur...
	//...einmal gewandelt wird bis die funktion erneut aufgerufen wird
	//--------------------------------------------
	HAL_Delay(2000);
	BSP_LCD_Clear(LCD_COLOR_BLUE);
*/
		int i=0, n=1;
	while(1)
	{
		/*
		//6.3.2 Interrupt
		char buffer[20];
		snprintf(buffer, sizeof(buffer),"%5d:%2d.%02dV\n", time_ref/1000, value/1000, (value%1000)/10);
		//schreibt den aktuellen wert des adc in der form "tt 0.00V"

		draw_text_center(buffer);		//gibt den char auf das Display aus

		//es wird eine bitmaske generiert mithilfe sich eine "analoge Anzeige" darstellen lässt
		uint8_t Dioden=0xff<<adc_get()/32;
		//zuerst werden 8 bit zu 1, dadurch das der Integer unsigned ist werden nullen nachgezogen beim verschieben,
		//es wird jeweils um die entsprechenden stellen verschoben
		virtual_Led(~Dioden);
		// nutzt die Funktion virtual_Led und negiert den uint8_t

		//6.3.3 Synchronisation mit dem Timer
		int time_ref = HAL_GetTick();
		//Funktion um eine Referenzzeit zu bilden die mit abgebildet wird
		int value = adc_in_millivolt(adc_get());
		// in value wird der aktuelle wert des adc gespeichert	durch aufruf der beiden funktionen
		*/

		//5.4.2
		/*if ((virtual_switch_port() & 0b0001) == 0) 	//S1
			display_LED(2, LCD_COLOR_RED);
		if ((virtual_switch_port() & 0b0010) == 0)    	//S2
			display_LED(4, LCD_COLOR_RED);
		if ((virtual_switch_port() & 0b0100) == 0)   	//S3
			display_LED(6, LCD_COLOR_RED);
		if ((virtual_switch_port() & 0b1000) == 0)     //Button1... S4
//		display_LED(8, LCD_COLOR_RED);*/

//5.4.3
	if ((virtual_switch_port() & 0b0001) == 0) //S1
		display_LED(2, LCD_COLOR_RED);
		HAL_Delay(100);
	if ((virtual_switch_port() & 0b0010) == 0)    //S2
		display_LED(4, LCD_COLOR_RED);
		HAL_Delay(100);
	if ((virtual_switch_port() & 0b0100) == 0){    //S3
		display_LED(6, LCD_COLOR_RED);
		HAL_Delay(100);
		n+=5;i++;
		outi(&n);}
	if ((virtual_switch_port() & 0b1000) == 0)     //Button1... S4
		display_LED(8, LCD_COLOR_RED);
		HAL_Delay(100);
	if ((virtual_switch_port() & 0b0000) == 0)
		display_LED(2, LCD_COLOR_GREEN);
		display_LED(4, LCD_COLOR_GREEN);
		display_LED(6, LCD_COLOR_GREEN);
		display_LED(8, LCD_COLOR_GREEN);
	if (i=4)
		n=1;
	}
//5.4.4
		draw_text_2(2, "STOP");
		draw_text_2(8, "STEP n ="); //n ausgeben fehlt
		draw_text_2(18,"UP");
		draw_text_2(7, "DOWN");
//5.4.5

    //int check_LED_area();
}



