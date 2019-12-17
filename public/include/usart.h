#define MYTX 6
#define MYRX 7

void initUsart(uint32_t baudrate);
void newline();
void outc_test();
void outs_test();
void outx4_test();
void outx8_test();
void outx16_test();
void outc(char c);
void outs(char *s);
void outx4(uint8_t n);
void outx8(uint8_t b);
void outx16(uint16_t w);
void outi(int32_t i);
