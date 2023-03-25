#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include "clock.h"
#include "tm4c123gh6pm.h"
#include "wait.h"
#include "uart0.h"
#include "uart1.h"
#include "loader_apis.h"
#include "sha256.h"

extern char debug_msg[DEBUG_MSG_MAX_SIZE];

void waitPbPress(void)
{	
	while(GPIO_PORTF_DATA_R & PUSH_BUTTON_MASK);
}

void uninit_hardware()
{
	GPIO_PORTF_PUR_R   = 0;
	GPIO_PORTF_DEN_R   = 0;
	GPIO_PORTF_DR2R_R  = 0;
	GPIO_PORTF_DIR_R   = 0;
	
    UART1_CTL_R  = 0; 
    UART1_LCRH_R = 0; 
    UART1_FBRD_R = 0; 
    UART1_IBRD_R = 0;
    UART1_CC_R   = 0; 
    
    GPIO_PORTB_PCTL_R  = 0;
    GPIO_PORTB_PCTL_R  = 0;
    GPIO_PORTB_AFSEL_R = 0;  
    GPIO_PORTB_DEN_R   = 0; 
    GPIO_PORTB_DR2R_R  = 0;
    GPIO_PORTB_DIR_R   = 0;
    GPIO_PORTB_DIR_R   = 0;
    
   	UART0_CTL_R  = 0; 
    UART0_LCRH_R = 0; 
    UART0_FBRD_R = 0; 
    UART0_IBRD_R = 0;
    UART0_CC_R   = 0; 
    
    GPIO_PORTA_PCTL_R  = 0;
    GPIO_PORTA_PCTL_R  = 0;
    GPIO_PORTA_AFSEL_R = 0;  
    GPIO_PORTA_DEN_R   = 0; 
    GPIO_PORTA_DR2R_R  = 0;
    GPIO_PORTA_DIR_R   = 0;
    GPIO_PORTA_DIR_R   = 0;
    
    SYSCTL_RCGCGPIO_R = 0;
    SYSCTL_RCGCUART_R = 0;  
}

void configure_watch_dog(void)
{
	WATCHDOG0_LOAD_R = WATCHDOG_LOAD_VAL;
	WATCHDOG0_CTL_R |= WDT_CTL_INTEN | WDT_CTL_RESEN;
	WATCHDOG0_LOCK_R = 1;
}

void initHw(void)
{
    initSystemClockTo40Mhz();

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
    SYSCTL_RCGCWD_R |= SYSCTL_RCGCWD_R0;

    GPIO_PORTF_DIR_R  |= RED_LED_MASK;   
    GPIO_PORTF_DIR_R  &= ~PUSH_BUTTON_MASK;             
    GPIO_PORTF_DR2R_R |= RED_LED_MASK;  
    GPIO_PORTF_DEN_R  |= PUSH_BUTTON_MASK | RED_LED_MASK;       
    GPIO_PORTF_PUR_R  |= PUSH_BUTTON_MASK;                                                       
}

void erase_flash_app_area(void)
{
	uint8_t page_no;

	for(page_no = 0; page_no < FLASH_APP_TOTAL_PAGES; page_no += 1)
	{
		FLASH_FMA_R = FLASH_APP_BASE_ADDR + (page_no * ONE_KIB);
		FLASH_FMC_R = FLASH_FMC_WRKEY | FLASH_FMC_ERASE;
		
		while(FLASH_FMC_R & FLASH_FMC_ERASE);
	}
}

void write_app_to_flash(IMAGE *image_ptr)
{
	uint16_t ind;	
	uint32_t dword;
	uint8_t  range = image_ptr -> app_size / 4;
	uint32_t flash_app_base_addr = FLASH_APP_BASE_ADDR;
	
	for(ind = 0; ind < range; ind += 1)
	{
		FLASH_FMA_R = flash_app_base_addr;
		flash_app_base_addr += 4;
		
		dword = (image_ptr -> app_bytes[ind * 4] | (image_ptr -> app_bytes[ind * 4 + 1] << 8) | (image_ptr -> app_bytes[ind * 4 + 2] << 16) | (image_ptr -> app_bytes[ind * 4 + 3] << 24));
		
/*		sprintf(debug_msg, "\rDEBUG_LOG: dword => 0x%lx\n", dword);*/
/*		putsUart0(debug_msg);*/
		
		FLASH_FMD_R = dword;
		FLASH_FMC_R = FLASH_FMC_WRKEY | FLASH_FMC_WRITE;
		
		while(FLASH_FMC_R & FLASH_FMC_WRITE);
	}
}

void check_hash_check_feature(IMAGE *image_ptr)
{
	if(image_ptr -> header_bytes[HEADER_FEATURES_OFFSET] & HEADER_HASH_FEATURE_MASK)
	{
		image_ptr -> hash_check_flag = true;
		sprintf(debug_msg, "\rDEBUG_LOG: Integrity checks enabled\n");
		putsUart0(debug_msg);
	}
	else
	{
		image_ptr -> hash_check_flag = false;
		sprintf(debug_msg, "\rDEBUG_LOG: Integrity checks disabled\n");
		putsUart0(debug_msg);	
	}
}

bool check_app_size(IMAGE *image_ptr)
{
	uint8_t app_size_lsb;
	uint8_t app_size_msb;
	
	app_size_lsb = image_ptr -> header_bytes[HEADER_APP_SIZE_OFFSET];
	app_size_msb = image_ptr -> header_bytes[HEADER_APP_SIZE_OFFSET + 1];

	image_ptr -> app_size = app_size_lsb | (app_size_msb << 8);
	
	sprintf(debug_msg, "\rDEBUG_LOG: App size => %d\n", image_ptr -> app_size);
	putsUart0(debug_msg);
	
	if(image_ptr -> app_size <= FLASH_APP_SPACE_ALLOCATED)
	{
		sprintf(debug_msg, "\rDEBUG_LOG: App size is within range\n");
		putsUart0(debug_msg);
		
		return RETURN_SUCCESS;
	}

	sprintf(debug_msg, "\rDEBUG_LOG: App size is not within range. Boot failed\n");
	putsUart0(debug_msg);
		
	return RETURN_FAILURE;
}

bool check_app_hash(IMAGE *image_ptr)
{
	SHA256_CTX ctx;
	uint8_t pass = 1;
	uint8_t buf[SHA256_BLOCK_SIZE];
	uint8_t *app_hash_ptr = &(image_ptr -> header_bytes[HEADER_HASH_OFFSET]);
	
	sha256_init(&ctx);
	sha256_update(&ctx, image_ptr -> app_bytes, image_ptr -> app_size);
	sha256_final(&ctx, buf);
	pass = pass && !memcmp(app_hash_ptr, buf, SHA256_BLOCK_SIZE);
	
/*	uint8_t i;*/
/*	*/
/*	for(i = 0; i < SHA256_BLOCK_SIZE; i++)*/
/*	{*/
/*		sprintf(debug_msg, "\rDEBUG_LOG: idx = %d, hash byte => 0x%x, BUF byte => 0x%x\n", i, app_hash_ptr[i], buf[i]);*/
/*		putsUart0(debug_msg);*/
/*	}*/
		
	if(pass)
	{
		sprintf(debug_msg, "\rDEBUG_LOG: Hash check passed\n");
		putsUart0(debug_msg);
	
		return RETURN_SUCCESS;
	}
	
	sprintf(debug_msg, "\rDEBUG_LOG: Hash check failed. Initiating reset\n");
	putsUart0(debug_msg);
	
	return RETURN_FAILURE;
}

bool process_command(IMAGE *image_ptr, uint8_t command)
{
	if(command == COMMAND_INIT)
	{
		image_ptr -> command_mode = false;
		sprintf(debug_msg, "\rDEBUG_LOG: INIT command received. Send bytes\n");
		putsUart0(debug_msg);
		putcUart1(COMMAND_ACK);
		
		return RETURN_NOT_DONE;
	}	
	else if(command == COMMAND_EXIT)
	{
		image_ptr -> command_mode = false;
		sprintf(debug_msg, "\rDEBUG_LOG: Exit command received\n");
		putsUart0(debug_msg);	
		putcUart1(COMMAND_ACK);
		
		return RETURN_DONE;
	}
	else
	{
		sprintf(debug_msg, "\rDEBUG_LOG: Invalid command\n");
		putsUart0(debug_msg);
		putcUart1(COMMAND_ACK);
	
		return RETURN_NOT_DONE;
	}
}

void issue_software_reset(void)
{
	NVIC_APINT_R = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;
	while(true);
}

void check_wdt_feature(IMAGE *image_ptr)
{
	if(image_ptr -> header_bytes[HEADER_FEATURES_OFFSET] & HEADER_WDT_FEATURE_MASK)
	{
		image_ptr -> wdt_check_flag = true;
		sprintf(debug_msg, "\rDEBUG_LOG: WDT feature enabled\n");
		putsUart0(debug_msg);
	}
	else
	{
		image_ptr -> wdt_check_flag = false;
		sprintf(debug_msg, "\rDEBUG_LOG: WDT feature disabled\n");
		putsUart0(debug_msg);	
	}
}

void get_header(IMAGE *image_ptr)
{
	uint8_t recv_byte;
	uint8_t header_byte_recv_count = 0;
	
	sprintf(debug_msg, "\rDEBUG_LOG: Waiting for INIT command\n");
	putsUart0(debug_msg);	
	
	image_ptr -> command_mode = true;
	
	while(true)
	{
		recv_byte = getcUart1();
		
		if(image_ptr -> command_mode)
		{
			if(!process_command(image_ptr, recv_byte))
			{
				break;
			}
		}
		else
		{
			image_ptr -> header_bytes[header_byte_recv_count] = recv_byte;
				
			sprintf(debug_msg, "\rDEBUG_LOG: byte %d => 0x%x\n", header_byte_recv_count, recv_byte);
			putsUart0(debug_msg);
			putcUart1(COMMAND_ACK);
			
			header_byte_recv_count += 1;
			
			if(header_byte_recv_count == HEADER_SIZE)
			{
					image_ptr -> command_mode = true;
					sprintf(debug_msg, "\rDEBUG_LOG: Header bytes received. Send exit command\n");
					putsUart0(debug_msg);	
			}
		}
	}
}

void get_app_firmware(IMAGE *image_ptr)
{
	uint8_t recv_byte;
	uint16_t app_byte_recv_count = 0;
	
	sprintf(debug_msg, "\rDEBUG_LOG: Waiting for INIT command\n");
	putsUart0(debug_msg);	
	
	image_ptr -> command_mode = true;
	
	while(true)
	{
		recv_byte = getcUart1();
		
		if(image_ptr -> command_mode)
		{
			if(!process_command(image_ptr, recv_byte))
			{
				break;
			}
		}
		else
		{
			image_ptr -> app_bytes[app_byte_recv_count] = recv_byte;
			
			sprintf(debug_msg, "\rDEBUG_LOG: byte %d => 0x%x\n", app_byte_recv_count, recv_byte);
			putsUart0(debug_msg);
			putcUart1(COMMAND_ACK);
			
			app_byte_recv_count += 1;
			
			if(app_byte_recv_count == image_ptr -> app_size)
			{
					image_ptr -> command_mode = true;
					sprintf(debug_msg, "\rDEBUG_LOG: App bytes received. Send exit command\n");
					putsUart0(debug_msg);	
			}
		}
	}
}
