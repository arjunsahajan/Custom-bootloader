#ifndef UART0_H_
#define UART0_H_

void initUart0(void);
void putcUart0(char c);
void putsUart0(char* str);
char getcUart0(void);
bool kbhitUart0(void);

#endif
