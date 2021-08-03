/*
 * Sine wave  generator
 *
 * Created: 8/2/2021 10:44:55 AM
 * 
 * Author: RAJAT MISHRA
 
 * Hardware: AVR128DA48 
 
 */ 


#define  F_CPU	4000000UL
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>
#include "UART_1_AVR128DA64.h"
#include "MPRSS_sensor.h"
#include "Motorcontrol.h"
#define PI 3.14
#define AMPLITUDE 5   //Amplitude value
#define AMP ((AMPLITUDE*255)/5)
#define frequency 0.1 //frequency of sine wave
float output = 0.0;
unsigned long milliseconds = 0,millis;
float amp_value=0;
void sineWave(void);


void set_millis(void)
{
	sei();
	TCB0_CCMP = 3999;				// Write a TOP value to the Compare/Capture (TCBn.CCMP) register
	
	TCB0_CTRLB |= (0x0 << 0);
	TCB0_INTCTRL |= (1<<0);
	
	TCB0_CTRLA |= (1<<0)|(0x0 <<1); // ENABLE bit in the Control A (TCBn.CTRLA) register,
}

ISR(TCB0_INT_vect)
{
	millis++;
	TCB0_INTFLAGS |= (1<<0);
}



int main(void)
{
	 set_millis();
	 USART1_init(9600);
	 Pressure_init();
	 TCA0_PWM_init();    //Initialize PA0 pin as PWM pin for motor
	  // 	 _delay_ms(1000);
// 	 USART1_sendString("Hello");
	SET_DUTYCYCLE(1024);
    while(1)
    { 
      // sineWave(); 
	  Pressure_read();
	  
	  // USART1_sendFloat(pressure,1);
	   
    }
}
void sineWave(void)
{
	milliseconds = millis;
	int t = 0;
	while (t < 10000)
	{
		output=AMP* sin(2 * PI * frequency * t * 0.001);
		 if(output < 0.0)
		 {
			 output = 0.0;
		 }
		USART1_sendFloat(output, 1);
					
	     t = millis - milliseconds;
		 
		
	}
	
	 milliseconds = 0;


}