#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdint.h>

// i2c DCO base address registration
// 20 cycles added as a reserve for irq entry
#define	I2C_BASE_ADDR   					0x08
#define	PWMBASE								1023 + 22

// i2c device type enumeration
#define REG_B_DEVTYPE           			0xfe
#define DEV_TYPE_DCO            			0x10
#define DEV_TYPE_ADSR           			0x11
#define DEV_TYPE_DAC            			0x12

// i2c dco registers
#define REG_B_LED               			0x00
#define REG_B_R2R               			0x01
#define REG_B_DIVIDER           			0x02
#define REG_W_COUNTER           			0x03
#define REG_B_CONTROL           			0x04
#define REG_B_KEY_VELOCITY					0x05
#define REG_B_CALIBRATE         			0xf0

// 111 various sysex messages from 0x10 - 0x7f *7bit data register
// ---------------------------------------------
// public register addresses
// DCO UNIT
// ---------------------------------------------
#define SYSEX_W_DCO_ADSR0_ATTACK                16
#define SYSEX_W_DCO_ADSR0_DECAY                 17
#define SYSEX_W_DCO_ADSR0_SUSTAIN               18
#define SYSEX_W_DCO_ADSR0_RELEASE               19
#define SYSEX_W_DCO_ADSR0_DEPTH                 20

#define SYSEX_W_DCO_ADSR1_ATTACK                21
#define SYSEX_W_DCO_ADSR1_DECAY                 22
#define SYSEX_W_DCO_ADSR1_SUSTAIN               23
#define SYSEX_W_DCO_ADSR1_RELEASE               24
#define SYSEX_W_DCO_ADSR1_DEPTH                 25

#define SYSEX_W_DCO_LFO0_MODE                   26
#define SYSEX_W_DCO_LFO0_SPEED                  27
#define SYSEX_W_DCO_LFO0_SHAPE                  28
#define SYSEX_W_DCO_LFO0_ATTACK                 29
#define SYSEX_W_DCO_LFO0_RELEASE                30
#define SYSEX_W_DCO_LFO0_DEPTH                  31

#define SYSEX_W_DCO_LFO1_MODE                   32
#define SYSEX_W_DCO_LFO1_SPEED                  33
#define SYSEX_W_DCO_LFO1_SHAPE                  34
#define SYSEX_W_DCO_LFO1_ATTACK                 35
#define SYSEX_W_DCO_LFO1_RELEASE                36
#define SYSEX_W_DCO_LFO1_DEPTH                  37

#define SYSEX_W_DCO_FILTER_CUTOFF               38
#define SYSEX_W_DCO_FILTER_RESONANCE            39

#define SYSEX_W_DCO_FILTER_KEY_FOLLOW_DEPTH     40
#define SYSEX_W_DCO_FILTER_KEY_VELOCITY_DEPTH   41
#define SYSEX_W_DCO_FILTER_KEY_AFTERTOUCH_DEPTH 42


struct i2c_reg_struct {									// i2c comm protocol support structure
	uint8_t addr;
	uint8_t cntr;
	uint8_t temporary_lsb;
	uint8_t temporary_msb;
};

struct dco_reg_struct {									// dco generator direct struture
	uint8_t	key_velocity;
	uint8_t	r2r;
	uint8_t divider;
	uint8_t counter_lsb;
	uint8_t counter_msb;
	uint8_t calibrate;
	uint8_t change;
	uint16_t virt_TA0CCR0;
	uint16_t virt_TA0CTL;
};

struct dac_reg_struct {									// dco generator support struture
	uint16_t dac0;
	uint16_t dac1;
	uint16_t virt_TA1CCR1;
	uint16_t virt_TA1CCR2;
};

//#define		ENV_MAX		0x3FFFFFFF
// <><---10bit--> <---------20bit-------->
// +r-- ---  ---- xxxx xxxx xxxx xxxx xxxx
// 0011 1111 1111 0000 0000 0000 0000 0000
//
// maximum increment: 1 072 693 248
// minimal increment:         1 023 (offset)
//
#define		ENV_MAX		0x3FF00000

#define		GATE_ON		0x01
#define		GATE_OFF	0x00

#define 	ATTACK		0
#define		DECAY		1
#define 	RELEASE		2

//
// devices (adsr, lfo)
//

// control pannel adsr 1:1 modifiers and internal adsr helpers
struct gen_adsr_struct {
	uint8_t 	gate,
				stage;
	int32_t		attack_step,
				decay_step,
				sustain_level,
				release_step;
	uint16_t	attack_step_parameter,
				decay_step_parameter,
				sustain_level_parameter,
				release_step_parameter;
	int32_t 	level;
};

// control pannel lfo 1:1 modifiers and internal lfo helpers
struct gen_lfo_struct {
	int16_t 	speed;
	uint8_t		shape;
	uint16_t 	sine_t_pos,
				sine_s_ctr;
};

#endif /* GLOBALS_H_ */
