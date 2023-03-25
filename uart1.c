#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "uart1.h"

#define UART_TX_MASK 2
#define UART_RX_MASK 1

void initUart1()
{
    SYSCTL_GPIOHBCTL_R = 0;

    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    GPIO_PORTB_DIR_R |= UART_TX_MASK;                   
    GPIO_PORTB_DIR_R &= ~UART_RX_MASK;                   
    GPIO_PORTB_DR2R_R |= UART_TX_MASK;                  
    GPIO_PORTB_DEN_R |= UART_TX_MASK | UART_RX_MASK;    
    GPIO_PORTB_AFSEL_R |= UART_TX_MASK | UART_RX_MASK;  
    GPIO_PORTB_PCTL_R &= ~(GPIO_PCTL_PB1_M | GPIO_PCTL_PB0_M); 
    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB1_U1TX | GPIO_PCTL_PB0_U1RX;

    UART1_CTL_R = 0;                                   
    UART1_CC_R = UART_CC_CS_SYSCLK;                   
    UART1_IBRD_R = 21;                                 
    UART1_FBRD_R = 45;                                  
    UART1_LCRH_R = UART_LCRH_WLEN_8 | UART_LCRH_FEN;   
    UART1_CTL_R = UART_CTL_TXE | UART_CTL_RXE | UART_CTL_UARTEN;
}

void putcUart1(char c)
{
    while (UART1_FR_R & UART_FR_TXFF);               
    UART1_DR_R = c;                                  
}

void putsUart1(char* str)
{
    uint8_t i = 0;
    while (str[i] != '\0')
        putcUart1(str[i++]);
}

char getcUart1()
{
    while (UART1_FR_R & UART_FR_RXFE);               
    return UART1_DR_R & 0xFF;                       
}

bool kbhitUart1()
{
    return !(UART1_FR_R & UART_FR_RXFE);
}
