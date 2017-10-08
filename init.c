#include <msp430.h>
#include <stdint.h>
#include "globals.h"

extern struct dco_reg_struct 	dco_reg;

void init_gpio(void)
{
    P1SEL2 = BIT6 | BIT7;										// P1
    P1OUT = BIT0 | BIT1 | BIT2 | BIT3 | BIT4;
    P1SEL = BIT5 | BIT6 | BIT7;
    P1DIR = BIT5;
    P1REN = BIT0 | BIT1 | BIT2 | BIT3 | BIT4;
    P1IES = 0;
    P1IFG = 0;
    P2OUT = 0;													// P2
    P2SEL = BIT2 | BIT4 | BIT6 | BIT7;
    P2DIR = BIT2 | BIT3 | BIT4 | BIT5;
    P2REN = BIT0 | BIT1;
    P2IES = 0;
    P2IFG = 0;
    P3OUT = 0;													// P3
    P3DIR = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7;
}

void init_timer0(void)
{
	dco_reg.r2r = 0;
	dco_reg.virt_TA0CTL = TASSEL_2 | ID_3 | MC_3;
	dco_reg.virt_TA0CCR0 = 64792;
	P3OUT = 0;
	TA0CTL = TASSEL_2 | ID_3 | MC_3;
	TA0CCR0 = 64792;
	TA0CCTL0 = CM_0 | CCIS_0 | OUTMOD_4 | CCIE;
}

void init_timer1(void)
{
	TA1CCTL0 = CM_0 | CCIS_0 | OUTMOD_4 | CCIE;
    TA1CCTL1 = CM_0 | CCIS_0 | OUTMOD_3;
    TA1CCTL2 = CM_0 | CCIS_0 | OUTMOD_3;
    TA1CCR0 = PWMBASE;
    TA1CCR1 = 0;
    TA1CCR2 = 0;
    TA1CTL = TASSEL_2 | ID_0 | MC_1;
}

uint8_t set_i2c_addr(void) {
    uint8_t     i2c_dev_address;
    i2c_dev_address = P1IN;
    i2c_dev_address = (~i2c_dev_address) & 0x1f;
    i2c_dev_address += I2C_BASE_ADDR;
    return(i2c_dev_address);
}

void init_i2c(void)
{
    UCB0CTL1 |= UCSWRST;
    UCB0CTL0 = UCMODE_3 | UCSYNC;
    UCB0I2COA = set_i2c_addr();
    UCB0BR0 = 160;
    UCB0I2CIE = UCSTTIE;
    UCB0CTL1 &= ~UCSWRST;
    IFG2 &= ~(UCB0TXIFG | UCB0RXIFG);                   		/* IFG2, Interrupt Flag Register 2 */
    IE2 |= UCB0TXIE | UCB0RXIE;                         		/* IE2, Interrupt Enable Register 2 */
}

void init_clock(void) {
	BCSCTL2 = SELM_0 | DIVM_0 | DIVS_0;
	if (CALBC1_16MHZ != 0xFF) {
		__delay_cycles(200000); 								/* Adjust this accordingly to your VCC rise time */
		DCOCTL = 0x00;
		BCSCTL1 = CALBC1_16MHZ; 								/* Set DCO to 16MHz */
		DCOCTL = CALDCO_16MHZ;
	}
	BCSCTL1 |= XT2OFF | DIVA_0;
	BCSCTL3 = XT2S_0 | LFXT1S_0 | XCAP_1;
}
