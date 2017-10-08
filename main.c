#include <msp430.h>
#include <stdint.h>
#include "globals.h"
#include "init.h"
#include "irq_vectors.h"
#include "set_timer.h"
#include "gen_adsr.h"
#include "gen_sine.h"

struct i2c_reg_struct			i2c_reg;									// global
struct dco_reg_struct			dco_reg;									// global
struct dac_reg_struct			dac_reg;									// global
struct gen_adsr_struct			adsr0, adsr1;								// global
struct gen_lfo_struct			lfo0, lfo1;									// global

int16_t sysex_parameter[127];												// global
int16_t	filter, resonance;													// local

void adsr_init(void) {
	adsr0.gate = GATE_OFF;
	adsr0.stage = RELEASE;
	adsr0.level = 0;
	sysex_parameter[SYSEX_W_DCO_ADSR0_ATTACK] = 400;
	sysex_parameter[SYSEX_W_DCO_ADSR0_DECAY] = 600;
	sysex_parameter[SYSEX_W_DCO_ADSR0_SUSTAIN] = 300;
	sysex_parameter[SYSEX_W_DCO_ADSR0_RELEASE] = 400;
	sysex_parameter[SYSEX_W_DCO_ADSR0_DEPTH] = 1023;

	adsr1.gate = GATE_OFF;
	adsr1.stage = RELEASE;
	adsr1.level = 0;
	sysex_parameter[SYSEX_W_DCO_ADSR1_ATTACK] = 400;
	sysex_parameter[SYSEX_W_DCO_ADSR1_DECAY] = 600;
	sysex_parameter[SYSEX_W_DCO_ADSR1_SUSTAIN] = 300;
	sysex_parameter[SYSEX_W_DCO_ADSR1_RELEASE] = 400;
	sysex_parameter[SYSEX_W_DCO_ADSR1_DEPTH] = 1023;
}

void lfo_init(void) {
	sysex_parameter[SYSEX_W_DCO_LFO0_SPEED] = 1;							// osc. frequency
	sysex_parameter[SYSEX_W_DCO_LFO0_SHAPE] = 0;
	sysex_parameter[SYSEX_W_DCO_LFO0_DEPTH] = 1023;
	lfo0.sine_t_pos	= 0;													// internal position
	lfo0.sine_s_ctr	= 0;													// internal speed

	sysex_parameter[SYSEX_W_DCO_LFO1_SPEED] = 1;							// osc. frequency
	sysex_parameter[SYSEX_W_DCO_LFO1_SHAPE] = 0;
	sysex_parameter[SYSEX_W_DCO_LFO1_DEPTH] = 1023;
	lfo1.sine_t_pos	= 0;													// internal position
	lfo1.sine_s_ctr	= 0;													// internal speed
}

uint8_t	processing_scheduler;												// task scheduler
#pragma vector=WDT_VECTOR													// watchdog, each 8000 cycles (2kHz)
__interrupt void watchdog_timer(void) {										// cca 7x probehne pwm signal
	processing_scheduler++;													// WDTIFG is cleared automatically as interrupt is processed in interval mode
}

int32_t emphasis(int32_t val, int16_t mod) {
    val = val * (1 + mod); 													// multiply by modulation (10bit)
    val = val >> 10;														// we have +/- 1024 (2048 == 11bit)
    return(val);
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       										// stop watchdog timer
    WDTCTL = WDT_MDLY_0_5;													// WD irq each 8000 cycles (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS0)
	IE1 |= WDTIE;															// Enable WDT interrupt
    init_gpio();															// set gpio
    init_clock();															// set clock
    init_i2c();																// set i2c
    init_timer0();															// set timer0
    init_timer1();															// set timer1

    adsr_init();															// set adsr0
    lfo_init();																// set lfo
    __bis_SR_register(GIE);													// general interupt enable

    sysex_parameter[SYSEX_W_DCO_FILTER_CUTOFF] = 1023;
    sysex_parameter[SYSEX_W_DCO_FILTER_RESONANCE] = 0;
    for(;;) {																// loop
		while(processing_scheduler != 4);
		processing_scheduler = 0;											// reset scheduler

		lfo0.speed = sysex_parameter[SYSEX_W_DCO_LFO0_SPEED];
		lfo0.shape = sysex_parameter[SYSEX_W_DCO_LFO0_SHAPE];
		adsr0.attack_step_parameter = sysex_parameter[SYSEX_W_DCO_ADSR0_ATTACK];
		adsr0.decay_step_parameter = sysex_parameter[SYSEX_W_DCO_ADSR0_DECAY];
		adsr0.sustain_level_parameter = sysex_parameter[SYSEX_W_DCO_ADSR0_SUSTAIN];
		adsr0.release_step_parameter = sysex_parameter[SYSEX_W_DCO_ADSR0_RELEASE];

		filter  = sysex_parameter[SYSEX_W_DCO_FILTER_CUTOFF];
		resonance = sysex_parameter[SYSEX_W_DCO_FILTER_RESONANCE];

		// control panel or sysex emphasis for envelope
		// modulation to (+) and (-) ranges with a singel 10bit value (0-1023), 511 is the middle controller positon
		// max/min result is -1023/+1023
		filter += emphasis(envelope(&adsr0), (((sysex_parameter[SYSEX_W_DCO_ADSR0_DEPTH] - 512) * 2) + 1));
		// sine returns +/- 1023
		filter += emphasis(sine(&lfo0), sysex_parameter[SYSEX_W_DCO_LFO0_DEPTH]);
		// emphasis on filter key follow - key is from 0-127 (0-254), key 0 shuld have effect 0, key 255 should have effect 1023(1020)
		filter += emphasis((dco_reg.r2r * 4), (((sysex_parameter[SYSEX_W_DCO_FILTER_KEY_FOLLOW_DEPTH] - 512) * 2) + 1));
		filter += emphasis((dco_reg.key_velocity * 8), (((sysex_parameter[SYSEX_W_DCO_FILTER_KEY_VELOCITY_DEPTH] - 512) * 2) + 1));

		timer1_set_pwm0(filter);											// PWM0 is CUTOFF
    	timer1_set_pwm1(resonance);											// PWM1 is resonance
    }
}
