#include "button.h"
#include "LPC17xx.h"


#include "../led/led.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"		  			/* you now need RIT library 			 */

extern unsigned int buffer[];
double avg;

void bubble_sort(unsigned int buffer[], int n) {
	int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (buffer[j] > buffer[j + 1]) {
                unsigned int temp = buffer[j];
                buffer[j] = buffer[j + 1];
                buffer[j + 1] = temp;
            }
        }
        
    }

	}

double buffer_average(unsigned int buffer[], int n){
		int i =0;
		unsigned int sum=0;
		for(i=0;i<n;i++){
			sum = sum + buffer[i];
		}

		return (double) (sum/n);
	}
	
void buffer_clean(unsigned int buffer[], int n, unsigned int pattern){
		int i=0;
		for(i=0;i<n;i++){
			buffer[i]=pattern;
		}
	}

void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	enable_RIT();										/* enable RIT to count 50ms				 */
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4  &= ~(1 << 22);     /* GPIO pin selection */
	bubble_sort(buffer, 7000);
	avg = buffer_average(buffer, 7000);
	buffer_clean(buffer, 7000, 0xCAFECAFE);
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
	
}

void EINT0_IRQHandler (void)	  	/* INT0														 */
{
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}




void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */  
	enable_timer(0);  
}


