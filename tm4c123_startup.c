#include <stdint.h>

#define SRAM_START  0x20000000
#define SRAM_SIZE   0x00008000 				
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))
#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _la_data;

int main(void);
void __libc_init_array(void);


void reset_handler(void);
void nmi_handler(void)				__attribute__((weak, alias("default_handler")));
void fault_handler(void)			__attribute__((weak, alias("default_handler")));
void mpu_fault_handler(void)          		__attribute__((weak, alias("default_handler")));
void bus_fault_handler(void)          		__attribute__((weak, alias("default_handler")));
void usage_fault_handler(void)       		__attribute__((weak, alias("default_handler")));
void svc_handler(void)                      	__attribute__((weak, alias("default_handler")));	
void debug_monitor_handler(void)                __attribute__((weak, alias("default_handler")));       
void pendsv_handler(void)                       __attribute__((weak, alias("default_handler")));	
void systick_handler(void)                      __attribute__((weak, alias("default_handler"))); 	
void gpio_PORTA_handler(void)                   __attribute__((weak, alias("default_handler")));   	
void gpio_PORTB_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void gpio_PORTC_handler(void)                   __attribute__((weak, alias("default_handler")));   	
void gpio_PORTD_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void gpio_PORTE_handler(void)                   __attribute__((weak, alias("default_handler")));   	
void uart0_RX_TX_handler(void)                  __attribute__((weak, alias("default_handler")));
void uart1_RX_TX_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void spi0_RX_TX_handler(void)                   __attribute__((weak, alias("default_handler")));    
void i2c0_master_slave_handler(void)            __attribute__((weak, alias("default_handler")));     
void pwm_fault_handler(void)                    __attribute__((weak, alias("default_handler")));       
void pwm_generator0_handler(void)               __attribute__((weak, alias("default_handler")));      
void pwm_generator1_handler(void)               __attribute__((weak, alias("default_handler")));     
void pwm_generator2_handler(void)               __attribute__((weak, alias("default_handler")));      
void quadrature_encoder0_handler(void)          __attribute__((weak, alias("default_handler")));       
void adc_sequence0_handler(void)                __attribute__((weak, alias("default_handler")));       
void adc_sequence1_handler(void)                __attribute__((weak, alias("default_handler")));     
void adc_sequence2_handler(void)                __attribute__((weak, alias("default_handler")));       
void adc_sequence3_handler(void)                __attribute__((weak, alias("default_handler")));      
void watch_dog_handler(void)                    __attribute__((weak, alias("default_handler")));  	
void timer0_subtimerA_handler(void)             __attribute__((weak, alias("default_handler")));      
void timer0_subtimerB_handler(void)             __attribute__((weak, alias("default_handler")));      
void timer1_subtimerA_handler(void)             __attribute__((weak, alias("default_handler")));     
void timer1_subtimerB_handler(void)             __attribute__((weak, alias("default_handler")));    
void timer2_subtimerA_handler(void)             __attribute__((weak, alias("default_handler")));      
void timer2_subtimerB_handler(void)             __attribute__((weak, alias("default_handler")));     
void analog_comparator0_handler(void)           __attribute__((weak, alias("default_handler")));      
void analog_comparator1_handler(void)           __attribute__((weak, alias("default_handler")));      
void analog_comparator2_handler(void)           __attribute__((weak, alias("default_handler")));     
void system_control_handler(void)               __attribute__((weak, alias("default_handler")));       
void flash_control_handler(void)                __attribute__((weak, alias("default_handler")));      
void gpio_PORTF_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void gpio_PORTG_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void gpio_PORTH_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void uart2_RX_TX_handler(void)                  __attribute__((weak, alias("default_handler")));     
void spi1_RX_TX_handler(void)                   __attribute__((weak, alias("default_handler")));   
void timer3_subtimerA_handler(void)             __attribute__((weak, alias("default_handler")));     
void timer3_subtimerB_handler(void)             __attribute__((weak, alias("default_handler")));      
void i2c1_master_slave_handler(void)            __attribute__((weak, alias("default_handler")));      
void quadrature_encoder1_handler(void)          __attribute__((weak, alias("default_handler")));       
void can0_handler(void)                       	__attribute__((weak, alias("default_handler")));	
void can1_handler(void)                       	__attribute__((weak, alias("default_handler")));	
void hibernate_handler(void)                    __attribute__((weak, alias("default_handler")));   	
void usb0_handler(void)                       	__attribute__((weak, alias("default_handler")));	
void pwm_generator3_handler(void)               __attribute__((weak, alias("default_handler")));       
void udma_software_transfer_handler(void)       __attribute__((weak, alias("default_handler")));       
void udma_error_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void adc1_sequence0_handler(void)               __attribute__((weak, alias("default_handler")));       
void adc1_sequence1_handler(void)               __attribute__((weak, alias("default_handler")));      
void adc1_sequence2_handler(void)               __attribute__((weak, alias("default_handler")));       
void adc1_sequence3_handler(void)               __attribute__((weak, alias("default_handler")));      
void gpio_PORTJ_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void gpio_PORTK_handler(void)                   __attribute__((weak, alias("default_handler")));   	
void gpio_PORTL_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void spi2_RX_TX_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void spi3_RX_TX_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void uart3_RX_TX_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void uart4_RX_TX_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void uart5_RX_TX_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void uart6_RX_TX_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void uart7_RX_TX_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void i2c2_master_slave_handler(void)            __attribute__((weak, alias("default_handler")));      
void i2c3_master_slave_handler(void)            __attribute__((weak, alias("default_handler")));       
void timer4_subtimerA_handler(void)             __attribute__((weak, alias("default_handler")));     
void timer4_subtimerB_handler(void)             __attribute__((weak, alias("default_handler")));      
void timer5_subtimerA_handler(void)             __attribute__((weak, alias("default_handler")));     
void timer5_subtimerB_handler(void)             __attribute__((weak, alias("default_handler")));      
void wide_timer0_subtimerA(void)                __attribute__((weak, alias("default_handler")));       
void wide_timer0_subtimerB(void)                __attribute__((weak, alias("default_handler")));       
void wide_timer1_subtimerA(void)                __attribute__((weak, alias("default_handler")));      
void wide_timer1_subtimerB(void)                __attribute__((weak, alias("default_handler")));     
void wide_timer2_subtimerA(void)                __attribute__((weak, alias("default_handler")));     
void wide_timer2_subtimerB(void)                __attribute__((weak, alias("default_handler")));       
void wide_timer3_subtimerA(void)                __attribute__((weak, alias("default_handler")));       
void wide_timer3_subtimerB(void)                __attribute__((weak, alias("default_handler")));       
void wide_timer4_subtimerA(void)                __attribute__((weak, alias("default_handler")));      
void wide_timer4_subtimerB(void)                __attribute__((weak, alias("default_handler")));     
void wide_timer5_subtimerA(void)                __attribute__((weak, alias("default_handler")));      
void wide_timer5_subtimerB(void)                __attribute__((weak, alias("default_handler")));       
void fpu_handler(void)                       	__attribute__((weak, alias("default_handler")));	
void i2c4_master_slave_handler(void)            __attribute__((weak, alias("default_handler")));       
void i2c5_master_slave_handler(void)            __attribute__((weak, alias("default_handler")));       
void gpio_PORTM_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void gpio_PORTN_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void quadrature_encoder2_handler(void)          __attribute__((weak, alias("default_handler")));       
void gpio_PORTP_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void gpio_PORTP1_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void gpio_PORTP2_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void gpio_PORTP3_handler(void)                  __attribute__((weak, alias("default_handler")));     
void gpio_PORTP4_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void gpio_PORTP5_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void gpio_PORTP6_handler(void)                  __attribute__((weak, alias("default_handler")));   	
void gpio_PORTP7_handler(void)                  __attribute__((weak, alias("default_handler")));    	
void gpio_PORTQ_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void gpio_PORTQ1_handler(void)                  __attribute__((weak, alias("default_handler")));    	
void gpio_PORTQ2_handler(void)                  __attribute__((weak, alias("default_handler")));    	
void gpio_PORTQ3_handler(void)                  __attribute__((weak, alias("default_handler")));    	
void gpio_PORTQ4_handler(void)                  __attribute__((weak, alias("default_handler")));    	
void gpio_PORTQ5_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void gpio_PORTQ6_handler(void)                  __attribute__((weak, alias("default_handler")));    	
void gpio_PORTQ7_handler(void)                  __attribute__((weak, alias("default_handler")));     	
void gpio_PORTR_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void gpio_PORTS_handler(void)                   __attribute__((weak, alias("default_handler")));    	
void pwm1_generator0_handler(void)              __attribute__((weak, alias("default_handler")));      
void pwm1_generator1_handler(void)              __attribute__((weak, alias("default_handler")));      
void pwm1_generator2_handler(void)              __attribute__((weak, alias("default_handler")));       
void pwm1_generator3_handler(void)              __attribute__((weak, alias("default_handler")));       
void pwm1_fault_handler(void)                   __attribute__((weak, alias("default_handler")));     		


uint32_t vectors[] __attribute__((section(".vector_table"))) = 
{
	STACK_START,
	(uint32_t) &reset_handler,          			// The reset handler
	(uint32_t) &nmi_handler,                		// The NMI handler
	(uint32_t) &fault_handler,              		// The hard fault handler
	(uint32_t) &mpu_fault_handler,          		// The MPU fault handler
	(uint32_t) &bus_fault_handler,          		// The bus fault handler
	(uint32_t) &usage_fault_handler,        		// The usage fault handler
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	(uint32_t) &svc_handler,                      		// SVCall handler
	(uint32_t) &debug_monitor_handler,                      // Debug monitor handler
	0,                                      		// Reserved
	(uint32_t) &pendsv_handler,                      	// The PendSV handler
	(uint32_t) &systick_handler,                      	// The SysTick handler
	(uint32_t) &gpio_PORTA_handler,                      	// GPIO Port A
	(uint32_t) &gpio_PORTB_handler,                      	// GPIO Port B
	(uint32_t) &gpio_PORTC_handler,                     	// GPIO Port C
	(uint32_t) &gpio_PORTD_handler,                      	// GPIO Port D
	(uint32_t) &gpio_PORTE_handler,                      	// GPIO Port E
	(uint32_t) &uart0_RX_TX_handler,                      	// UART0 Rx and Tx
	(uint32_t) &uart1_RX_TX_handler,                      	// UART1 Rx and Tx
	(uint32_t) &spi0_RX_TX_handler,                      	// SSI0 Rx and Tx
	(uint32_t) &i2c0_master_slave_handler,                  // I2C0 Master and Slave
	(uint32_t) &pwm_fault_handler,                          // PWM Fault
	(uint32_t) &pwm_generator0_handler,                     // PWM Generator 0
	(uint32_t) &pwm_generator1_handler,                     // PWM Generator 1
	(uint32_t) &pwm_generator2_handler,                     // PWM Generator 2
	(uint32_t) &quadrature_encoder0_handler,                // Quadrature Encoder 0
	(uint32_t) &adc_sequence0_handler,                      // ADC Sequence 0
	(uint32_t) &adc_sequence1_handler,                      // ADC Sequence 1
	(uint32_t) &adc_sequence2_handler,                      // ADC Sequence 2
	(uint32_t) &adc_sequence3_handler,                      // ADC Sequence 3
	(uint32_t) &watch_dog_handler,                     	// Watchdog timer
	(uint32_t) &timer0_subtimerA_handler,                   // Timer 0 subtimer A
	(uint32_t) &timer0_subtimerB_handler,                   // Timer 0 subtimer B
	(uint32_t) &timer1_subtimerA_handler,                   // Timer 1 subtimer A
	(uint32_t) &timer1_subtimerB_handler,                   // Timer 1 subtimer B
	(uint32_t) &timer2_subtimerA_handler,                   // Timer 2 subtimer A
	(uint32_t) &timer2_subtimerB_handler,                   // Timer 2 subtimer B
	(uint32_t) &analog_comparator0_handler,                 // Analog Comparator 0
	(uint32_t) &analog_comparator1_handler,                 // Analog Comparator 1
	(uint32_t) &analog_comparator2_handler,                 // Analog Comparator 2
	(uint32_t) &system_control_handler,                     // System Control (PLL, OSC, BO)
	(uint32_t) &flash_control_handler,                      // FLASH Control
	(uint32_t) &gpio_PORTF_handler,                      	// GPIO Port F
	(uint32_t) &gpio_PORTG_handler,                      	// GPIO Port G
	(uint32_t) &gpio_PORTH_handler,                      	// GPIO Port H
	(uint32_t) &uart2_RX_TX_handler,                      	// UART2 Rx and Tx
	(uint32_t) &spi1_RX_TX_handler,                      	// SSI1 Rx and Tx
	(uint32_t) &timer3_subtimerA_handler,                   // Timer 3 subtimer A
	(uint32_t) &timer3_subtimerB_handler,                   // Timer 3 subtimer B
	(uint32_t) &i2c1_master_slave_handler,                  // I2C1 Master and Slave
	(uint32_t) &quadrature_encoder1_handler,                // Quadrature Encoder 1
	(uint32_t) &can0_handler,                      		// CAN0
	(uint32_t) &can1_handler,                      		// CAN1
	0,                                      		// Reserved
	0,                                      		// Reserved
	(uint32_t) &hibernate_handler,                      	// Hibernate
	(uint32_t) &usb0_handler,                      		// USB0
	(uint32_t) &pwm_generator3_handler,                     // PWM Generator 3
	(uint32_t) &udma_software_transfer_handler,             // uDMA Software Transfer
	(uint32_t) &udma_error_handler,                      	// uDMA Error
	(uint32_t) &adc1_sequence0_handler,                     // ADC1 Sequence 0
	(uint32_t) &adc1_sequence1_handler,                     // ADC1 Sequence 1
	(uint32_t) &adc1_sequence2_handler,                     // ADC1 Sequence 2
	(uint32_t) &adc1_sequence3_handler,                     // ADC1 Sequence 3
	0,                                      		// Reserved
	0,                                      		// Reserved
	(uint32_t) &gpio_PORTJ_handler,                      	// GPIO Port J
	(uint32_t) &gpio_PORTK_handler,                     	// GPIO Port K
	(uint32_t) &gpio_PORTL_handler,                      	// GPIO Port L
	(uint32_t) &spi2_RX_TX_handler,                      	// SSI2 Rx and Tx
	(uint32_t) &spi3_RX_TX_handler,                      	// SSI3 Rx and Tx
	(uint32_t) &uart3_RX_TX_handler,                      	// UART3 Rx and Tx
	(uint32_t) &uart4_RX_TX_handler,                      	// UART4 Rx and Tx
	(uint32_t) &uart5_RX_TX_handler,                      	// UART5 Rx and Tx
	(uint32_t) &uart6_RX_TX_handler,                      	// UART6 Rx and Tx
	(uint32_t) &uart7_RX_TX_handler,                      	// UART7 Rx and Tx
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	(uint32_t) &i2c2_master_slave_handler,                  // I2C2 Master and Slave
	(uint32_t) &i2c3_master_slave_handler,                  // I2C3 Master and Slave
	(uint32_t) &timer4_subtimerA_handler,                   // Timer 4 subtimer A
	(uint32_t) &timer4_subtimerB_handler,                   // Timer 4 subtimer B
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                     			// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	0,                                      		// Reserved
	(uint32_t) &timer5_subtimerA_handler,                   // Timer 5 subtimer A
	(uint32_t) &timer5_subtimerB_handler,                   // Timer 5 subtimer B
	(uint32_t) &wide_timer0_subtimerA,                      // Wide Timer 0 subtimer A
	(uint32_t) &wide_timer0_subtimerB,                      // Wide Timer 0 subtimer B
	(uint32_t) &wide_timer1_subtimerA,                      // Wide Timer 1 subtimer A
	(uint32_t) &wide_timer1_subtimerB,                      // Wide Timer 1 subtimer B
	(uint32_t) &wide_timer2_subtimerA,                      // Wide Timer 2 subtimer A
	(uint32_t) &wide_timer2_subtimerB,                      // Wide Timer 2 subtimer B
	(uint32_t) &wide_timer3_subtimerA,                      // Wide Timer 3 subtimer A
	(uint32_t) &wide_timer3_subtimerB,                      // Wide Timer 3 subtimer B
	(uint32_t) &wide_timer4_subtimerA,                      // Wide Timer 4 subtimer A
	(uint32_t) &wide_timer4_subtimerB,                      // Wide Timer 4 subtimer B
	(uint32_t) &wide_timer5_subtimerA,                      // Wide Timer 5 subtimer A
	(uint32_t) &wide_timer5_subtimerB,                      // Wide Timer 5 subtimer B
	(uint32_t) &fpu_handler,                      		// FPU
	0,                                      		// Reserved
	0,                                      		// Reserved
	(uint32_t) &i2c4_master_slave_handler,                  // I2C4 Master and Slave
	(uint32_t) &i2c5_master_slave_handler,                  // I2C5 Master and Slave
	(uint32_t) &gpio_PORTM_handler,                      	// GPIO Port M
	(uint32_t) &gpio_PORTN_handler,                      	// GPIO Port N
	(uint32_t) &quadrature_encoder2_handler,                // Quadrature Encoder 2
	0,                                      		// Reserved
	0,                                      		// Reserved
	(uint32_t) &gpio_PORTP_handler,                      	// GPIO Port P (Summary or P0)
	(uint32_t) &gpio_PORTP1_handler,                      	// GPIO Port P1
	(uint32_t) &gpio_PORTP2_handler,                      	// GPIO Port P2
	(uint32_t) &gpio_PORTP3_handler,                      	// GPIO Port P3
	(uint32_t) &gpio_PORTP4_handler,                      	// GPIO Port P4
	(uint32_t) &gpio_PORTP5_handler,                      	// GPIO Port P5
	(uint32_t) &gpio_PORTP6_handler,                     	// GPIO Port P6
	(uint32_t) &gpio_PORTP7_handler,                     	// GPIO Port P7
	(uint32_t) &gpio_PORTQ_handler,                      	// GPIO Port Q (Summary or Q0)
	(uint32_t) &gpio_PORTQ1_handler,                     	// GPIO Port Q1
	(uint32_t) &gpio_PORTQ2_handler,                     	// GPIO Port Q2
	(uint32_t) &gpio_PORTQ3_handler,                     	// GPIO Port Q3
	(uint32_t) &gpio_PORTQ4_handler,                     	// GPIO Port Q4
	(uint32_t) &gpio_PORTQ5_handler,                      	// GPIO Port Q5
	(uint32_t) &gpio_PORTQ6_handler,                      	// GPIO Port Q6
	(uint32_t) &gpio_PORTQ7_handler,                      	// GPIO Port Q7
	(uint32_t) &gpio_PORTR_handler,                      	// GPIO Port R
	(uint32_t) &gpio_PORTS_handler,                      	// GPIO Port S
	(uint32_t) &pwm1_generator0_handler,                    // PWM 1 Generator 0
	(uint32_t) &pwm1_generator1_handler,                    // PWM 1 Generator 1
	(uint32_t) &pwm1_generator2_handler,                    // PWM 1 Generator 2
	(uint32_t) &pwm1_generator3_handler,                    // PWM 1 Generator 3
	(uint32_t) &pwm1_fault_handler                       	// PWM 1 Fault	
};


void reset_handler(void)
{
	/* Copy .data section to SRAM */
	uint32_t size = (uint32_t) &_edata - (uint32_t) &_sdata;
	uint8_t *ptr_dst = (uint8_t *) &_sdata;
	uint8_t *ptr_src = (uint8_t *) &_la_data;
	
	for(uint32_t i = 0; i < size; i++)
	{
		*ptr_dst++ = *ptr_src;
	}
	
	/* Initialize .bss section to zero in SRAM */
	size = &_ebss - &_sbss;
	ptr_dst = (uint8_t *) &_sbss;
	
	for(uint32_t i = 0; i < size; i++)
	{
		*ptr_dst++ = 0;
	}
	
	/* Call init function of standard library
	   This is done if you are using standard functions
	   like printf or functions related to strings  */
	__libc_init_array();   
	
	/* Call main */
	main();
}

void default_handler(void)
{
	while(1);
}

