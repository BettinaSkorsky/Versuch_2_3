#include "main.h"
#include "led.h"
#include "usart.h"

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

int main(void)
{
	LCD_LOG_DeInit();

	BSP_LCD_Init();

	BSP_LCD_Clear(LCD_COLOR_YELLOW);
	draw_rect_center();
	draw_text_center("Hallo MIT Labor!");

//	outc_test();
//	outc('\r');
//	newline();
//	outs_test();
//	outx4_test();
//	outx8_test();
//	outx16_test();
	outi_test();
}

