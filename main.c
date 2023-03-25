#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clock.h"
#include "tm4c123gh6pm.h"
#include "wait.h"
#include "uart0.h"
#include "uart1.h"
#include "loader_apis.h"

char debug_msg[DEBUG_MSG_MAX_SIZE];

void (*app_rst_handler_ptr) (void);

int main(void)
{
	uint32_t app_rst_handler_addr;
	uint32_t msp_val;
	IMAGE image;
	
	initHw();
	initUart0();
	initUart1();
	
	sprintf(debug_msg, "\rDEBUG_LOG: ************ CUSTOM BOOTLOADER REV1 ************\n");
	putsUart0(debug_msg);
	
	sprintf(debug_msg, "\rDEBUG_LOG: Initialization of hardware done. In main()\n");
	putsUart0(debug_msg);

	GPIO_PORTF_DATA_R |= RED_LED_MASK;
	waitMicrosecond(1000000);
	GPIO_PORTF_DATA_R &= ~RED_LED_MASK;
	waitMicrosecond(1000000);
	GPIO_PORTF_DATA_R |= RED_LED_MASK;
	
	sprintf(debug_msg, "\rDEBUG_LOG: Getting Header info\n");
	putsUart0(debug_msg);	
	get_header(&image);
	
	if(!check_app_size(&image))
	{
		while(1);
	}
	
	check_hash_check_feature(&image);
	
	sprintf(debug_msg, "\rDEBUG_LOG: Getting application firmware\n");
	putsUart0(debug_msg);	
	get_app_firmware(&image);
		
	if(image.hash_check_flag)
	{
		if(!check_app_hash(&image))
		{
			check_wdt_feature(&image);
			
			if(image.wdt_check_flag)
			{
				configure_watch_dog();
			}
			else
			{
				issue_software_reset();
			}
		}
	}

	sprintf(debug_msg, "\rDEBUG_LOG: Erasing flash\n");
	putsUart0(debug_msg);	
	erase_flash_app_area();

	sprintf(debug_msg, "\rDEBUG_LOG: Writing app to flash\n");
	putsUart0(debug_msg);
	write_app_to_flash(&image);
	
	sprintf(debug_msg, "\rDEBUG_LOG: Waiting for button press\n");
	putsUart0(debug_msg);

    waitPbPress();
    
	sprintf(debug_msg, "\rDEBUG_LOG: Button pressed\n");
	putsUart0(debug_msg);
    
    GPIO_PORTF_DATA_R &= ~RED_LED_MASK;
    
    sprintf(debug_msg, "\rDEBUG_LOG: UnInit hardware. Jumping to application firmware\n");
    putsUart0(debug_msg);
    
    sprintf(debug_msg, "\rDEBUG_LOG: Application flash base address: 0x%x\n", FLASH_APP_BASE_ADDR);
    putsUart0(debug_msg);
    
    sprintf(debug_msg, "\rDEBUG_LOG: Application reset handler address: 0x%x\n", FLASH_APP_RESET_HANDLER_ADDR);
    putsUart0(debug_msg);
    
    waitMicrosecond(100000);
    
    uninit_hardware();   
   
   	NVIC_VTABLE_R = FLASH_APP_BASE_ADDR;
   
   	msp_val = * (uint32_t *) FLASH_APP_BASE_ADDR;
   	__asm("MSR MSP, %0;" :: "r" (msp_val));
   
  	app_rst_handler_addr = * (uint32_t *) (FLASH_APP_RESET_HANDLER_ADDR);
  	app_rst_handler_ptr = (void *) app_rst_handler_addr;	
  	
  	app_rst_handler_ptr();
}
