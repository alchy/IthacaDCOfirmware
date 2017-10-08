#include <stdint.h>
#include "globals.h"
#include "gen_sine.h"
#include "gen_table_sine.h"

int16_t get_sine(uint16_t position) {
	// @ inputs: position in wave 0 - 2047
	if(position < 1024) {										// sine table has 512 bytes == 1/4th of a whole cycle
		if(position < 512) {									// Q1
			return(sinetable[position]);
		} else {												// Q2
			position = 511 + (512 - position);
			return(-1 * sinetable[position]);
		}
	} else {													// Q3
		if(position < 1024 + 512) {
			position = -1 * (1024 - position);
			return(-1 * sinetable[position]);
		} else {												// Q4
			position = 1023 + 1024 - position;
			return(sinetable[position]);
		}
	}
}

int16_t sine(struct gen_lfo_struct *lfo) {
	// @ input params:
	// @ 	input speed: 		0 - 1023 /10bit/
    // @ 	input modulation: 	0 - 1023 /10bit/
    // @ 	function output: 	0 - 1023 /10bit/
	// @ output:
	// @ 	signed 10bit number
    int32_t sine;
    if(lfo->sine_s_ctr < lfo->speed) {						// speed == 0, full speed
        lfo->sine_s_ctr++;
    } else {
        lfo->sine_s_ctr = 0;								// reset speed
        if(lfo->sine_t_pos < 2047) {						// table overflow?
            lfo->sine_t_pos++;
        } else {
            lfo->sine_t_pos = 0;
        }
    }
    sine = get_sine(lfo->sine_t_pos);						// get sine +/- 1023 (11bit)
    return(sine);											// return __signed__ 10+1bit value (11bit range)
}
