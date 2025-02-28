/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: 
 *		to control led11 and led 10 through EINT buttons (similarly to project 03_)
 *		to control leds9 to led4 by the timer handler (1 second - circular cycling)
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/

                  
#include <stdio.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"

/* Led external variables from funct_led */
extern unsigned char led_value;					/* defined in lib_led								*/
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
void GPIO_Init(void) {
    LPC_GPIO2->FIODIR |= (1 << 0); // Configura P2.0 come uscita per il LED1 (TIMER2)
    LPC_GPIO2->FIODIR |= (1 << 1); // Configura P2.1 come uscita per il LED2 (TIMER3)
}

void configure_TIMER2_for_LED1(void) {
    uint32_t Prescaler = 0;        // Prescaler per ottenere 1 MHz (100 ns per tick a 100 MHz)
    uint32_t Period = 0X3D090;        // Periodo totale: 10 ms (100 Hz)
    uint32_t DutyCycle = 0X1E848;      // 50% Duty Cycle: LED acceso per 5 ms

    init_timer(2, Prescaler, 0, 3, Period); // Configura MR0: reset su Periodo
    init_timer(2, Prescaler, 1, 1, DutyCycle); // Configura MR1: interrupt su ON
		enable_timer(2);
    //LPC_TIM2->TCR = 0x01;           // Abilita TIMER2
}

void configure_TIMER3_for_LED2(void) {
    uint32_t Prescaler = 0;        // Prescaler per ottenere 1 MHz
    uint32_t Period = 0X7A120;        // Periodo totale: 20 ms (50 Hz)
    uint32_t DutyCycle = 0X3D090;     // 50% Duty Cycle: LED acceso per 10 ms

    init_timer(3, Prescaler, 0, 3, Period); // Configura MR0: reset su Periodo
    init_timer(3, Prescaler, 1, 1, DutyCycle); // Configura MR1: interrupt su ON
		enable_timer(3);
    //LPC_TIM3->TCR = 0x01;           // Abilita TIMER3
}


int main (void) {
  	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	
	LPC_SC -> PCONP |= (1 << 22);  // TURN ON TIMER 2
	LPC_SC -> PCONP |= (1 << 23);  // TURN ON TIMER 3	
	
	//GPIO_Init();                    // Inizializza GPIO per LED
  configure_TIMER2_for_LED1();    // Configura TIMER2
  configure_TIMER3_for_LED2();    // Configura TIMER3
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}


//	LPC_SC->PCONP |= (1 << 22); // Enable Timer 2
//  LPC_SC->PCONP |= (1 << 23); // Enable Timer 3