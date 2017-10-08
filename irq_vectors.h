/*
 * irq_vectors.h
 *
 *  Created on: 20. 7. 2016
 *      Author: Jindra
 */

#ifndef IRQ_VECTORS_H_
#define IRQ_VECTORS_H_

__interrupt void USCI0TX_ISR_HOOK(void);
__interrupt void USCI0RX_ISR_HOOK(void);
__interrupt void TIMER0_A0_ISR_HOOK(void);
__interrupt void TIMER1_A0_ISR_HOOK(void);


#endif /* IRQ_VECTORS_H_ */
