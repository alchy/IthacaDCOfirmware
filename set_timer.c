#include <stdint.h>
#include "globals.h"
#include "set_timer.h"

extern struct dac_reg_struct	dac_reg;

uint16_t convert(int16_t val) {
	uint16_t ccr;
	if(val < 0) {
		ccr = 0;
	} else if(val > 1023) {
		ccr = 1023;
	} else {
		ccr = val;
	}
	return(ccr);
}

void timer1_set_pwm0(int16_t val) {						// 10bit PWM timer 0 - 1023
	dac_reg.virt_TA1CCR1 = PWMBASE - convert(val);
}

void timer1_set_pwm1(int16_t val) {						// 10bit PWM timer 0 - 1023
	dac_reg.virt_TA1CCR2 = PWMBASE - convert(val);
}
