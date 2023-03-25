ENTRY(reset_handler)

MEMORY
{
	FLASH (RX) : ORIGIN = 0x00000000, LENGTH = 0x00020000 /* 128KiB */
	SRAM (RWX) : ORIGIN = 0x20000000, LENGTH = 0x00008000 /* 32KiB */
}

SECTIONS
{
	.text :
	{
		*(.vector_table)
		*(.text)
		*(.text.*)
		*(.init)
		*(.fini)
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
		_etext = .;
	}> FLASH
	
	_la_data = LOADADDR(.data);
	
	.data :
	{	
		_sdata = .;
		*(.data)
		*(.data.*)
		_edata = .;
	}> SRAM AT> FLASH

	.bss :
	{
		_sbss = .;
		__bss_start__ = _sbss;
		*(.bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
		__bss_end__ = _ebss;
		. = ALIGN(4);
		end = .;
		__end__ = .;
	}> SRAM
}
