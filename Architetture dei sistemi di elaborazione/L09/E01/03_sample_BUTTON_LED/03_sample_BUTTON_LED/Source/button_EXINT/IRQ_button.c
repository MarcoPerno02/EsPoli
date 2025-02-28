#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"

extern unsigned char current_state; // Seed iniziale (10101010 in binario)
extern unsigned char taps;          // Taps per i bit 3, 4, 5, 7
extern int output_bit;

void EINT0_IRQHandler (void)	  
{
	current_state = next_state(current_state, taps, &output_bit);
	// Mostra lo stato sui LED
	LPC_GPIO2->FIOCLR = 0xFF;    // Spegni tutti i LED
	LPC_GPIO2->FIOSET = current_state; // Mostra lo stato sui 
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{
  LED_On(1);
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
	LED_Off(0);
	LED_Off(1);
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


