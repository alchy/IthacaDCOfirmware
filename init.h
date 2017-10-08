/*
 * init.h
 *
 *  Created on: 26. 4. 2016
 *      Author: Jindra
 */

#ifndef INIT_H_
#define INIT_H_

#include <stdint.h>

void 	init_gpio(void);
void 	init_timer0(void);
void 	init_timer1(void);
uint8_t set_i2c_addr(void);
void 	init_i2c(void);
void 	init_clock(void);

#endif /* INIT_H_ */
