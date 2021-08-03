/*
 * Motorcontrol.h
 *
 * Created: 8/3/2021 4:39:26 PM
 *  
 * Author: RAJAT
 */ 


#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_
#define F_CPU							(4000000UL)

#include <avr/io.h>
#include <util/delay.h>


int  dutyCycle1  = 1024;			// MAX Value	1024 FOR 12V


void TCA0_PWM_init(void);
void PWM_Condition1(void);





void TCA0_PWM_init(void)
{
	//sei();
	/*		FIRST PWM on PA0 PIN		*/
	// Direction set and set output to high
	PORTA.DIR |= (1 << 0);
	PORTE.DIR |= (1 << 0);			// SOL 1	OUTPUT		PE0
	PORTE.DIR |= (1 << 1);
	
	PORTA.PIN0CTRL |= (1 << 3);
	//PORTA.OUTSET |= (1 << 0);
	TCA0.SINGLE.PER = 3990;     // calculation for 1ms
	TCA0.SINGLE.CMP0 = dutyCycle1;
	TCA0.SINGLE.CNT = 0;

	TCA0.SINGLE.CTRLA |= (0x0 << 1); //Ftca = fclk_per
	TCA0.SINGLE.CTRLB |= (1 << 4); // compare 0 enable
	TCA0.SINGLE.CTRLB |= (0x3 << 0); // Single slope PWM
	TCA0.SINGLE.CTRLA |= (1 << 0);  // Enable PWM
	
	// 	/*		Second PWM on PA1 PIN		*/
	//
	// 	PORTA.DIR |= (1 << 1);						// Direction set and set output to high
	// 	PORTA.PIN1CTRL |= (1 << 3);
	// 	TCA0.SINGLE.CTRLB |= (1 << 5);				// Enable Compare Pa1
	// 	TCA0.SINGLE.CTRLA |= (1 << 1);				// Enable PWM PA1
	// 	TCA0.SINGLE.CMP1 = dutyCycle2;					// Duty cycle

}

void PWM_Condition1(void)
{
	if (dutyCycle1 > 1024)
	{
		dutyCycle1  = 1024;
	}
	else if (dutyCycle1 < 0)
	{
		dutyCycle1 = 0;
	}
}








#endif /* MOTORCONTROL_H_ */