#include <msp430.h>
#include <stdint.h>
#include "globals.h"
#include "sysex.h"

extern struct i2c_reg_struct i2c_reg;								// i2c helper (addr, cntr, temporary_lsb, temporary_msb)
extern struct dco_reg_struct dco_reg;								// dco reg
extern struct dac_reg_struct dac_reg;								// for lfo
extern struct gen_adsr_struct adsr0;

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR_HOOK(void)								// in I2C mode the TX interrupt is called for RX __and__ TX
{
	uint8_t rx_buf;													// rx_buf is local
	if (IFG2 & UCB0TXIFG) {            								// callback to transmit bytes (READ ADDR)
		switch (i2c_reg.addr) {
		case REG_B_DEVTYPE:
			UCB0TXBUF = DEV_TYPE_DCO;                       		// identify itself
			break;
		default:
			UCB0TXBUF = 0xff;                         				// default response on any
			break;                                 					// not known register is 0xff
		}
	// send TX reply
	} else if (IFG2 & UCB0RXIFG) {   								// callback for bytes received (WRITE ADDR)
		rx_buf = UCB0RXBUF;                                			// load rx_buf
		if (i2c_reg.cntr == 0) {            						// i2c_cntr == 0 == register address
			i2c_reg.addr = rx_buf;        							// save <REGISTER> address in i2c_addr
			i2c_reg.cntr++;
		} else {                          							// code for specific <REGISTER> values

			switch (i2c_reg.addr) {									// switch

			case REG_B_LED:                                 		// REGISTER is 8bit
				if (!rx_buf) {                              		// diode off
					P2OUT &= ~(BIT5);
				} else {                                   			// diode on
					P2OUT |= BIT5;
				}
				i2c_reg.cntr++;										// can be omited
				break;

			case REG_B_R2R:                                 		// REGISTER is 8bit
				dco_reg.r2r = rx_buf;                       		// read R2R
				i2c_reg.cntr++;										// can be omited
				break;

			case REG_B_DIVIDER:                             		// REGISTER is 8bit
				dco_reg.divider = rx_buf;            				// read divider from rx_buf
				i2c_reg.cntr++;										// can be omited
				break;

			case REG_W_COUNTER:                             		// REGISTER is 16bit
				switch (i2c_reg.cntr) {
				case 1:
					dco_reg.counter_lsb = rx_buf; 					// Adafruit I2C lib send lsb first
					i2c_reg.cntr++;
					break;
				case 2:
					dco_reg.counter_msb = rx_buf;           		// read msb
					i2c_reg.cntr++;
					break;
				}
				break;

			case REG_B_CONTROL:                             		// REGISTER is 8bit
				if(rx_buf & BIT5) {
					dco_reg.virt_TA0CCR0 = dco_reg.counter_msb; 	// fill word of CCR0 (compare register value)
					dco_reg.virt_TA0CCR0 = dco_reg.virt_TA0CCR0 << 8; // with value received (msb+lsb)
					dco_reg.virt_TA0CCR0 |= dco_reg.counter_lsb;

					if (dco_reg.divider == 1) {                		// osc divider /1
						dco_reg.virt_TA0CTL = TASSEL_2 | ID_0 | MC_1; // MC_1 -- Timer A mode control: 1 - Up to CCR0
					} else if (dco_reg.divider == 2) {         		// osc divider /2
						dco_reg.virt_TA0CTL = TASSEL_2 | ID_1 | MC_1; // MC_1 -- Timer A mode control: 1 - Up to CCR0
					} else if (dco_reg.divider == 4) {         		// osc divider /4
						dco_reg.virt_TA0CTL = TASSEL_2 | ID_2 | MC_1; // MC_2 -- Timer A mode control: 1 - Up to CCR0
					} else if (dco_reg.divider == 8) {         		// osc divider /8
						dco_reg.virt_TA0CTL = TASSEL_2 | ID_3 | MC_1; // MC_2 -- Timer A mode control: 1 - Up to CCR0
					} else if (dco_reg.divider == 16) { 			// osc divider /16 (8 + up&down mode)
						dco_reg.virt_TA0CTL = TASSEL_2 | ID_3 | MC_3; // MC_3 -- Timer A mode control: 3 - Up/Down
					}
					dco_reg.change = 1; 							// allow to apply changes while TIMER IRQ
				}
				if (rx_buf & BIT6) {
					P2OUT ^= BIT5;                              	// toggle LED
				}
				if (rx_buf & BIT7) {
					P2OUT |= BIT3;                              	// GATE on
					adsr0.gate = GATE_ON;
				} else {
					P2OUT &= ~(BIT3);                           	// GATE off
					adsr0.gate = GATE_OFF;
				}
				i2c_reg.cntr++;
				break;

			case REG_B_CALIBRATE:                            		// REGISTER is 8bit
				dco_reg.calibrate = 1;                   			// set calibration flag
				i2c_reg.cntr++;										// can be omited
				break;

			case REG_B_KEY_VELOCITY:
				dco_reg.key_velocity = rx_buf;
				i2c_reg.cntr++;										// can be omited
				break;

			default:
				sysex_message(rx_buf);
				break;
			}
		}
	}
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR_HOOK(void) { 							// in I2C mode the RX interrupt is called for STATE handling ONLY!
	if (UCB0STAT & UCSTTIFG) {                      				// START condition interrupt
		i2c_reg.cntr = 0;                   						// transmission begins, 1 == pending
		UCB0STAT &= ~UCSTTIFG;                 						// clear start condition int flag
	} else if (UCB0STAT & UCSTPIFG) {  								// STOP condition interrupt, 1 == pending
		UCB0STAT &= ~UCSTPIFG;                  					// clear stop condition int flag
	} else if (UCB0STAT & UCNACKIFG) {                      		// NACK (if master)
		UCB0STAT &= ~UCNACKIFG;										// slave not acknowledged received data
	} else if (UCB0STAT & UCALIFG) { 								// two or more masters start trans. simultaneously
									 	 	 	 	 	 	 	 	// master code
	}
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR_HOOK(void) {
	if (dco_reg.change) {
		TA0CTL = dco_reg.virt_TA0CTL;                   			// set TA0CTL
		TA0CCR0 = dco_reg.virt_TA0CCR0;                  			// set TA0CCR0
		P3OUT = dco_reg.r2r;                          				// set P3
		dco_reg.change = 0;                          				// reset request for change
	}
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR_HOOK(void) {
	TA1CCR1 = dac_reg.virt_TA1CCR1;
	TA1CCR2 = dac_reg.virt_TA1CCR2;
}
