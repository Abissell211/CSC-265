// Authors: 
// Summary:
// Inputs: 
// Outputs: 
// DATE
//======================================================================================================================//
/* 			0.DETAILS
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
				0A.ISSUES: 	
			
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
				0B.SUGGESTIONS: 
		[ ] FOR SYSTICK and PLL- Try changing it to use a DESIRED_FREQUENCY so its uniform instead of having a thousandth 
		defined value and an integer defined value
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
				0C.TODO:
				
		[ ] test that PLL, SYSTICK work properly
		
		[ ] test that porta interrupts work properly 
		
		[ ]	takes the input from the PORT A2 and count the number
				of times the switch is pressed and also toggle the RED LED on the PORTF
				whenever the switch is pressed.
				
		[ ] need to implement PORTF defines

		[ ] use systick delay of 10 ms in GPIO port a handler
		
		[ ] disableinterrupts and enableinterrupts needs included

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
				0D.DONE:

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
				0E.PROBLEMS SOLVED: 

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#include <stdio.h>   // standard C library 
#include "uart.h"    // functions to implment input/output
#include "TExaS.h"   // Lab grader functions
/*======================================================================================================================*/
/*========================================|		1. Pre-processor Directive Section	|=====================================*/

/*--------------------------------------------		1__PORT A INTERRUPT DEF		--------------------------------------------*/
/*- - - -	- - - - - - - - - - - - - - - - - - - - -   PORT A PIN DEFINE		- - - - - - - - - - - - - - - - - - - - - - - */
#define 	PIN_A2 			0x04
#define 	GPIO_PORTA_DATA_R     (*((volatile unsigned long *)0x400043FC))
#define 	GPIO_PORTA_DIR_R      (*((volatile unsigned long *)0x40004400))
#define 	GPIO_PORTA_PCTL_R     (*((volatile unsigned long *)0x4000452C))
#define 	GPIO_PORTA_DEN_R      (*((volatile unsigned long *)0x4000451C))
#define		GPIO_PORTA_LOCK_R     (*((volatile unsigned long *)0x40004520))
#define 	GPIO_PORTA_PUR_R      (*((volatile unsigned long *)0x40004510))
#define 	GPIO_PORTA_AFSEL_R    (*((volatile unsigned long *)0x40004420))
#define 	GPIO_PORTA_AMSEL_R    (*((volatile unsigned long *)0x40004528))
#define 	SYSCTL_RCGC2_R        (*((volatile unsigned long *)0x400FE108))
/*- - - -	- - - - - - - - - - - - - - - - - - - - -	PORT A INTERRUPT DEF	- - - - - - - - - - - - - - - - - - - - - - - */
#define 	GPIO_PORTA_IS_R       (*((volatile unsigned long *)0x40004404))
#define 	GPIO_PORTA_IBE_R     	(*((volatile unsigned long *)0x40004408))
#define 	GPIO_PORTA_IEV_R    	(*((volatile unsigned long *)0x4000440C))
#define 	GPIO_PORTA_IM_R       (*((volatile unsigned long *)0x40004410))
#define 	GPIO_PORTA_ICR_R 			(*((volatile unsigned long *)0x4000441C))
/*- - - -	- - - - - - - - - - - - - - - - - - - - - - - PORT F INIT - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define 	SYSCTL			0x400FE000					// System Control Register Base Address of 0x400F.E000 	Page 231
#define 	RCGCGPIO		0x608								// GPIO Run Mode Clock Gating Control offset 0x608 			Page 340
#define 	SYSCTL_RCGCGPIO_R			(*((volatile unsigned long *)(SYSCTL | RCGCGPIO)))
#define 	GPIO_PORTF	0x40025000					// GPIO PORTF Base Address 0x4002.5000 									Page 659
#define 	GPIO_DIR		0x400								// GPIO Direction offset 0x400													Page 663
#define 	GPIO_DEN		0x51C								// GPIO Digital Enable offset 0x51C											Page 682
#define 	GPIO_DATA		0x3FC								// GPIO Data Mask bits 9:2 offset												Page 662
#define 	GPIO_PORTF_DIR_R			(*((volatile unsigned long *)(GPIO_PORTF | GPIO_DIR)))
#define 	GPIO_PORTF_DEN_R			(*((volatile unsigned long *)(GPIO_PORTF | GPIO_DEN)))
#define 	GPIO_PORTF_DATA_R			(*((volatile unsigned long *)(GPIO_PORTF | GPIO_DATA)))
#define 	PORTF				0x20								// PORTF Bit Position
#define 	Red					0x02								// PF1 Red LED
/*- - - -	- - - - - - - - - - - - - - - - - - - - -	INTERRUPT PRIORITY DEF	- - - - - - - - - - - - - - - - - - - - - - */
#define 	NVIC_EN0_R            (*((volatile unsigned long *)0xE000E100))
#define 	NVIC_PRI0_R        		(*((volatile unsigned long *)0xE000E400))
	
/*-----------------------------------------------		1__SYSTICK	DEF				----------------------------------------------*/
#define 	NVIC_ST_CTRL_R				(*((volatile unsigned long *)0xE000E010))
#define 	NVIC_ST_RELOAD_R			(*((volatile unsigned long *)0xE000E014))
#define 	NVIC_ST_CURRENT_R			(*((volatile unsigned long *)0xE000E018))
#define 	THOUSANDTH_CLK_FREQ				80000

/*-----------------------------------------------		1__PHASE LOCK LOOP DEF		------------------------------------------*/
#define 	SYSCTL_RCC2_R					(*((volatile unsigned long *)0x400FE070))
#define 	SYSCTL_RCC_R					(*((volatile unsigned long *)0x400FE060))
#define 	SYSCTL_RIS_R					(*((volatile unsigned long *)0x400FE050))
#define 	SYSDIV2							4						// N+1 = 400 MHz / Desired_Frequency, where Desired_Frequency = 80MHz

/*======================================================================================================================*/
/*===========================================|		2. Declaration Section				|=======================================*/
unsigned long count;											// Incremented every time the switch is activated



/*--------------------------------------------		2__GLOBAL FUNCT PROTOTYPE	--------------------------------------------*/
void 		PortA_VectorInterrupt_Init(void);
void 		GPIOPortA_Handler(void);
void 		SYSTICK_INIT(void);
void 		SYSTICK_DELAY(unsigned long msec);
void 		PLL_INIT(void);
void		EnableInterrupts(void);
void		DisableInterrupts(void);
/*======================================================================================================================*/	
/*===========================================|		3. Main function 					|===========================================*/
int main(void){
	DisableInterrupts();
/*--------------------------------------------		3__VARIABLES INIT			------------------------------------------------*/

/*--------------------------------------------		3__FUNCTION INIT			------------------------------------------------*/

/*--------------------------------------------		3__STATUS INIT				------------------------------------------------*/
	SYSTICK_INIT();
	PLL_INIT();
	PortA_VectorInterrupt_Init();
	UART_Init();    // initialize UART for printing
/*--------------------------------------------    3__PORTF INIT					------------------------------------------------*/
	SYSCTL_RCGCGPIO_R |= PORTF;							// turn on bus clock for GPIO_PORTF											Page 340
	GPIO_PORTF_DIR_R |= Red;								// set PF3 GREEN pin as a digital output pin
	GPIO_PORTF_DEN_R |= Red;								// Enable PF3 GREEN pin as a digital pin
/*--------------------------------------------    3__POST INIT DECLARATIONS   ------------------------------------------*/
	count = 0;
	EnableInterrupts();
	GPIO_PORTF_DATA_R = 0x02;								// Toggle Red LED
/*--------------------------------------------		3__RUNNING					--------------------------------------------------*/
	while(1){
		// do nothing
	}

}
/*======================================================================================================================*/	
/*===========================================|		4. Subroutines and Functions		|=====================================*/
/*--------------------------------------------		4__PORTA INTERRUPT			----------------------------------------------*/
void 		PortA_VectorInterrupt_Init(void){	// SETS UP INTERRUPT ON PA2
/*- - - - - - - - - - - - - - - - - - - - - - - - -
REQUIRES: PORT A INTERRUPT DEF
RESULTS: Sets up PORT A PIN 2 to be a rising edge
		interrupt event with priority 4
- - - - - - - - - - - - - - - - - - - - - - - - -*/	
	
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000001;   				// 1) activate clock for Port A
	GPIO_PORTA_LOCK_R = 0x4C4F434B;   			//  unlock 
	delay = SYSCTL_RCGC2_R;           			// delay   
	GPIO_PORTA_DIR_R &= ~PIN_A2;          	//  PA2 as input
	GPIO_PORTA_AFSEL_R &= ~PIN_A2;        	//  no alternate function
	GPIO_PORTA_DEN_R |= PIN_A2;          		//  enable digital pins PE5
	GPIO_PORTA_PCTL_R &= ~0x000000F0;   		//  GPIO clear bit PCTL  
	GPIO_PORTA_AMSEL_R &= ~PIN_A2;        	//  disable analog function
	GPIO_PORTA_PUR_R &= ~PIN_A2;          	// no pullup  
	
	

	
	// PIN SPECIFIC: FOLLOWING FOR PA2 WHICH IS 0x04
	GPIO_PORTA_IS_R  	&= ~PIN_A2;        		// GPIOIS-Interrupt Sense [664]: Edge Sensitive {clear as 0}
	GPIO_PORTA_IBE_R 	&= ~PIN_A2;       		// GPIOIBE-Interrupt Both Edges [665]: Not both edges {clear as 0}
	GPIO_PORTA_IEV_R 	|= PIN_A2;       			// GPIOIVE-Interrupt Event [666]: Rising Edge {set as 1}
	GPIO_PORTA_ICR_R 	|= PIN_A2;          	// GPIOICR-Interrupt Clear [670]: Clear flag {1 = clear}
	GPIO_PORTA_IM_R  	|= PIN_A2;       			// GPIOIM-Interrupt Mask [667]: Arm the interrupt by allowing pin to send
	//	interrupt {set as 1}

	// NVIC_PRI0_R deals with priority interrupt for GPIO Port A through D
	// Want to clear the specific range and then reassign it
	//[Book 357]
	NVIC_PRI0_R	= (NVIC_PRI0_R&0xFFFFFF0F)| (4<<5); // bits 7-5 as target, Priority 4, Shift priority value into the 
	//location (5 here)
	NVIC_EN0_R 	|= 0x00000001;							// Port A is bit 0 [Page 104] for NVIC Enable, EN0 is bit 
																					//  numbers 0-31 [140]
}

void 		GPIOPortA_Handler(void){					// HANDLES PORTA INTERRUPTS (NOTABLY PA2)	
/*- - - - - - - - - - - - - - - - - - - - - - - - -
REQUIRES: GPIO_PORTA_ICR_R define, PIN_A2 define
RESULTS: 
- - - - - - - - - - - - - - - - - - - - - - - - -*/
	
	// Rising edge occurs
	GPIO_PORTA_ICR_R = PIN_A2;    					// acknowledge flag
	DisableInterrupts();										// Disable interrupt to stop switch debouncing

	
		
	// CODE GOES HERE UNTILL Return from Interrupt
	GPIO_PORTF_DATA_R ^= Red;								// Toggle Red LED
	count++;																// Increment count for times the switch is pushed
	printf("\nThe count is: %ld \n", count);
	SYSTICK_DELAY(1000);											// Delay 10ms
	EnableInterrupts();											// re-enable interrupts
	// Return from interrupt
}

/*--------------------------------------------		4__SYSTICK					------------------------------------------------*/
void 		SYSTICK_INIT(void){
/*- - - - - - - - - - - - - - - - - - - - - - - - -
REQUIRES: SYSTICK DEF
RESULTS: SYSTICK will be initialized and able to use for timing purposes.
- - - - - - - - - - - - - - - - - - - - - - - - -*/
	NVIC_ST_CTRL_R 		= 0;									// 1) Disable SYSTICK during set up
	NVIC_ST_RELOAD_R 	= 0x00FFFFFF;					// 2) MAX reload value
	NVIC_ST_CURRENT_R 	= 0;								// 3) Clear CURRENT by simply writing to it (any write to it clears it)
	NVIC_ST_CTRL_R		= 0x00000005;					// 4) Enable SYSTICK timer with core clock
}
void 		SYSTICK_DELAY(unsigned long msec){
/*- - - - - - - - - - - - - - - - - - - - - - - - -
REQUIRES: SYSTICK DEFINES, SYSTICK_INIT()
INPUTS: msec [unsigned long integer value]
RESULTS: SYSTICK will be used to form a time delay
of msec milliseconds (EX: msec = 1, resulting time delay = 1ms
- - - - - - - - - - - - - - - - - - - - - - - - -*/
	unsigned long i;																// Initialize a counter																	
	for (i=0; i<msec; i++){													//	wanted delay given as msec integer, will result in msec loops
		volatile unsigned long elapsedTime;						// Define an elapsed time for aach loop, as it will change between  
		//the for loops
		unsigned long startTime = NVIC_ST_CURRENT_R;	// Copy the current value, since NVIC_ST_CURRENT_R 
		//decrements with every bus cycle and instruction
		do{
			elapsedTime = 															// Measures the difference between start and what it
																									//  currently is
			(startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;		
		}while(elapsedTime <= THOUSANDTH_CLK_FREQ);		// Each loop is 1/Frequency, so doing it as many times 
																									//as the frequency would yield 1 s. Ding it by 1/1000 of the frequency yields 1ms

	}
}
/*--------------------------------------------		4__PHASE LOCK LOOP			------------------------------------------------*/
void 		PLL_INIT(void){	
/*- - - - - - - - - - - - - - - - - - - - - - - - -
REQUIRES: PHASE LOCK LOOP DEF
RESULTS: The microprocessor's clock will be more accurate, utilizing
the phase loop loop circuitry rather and crystal rather than the oscillator
- - - - - - - - - - - - - - - - - - - - - - - - -*/	
																							// 0) Use RCC2
	SYSCTL_RCC2_R |=  0x80000000;  								// USERCC2
																							// 1) bypass PLL while initializing
	SYSCTL_RCC2_R |=  0x00000800;  								// BYPASS2, PLL bypass
																							// 2) select the crystal value and oscillator source
	SYSCTL_RCC_R = (SYSCTL_RCC_R &~(5<<6)) 				// clear XTAL field, bits 10-6
	+ 0x00000540;   															// 10101 configure for 16 MHz crystal
	SYSCTL_RCC2_R &= ~0x00000070;  								// configure for main oscillator source
																							// 3) activate PLL by clearing PWRDN
	SYSCTL_RCC2_R &= ~0x00002000;
																							// 4) set the desired system divider
	SYSCTL_RCC2_R |= 0x40000000;   								// use 400 MHz PLL
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000) 	// clear system clock divider
	+ (SYSDIV2<<22);      												// configure for XX MHz clock [Determined by SYSDIV2, check THOUSANDTH FREQ]
																							// 5) wait for the PLL to lock by polling PLLLRIS
	while((SYSCTL_RIS_R&0x00000040)==0){};  			// wait for PLLRIS bit
																							// 6) enable use of PLL by clearing BYPASS
	SYSCTL_RCC2_R &= ~0x00000800;									// BYPASS2, PLL bypass
}
