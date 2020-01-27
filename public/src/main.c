
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
		int i=0, n=1;
	while(1)
	{	 //5.4.2
		if ((virtual_switch_port() & 0b0001) == 0) 	//S1
			display_LED(2, LCD_COLOR_RED);
		if ((virtual_switch_port() & 0b0010) == 0)    	//S2
			display_LED(4, LCD_COLOR_RED);
		if ((virtual_switch_port() & 0b0100) == 0)   	//S3
			display_LED(6, LCD_COLOR_RED);
		if ((virtual_switch_port() & 0b1000) == 0)     //Button1... S4
		display_LED(8, LCD_COLOR_RED);
    }
//5.4.3
	if ((virtual_switch_port() & 0b0001) == 0) //S1
		display_LED(2, LCD_COLOR_RED);
	if ((virtual_switch_port() & 0b0010) == 0)    //S2
		display_LED(4, LCD_COLOR_RED);
	if ((virtual_switch_port() & 0b0100) == 0){    //S3
		n+=5;i++;outi(n);}
	if ((virtual_switch_port() & 0b1000) == 0)     //Button1... S4
		display_LED(8, LCD_COLOR_RED);

	if (i=4) n=1;
	else
	{
		HAL_Delay(100);
		display_LED(2, LCD_COLOR_GREEN);
		HAL_Delay(100);
		display_LED(4, LCD_COLOR_GREEN);
		HAL_Delay(100);
		display_LED(6, LCD_COLOR_GREEN);
		HAL_Delay(100);
		display_LED(8, LCD_COLOR_GREEN);
		HAL_Delay(100);
	}
//5.4.4
		draw_text_2(2, "STOP");
		draw_text_2(8, "STEP n ="); //n ausgeben fehlt
		draw_text_2(18,"UP");
		draw_text_2(7, "DOWN");
//5.4.5
    
    //int check_LED_area();
}


