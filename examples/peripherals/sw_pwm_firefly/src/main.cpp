/*
===============================================================================
 Name        : FireFly
 Author      : uCXpresso
 Version     : v1.0.1
 Copyright   : www.ucxpresso.net
 Description : A software PWM demo
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/18 v1.0.0	First Edition.									LEO
 2015/2/16	v1.0.1	Use CMSIS DSP Library. (uCXpresso.NRF 1.0.6)	LEO
 ===============================================================================
 */

#include <uCXpresso.h>

#ifdef DEBUG
#include <debug.h>
#include <class/serial.h>
#define DBG dbg_printf
#else
#define DBG(...)
#endif

// TODO: insert other include files here
#include <class/pin.h>
#include <class/sw_pwm.h>
#include <arm_math.h>		// CMSIS DSP Library

// TODO: insert other definitions and declarations here
//#define BOARD_PCA10001
#define BOARD_NANO51822_UDK
#include <config/board.h>

//
// Main Routine
//
int main(void) {
#ifdef DEBUG
	CSerial ser;		// declare a UART object
	ser.enable();
	CDebug dbg(ser);	// Debug stream use the UART object
	dbg.start();
#endif

	//
	// Your setup code here
	//
	swPWM pwm(TIMER_1);
	pwm.period(0.01);		// set the period time of PWM to 10ms.
	pwm.enable();			// start the pwm

	int pins[] = {LED_PIN_0, LED_PIN_1, LED_PIN_2, LED_PIN_3};

	float y;
	int x[4] = { 0, 10, 20, 30 };        // initialize all channels x degree

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// FireFly loop
    	//
		for (int ch = 0; ch < 4; ch++) {
			x[ch] = (x[ch] + 10) % 360;							// degree 0~360, step by 2
			y = arm_sin_f32((x[ch] * M_PI) / 180.0f);           // y = sine @x
			pwm.output(pins[ch], map(y, -1.0f, 1.0f, 0.0f, 1.0f)); 	// update the duty-cycle of channel
		}
		sleep(10);    // speed
    }
}
