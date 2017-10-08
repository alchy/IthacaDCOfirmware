#include <stdint.h>
#include "globals.h"

extern struct i2c_reg_struct i2c_reg;
extern int16_t sysex_parameter[];

sysex_message(uint8_t rx_buf) {
	if(i2c_reg.addr < 128) {
		switch (i2c_reg.cntr) {
		case 1:
			i2c_reg.temporary_lsb = rx_buf; 				// Adafruit I2C lib send lsb first
			i2c_reg.cntr++;
			break;
		case 2:
			i2c_reg.temporary_msb = rx_buf;           		// read msb
			i2c_reg.cntr++;
			sysex_parameter[i2c_reg.addr] = i2c_reg.temporary_msb;
			sysex_parameter[i2c_reg.addr] = sysex_parameter[i2c_reg.addr] << 8;
			sysex_parameter[i2c_reg.addr] |= i2c_reg.temporary_lsb;
			break;
		}
	}
}


