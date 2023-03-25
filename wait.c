#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "wait.h"


void waitMicrosecond(uint32_t us)
{
	__asm("WMS_LOOP0:   MOV  R1, #3");          
    __asm("WMS_LOOP1:   SUB  R1, #1");         
    __asm("             CBZ  R1, WMS_DONE1");   
    __asm("             NOP");                  
    __asm("             NOP");                 
    __asm("             B    WMS_LOOP1");       
    __asm("WMS_DONE1:   SUB  R0, #1");          
    __asm("             CBZ  R0, WMS_DONE0");   
	__asm("             NOP");                  
    __asm("             B    WMS_LOOP0");       
    __asm("WMS_DONE0:");                        
                                                
}
