#!/usr/bin/python3

import sys
import os
import hashlib
import serial
from configparser import ConfigParser

MAX_ARGS = 3
CONFIG_FILE_OFFSET = 2
TX_PORT = "/dev/ttyUSB0"
COMMAND_INIT = 0xAA
COMMAND_EXIT = 0xBB
COMMAND_ACK = 0xCC
HASH_CHECK_MASK = 1
WDT_FEATURE_MASK = 2
BYTE_ZERO = 0x00
CONFIG_APP_SECTION = "APP"
CONFIG_APP_SECTION_INPUT_FILE = "APP_FILE"
CONFIG_APP_SECTION_HASH_CHECK = "HASH_CHECK"
CONFIG_APP_SECTION_WDT_FEATURE = "WDT_FEATURE"
HEADER_LIST_FEATURES_OFFSET = 2

class Transmitter:
	def __init__(self, config_file_name):
		self.config_file_name = config_file_name
		self.config_obj = None
		self.app_file_name = None
		self.app_hash_bytes_str = ""
		self.app_size = None
		self.app_bytes_list = []
		self.header_bytes_list = []
		self.ser = serial.Serial(TX_PORT, 115200, serial.EIGHTBITS, serial.PARITY_EVEN, serial.STOPBITS_ONE)
		self.command_init = COMMAND_INIT
		self.command_exit = COMMAND_EXIT
		self.command_ack = COMMAND_ACK
		self.hash_check_flag = False
		self.wdt_feature_flag = False
		
	def display_usage(self):
    		print("Incorrect Usage\nUsage: ./tx_tool -c <config.ini>")
    	    
	def check_args(self, arg_list):
		if arg_list[1] != "-c":
		    self.display_usage()
		    return 0

		if "." not in arg_list[CONFIG_FILE_OFFSET]:
		    self.display_usage()
		    return 0

		if arg_list[CONFIG_FILE_OFFSET].split(".")[1] != "ini":
		    self.display_usage()
		    return 0

		return 1
	
	def read_config(self):
		self.config_obj = ConfigParser()
		self.config_obj.read(self.config_file_name) 
	
		self.app_file_name =  self.config_obj[CONFIG_APP_SECTION][CONFIG_APP_SECTION_INPUT_FILE]
		
		if self.config_obj[CONFIG_APP_SECTION][CONFIG_APP_SECTION_HASH_CHECK] == "True":
			self.hash_check_flag = True
		else:
			self.hash_check_flag = False
		
		if self.config_obj[CONFIG_APP_SECTION][CONFIG_APP_SECTION_WDT_FEATURE] == "True":
			self.wdt_feature_flag = True
		else:
			self.wdt_feature_flag = False
	
	def get_app(self):	
		file_ptr = open(self.app_file_name, "rb")
		self.app_bytes_str = file_ptr.read().hex()
		file_ptr.close()
    	   
	def get_app_size(self):
		self.app_size = hex(os.stat(self.app_file_name).st_size)
    	   
	def get_app_hash(self):	
   		self.app_hash_bytes_str = hashlib.sha256(bytearray.fromhex(self.app_bytes_str)).hexdigest()
    	
	def populate_header_list(self):
		start_ind = 0
		stop_ind = 0
    	
		msb_app_len = self.app_size[2: len(self.app_size) - 2]
		lsb_app_len = self.app_size[3:]
    	
		self.header_bytes_list.append(int(lsb_app_len, 16))
		self.header_bytes_list.append(int(msb_app_len, 16))

		self.header_bytes_list.append(BYTE_ZERO)

		if self.hash_check_flag:
			self.header_bytes_list[HEADER_LIST_FEATURES_OFFSET] |= HASH_CHECK_MASK
		else:
			self.header_bytes_list[HEADER_LIST_FEATURES_OFFSET] &= ~(HASH_CHECK_MASK) 

		if self.wdt_feature_flag:
			self.header_bytes_list[HEADER_LIST_FEATURES_OFFSET] |= WDT_FEATURE_MASK
		else:
			self.header_bytes_list[HEADER_LIST_FEATURES_OFFSET] &= ~(WDT_FEATURE_MASK) 

		for ind in range(0, len(self.app_hash_bytes_str) + 1):
	    		if start_ind != stop_ind:
	    			if stop_ind % 2 == 0:
	    				byte = self.app_hash_bytes_str[start_ind: stop_ind]
	    				byte_int = int(byte, 16)
	    				self.header_bytes_list.append(byte_int)
	    				start_ind = stop_ind
	    		
	    		stop_ind += 1
	    		
		self.header_bytes_list[3] = 0x01	    	
    
	def populate_app_list(self):
		start_ind = 0
		stop_ind = 0
    	
		for ind in range(0, len(self.app_bytes_str) + 1):
			if start_ind != stop_ind:
				if stop_ind % 2 == 0:
					byte = self.app_bytes_str[start_ind: stop_ind]
					byte_int = int(byte, 16)
					self.app_bytes_list.append(byte_int)
					start_ind = stop_ind
	
			stop_ind += 1	
       
	def tx_header(self):
		self.send_init_command()
				
		if input("Enter c to send header bytes: ") == "c":
			self.tx_bytes(self.header_bytes_list)
			
		self.send_exit_command()
				
	def tx_app(self):
		self.send_init_command()
				
		if input("Enter c to send app bytes: ") == "c":
			self.tx_bytes(self.app_bytes_list)
			
		self.send_exit_command()
       
	def send_init_command(self):
		if input("Enter c to send init command: ") == "c":
			send_byte = bytearray([self.command_init])
			self.ser.write(send_byte)
			ack = self.ser.read()
			
			if ack == bytes([self.command_ack]):
				print("Init command received by controller")
	
	def send_exit_command(self):
		if input("Enter c to send exit command: ") == "c":
			send_byte = bytearray([self.command_exit])
			self.ser.write(send_byte)
			ack = self.ser.read()
			
			if ack == bytes([self.command_ack]):
				print("Exit command received by controller")
       
	def tx_bytes(self, byte_list):
		for byte in byte_list:
			send_byte = bytearray([byte])
			self.ser.write(send_byte)
			ack = self.ser.read()

			if ack == bytes([self.command_ack]):
				print("Byte received by controller")
       
def main():
	arg_list = sys.argv
	
	if len(arg_list) != MAX_ARGS:
		temp_obj = Transmitter("")
		temp_obj.display_usage()
	else:
		config_file = arg_list[CONFIG_FILE_OFFSET]
		tx_obj = Transmitter(config_file)

		if tx_obj.check_args(arg_list):
			tx_obj.read_config()	
			tx_obj.get_app()
			tx_obj.get_app_size()
			tx_obj.get_app_hash()
			tx_obj.populate_header_list()
			tx_obj.populate_app_list()
			tx_obj.tx_header()
			tx_obj.tx_app()
        	
if __name__ == "__main__":
	main()
