#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#define RED_LED_MASK 2
#define PUSH_BUTTON_MASK 16
#define DEBUG_MSG_MAX_SIZE 100
#define SHA256_BLOCK_SIZE 32
#define ONE_KIB 1024
#define WATCHDOG_LOAD_VAL 40000

#define FLASH_APP_BASE_ADDR 0x20000
#define FLASH_APP_SPACE_ALLOCATED (128 * 1024) /* 128KiB */
#define FLASH_APP_TOTAL_PAGES 128
#define FLASH_APP_RESET_HANDLER_ADDR (FLASH_APP_BASE_ADDR + 4)

#define HEADER_APP_SIZE_OFFSET 0
#define HEADER_HASH_OFFSET 3
#define HEADER_SIZE (HEADER_HASH_OFFSET + SHA256_BLOCK_SIZE)
#define HEADER_FEATURES_OFFSET 2
#define HEADER_HASH_FEATURE_MASK 1
#define HEADER_WDT_FEATURE_MASK 2

#define COMMAND_EXIT 0xBB
#define COMMAND_INIT 0xAA
#define COMMAND_ACK 0xCC

#define RETURN_SUCCESS 1
#define RETURN_FAILURE 0
#define RETURN_NOT_DONE 1
#define RETURN_DONE 0

typedef struct _IMAGE
{
	uint16_t app_size;
	uint8_t app_bytes[ONE_KIB];
	uint8_t header_bytes[HEADER_SIZE];
	uint8_t image_hash[SHA256_BLOCK_SIZE];
	bool init_cmd_received;
	bool header_bytes_received;
	bool command_mode;
	bool receive_mode;
	bool hash_check_flag;
	bool wdt_check_flag;
} IMAGE;

void uninit_hardware(void);
void initHw(void);
void waitPbPress(void);
void erase_flash_app_area(void);
void write_app_to_flash(IMAGE *);
void get_app_firmware(IMAGE *);
bool check_app_size(IMAGE *);
bool check_app_hash(IMAGE *);
void get_header(IMAGE *);
bool process_command(IMAGE *, uint8_t);
void check_hash_check_feature(IMAGE *);
void check_wdt_feature(IMAGE *);
void issue_software_reset();
void configure_watch_dog();

#endif
