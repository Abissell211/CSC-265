// ****************************** 0. Documentation Section ********************************
// main.c
// Runs on TM4C123
// Lab 6, Input from PE0, output to PE1 LED
// Authors: Andrew D. Bissell, Charles Krug
// Date: October 7, 2021

// Off Board hardware
// Using breadboard
// Switch, Green LED, Jumper Cables
// Resistor: 10k ohm, 470 ohm
// ****************************** 1. Pre-processor Directives Section *********************
#include "TExaS.h"

#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *)0x40024520))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
// ****************************** 2. Declarations Section *********************************

// 		Function Prototypes
void PortE_Init(void);
void EnableInterrupts(void);
void Delay1ms(unsigned long);

// ****************************** 3. Subroutines Section **********************************
int main(void){
	PortE_Init();
	EnableInterrupts();
	while(1){														// Loop forever
		while((GPIO_PORTE_DATA_R&0x01) != 00){
			GPIO_PORTE_DATA_R |= 0x02;
			Delay1ms(5);
		  GPIO_PORTE_DATA_R &= 0xFD;	
			Delay1ms(5);			
		}
	  GPIO_PORTE_DATA_R &= 0xFD;
	}																		
}

// Subroutine to initialize port E pins for input and output
// PE0 Input
// PE1 Output
// Inputs: None
// Outputs: None
void PortE_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010;     	// 1) E clock
  delay = SYSCTL_RCGC2_R;           	// 	  delay   
  GPIO_PORTE_LOCK_R = 0x4C4F434B;   	// 2) unlock PortE 
  GPIO_PORTE_CR_R = 0x03;           	// 	  allow changes PE0 and PE1      
  GPIO_PORTE_AMSEL_R = 0x00;       	 	// 3) disable analog function
  GPIO_PORTE_PCTL_R = 0x00000000;   	// 4) GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R = 0x02;          	// 5) Input PE0, Output PE1   
  GPIO_PORTE_AFSEL_R = 0x00;        	// 6) no alternate function      
  GPIO_PORTE_DEN_R = 0x03;          	// 7) enable digital pins PE0, PE1        
}

// Subroutine to initiate delays in the program
// Inputs: Time in ms to create delay
// Outputs: (1ms delay) x (the value given to subroutine)
void Delay1ms(unsigned long time){
	unsigned long i;
	while(time > 0){
		i = 13333;
		while(i > 0){
			i = i - 1;
		}
		time = time - 1;
	}
}
