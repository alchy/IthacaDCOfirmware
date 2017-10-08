#include <msp430.h>
#include <stdint.h>
#include "globals.h"
#include "set_timer.h"
#include "gen_adsr_dividers.h"

void attack(struct gen_adsr_struct *adsr) {
	if (adsr->gate == GATE_ON) {
		if((adsr->level + adsr_dividers[adsr->attack_step_parameter]) >= ENV_MAX) {
			adsr->level = ENV_MAX;
			adsr->stage = DECAY;
			return;
		} else {
			adsr->level += adsr_dividers[adsr->attack_step_parameter];
		}
	} else {
		adsr->stage = RELEASE;
	}
};

void decay(struct gen_adsr_struct *adsr) {
	if(adsr->gate == GATE_ON) {
		adsr->sustain_level = (long signed int) adsr->sustain_level_parameter;
		adsr->sustain_level = adsr->sustain_level * 65536;
		adsr->sustain_level = adsr->sustain_level * 16;
		if(( adsr->level - adsr_dividers[adsr->decay_step_parameter]) > adsr->sustain_level + 0xFFFFF) {
			adsr->level -= adsr_dividers[adsr->decay_step_parameter];
		} else {
			adsr->level = adsr->sustain_level;
		}
	} else {
		adsr->stage = RELEASE;
	}
};

void release(struct gen_adsr_struct *adsr) {
	if (adsr->gate == GATE_OFF) {
		if((adsr->level - adsr_dividers[adsr->release_step_parameter]) > 0) {
			adsr->level -= adsr_dividers[adsr->release_step_parameter];
		} else {
			adsr->level = 0;
		}
	} else {
		adsr->stage = ATTACK;
	}
};

uint16_t envelope(struct gen_adsr_struct *adsr) {
	switch(adsr->stage) {
	case ATTACK:
		attack(adsr);
		break;
	case DECAY:
		decay(adsr);
		break;
	case RELEASE:
		release(adsr);
		break;
	}
	// <><---10bit--> <---------20bit-------->
	// +r-- ---  ---- xxxx xxxx xxxx xxxx xxxx
	// 0011 1111 1111 0000 0000 0000 0000 0000
	return(adsr->level >> 20);
};
