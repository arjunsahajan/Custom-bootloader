#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "uart0.h"

#define UART_TX_MASK 2
#define UART_RX_MASK 1

void initUart0()
{
    SYSCTL_GPIOHBCTL_R = 0;

    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

    GPIO_PORTA_DIR_R |= UART_TX_MASK;              
    GPIO_PORTA_DIR_R &= ~UART_RX_MASK;                  
    GPIO_PORTA_DR2R_R |= UART_TX_MASK;                  
    GPIO_PORTA_DEN_R |= UART_TX_MASK | UART_RX_MASK;    
    GPIO_PORTA_AFSEL_R |= UART_TX_MASK | UART_RX_MASK;  
    GPIO_PORTA_PCTL_R &= ~(GPIO_PCTL_PA1_M | GPIO_PCTL_PA0_M); 
    GPIO_PORTA_PCTL_R |= GPIO_PCTL_PA1_U0TX | GPIO_PCTL_PA0_U0RX;

    UART0_CTL_R = 0;                                
    UART0_CC_R = UART_CC_CS_SYSCLK;                   
    UART0_IBRD_R = 21;                                 
    UART0_FBRD_R = 45;                                
    UART0_LCRH_R = UART_LCRH_WLEN_8 | UART_LCRH_FEN;  
    UART0_CTL_R = UART_CTL_TXE | UART_CTL_RXE | UART_CTL_UARTEN;
}

void putcUart0(char c)
{
    while (UART0_FR_R & UART_FR_TXFF);             
    UART0_DR_R = c;                                  
}

void putsUart0(char* str)
{
    uint8_t i = 0;
    while (str[i] != '\0')
        putcUart0(str[i++]);
}

char getcUart0()
{
    while (UART0_FR_R & UART_FR_RXFE);             
    return UART0_DR_R & 0xFF;                     
}

bool kbhitUart0()
{
    return !(UART0_FR_R & UART_FR_RXFE);
}
