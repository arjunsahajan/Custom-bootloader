#ifndef UART1_H_
#define UART1_H_

void initUart1(void);
void putcUart1(char c);
void putsUart1(char* str);
char getcUart1(void);
bool kbhitUart1(void);

#endif
