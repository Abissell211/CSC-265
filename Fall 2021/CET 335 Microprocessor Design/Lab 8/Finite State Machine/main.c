// ****************************** 0. Documentation Section ********************************
// main.c
// Runs on TM4C123
// Lab 8: Stepper Motor Control(FSM)
// Authors: Andrew D. Bissell, Charles Krug
// Date: November 1, 2021

// Off Board hardware:
// Using breadboard
// Jumper Cables
// Power Supply Module, 9V 1A Power Supply, ULN2003 Stepper Motor Driver Board, Stepper Motor
// ****************************** 1. Pre-processor Directives Section *********************
#include "TExaS.h"
#include "uart.h"

#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Counter load value

#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x40005520))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
// Define the actual switch 1 for use in functions
#define SW1											(*((volatile unsigned long *)0x40025040))
// Define the actual switch 2 for use in functions	
#define SW2											(*((volatile unsigned long *)0x40025004))		
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))

#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
																																						// 8   4   2   1 . 8   4   2   1
																																						// 0  PF4 PF3 PF2.PF1 PF0  0   0
#define SENSOR									(*((volatile unsigned long *)0x40025044))   // PF4(SW1), PF0(SW2)
	
																																						// 8   4   2   1 . 8   4   2   1
																																						// 0   0  PB3 PB2.PB1 PB0  0   0
#define MOTOR										(*((volatile unsigned long *)0x4000503C))		// PB0 - PB3 (all outputs)

// ****************************** 2. Declarations Section *********************************
void PortB_Init(void);       		  					// Initializes PortB
void PortF_Init(void);											// Initializes PortF
void EnableInterrupts(void);
void SysTick_Init(void);										// Initializes Systick Timer
void SysTick_Wait(unsigned long delay);			// Initializes Systick Delay using busy wait
																						// The delay parameter is in units of the core clock.
																						// (units of 20 nsec for 50 MHz clock)
void SysTick_Wait3ms(unsigned long delay);	// Initializes Systick Delay using busy wait
																						// This assumes 50 MHz system clock.

typedef struct StateStructure{
	unsigned long OUTPUT;										// Output for the state
	unsigned long Time;											// Delay for the state
	unsigned long Next[4];									// Array for the next states
}State;
								
#define HS0 0
#define HS1 1
#define HS2 2
#define HS3 3
#define HS4 4
#define HS5 5
#define HS6 6
#define HS7 7

State FSM[8] =
{				//  00   01   10   11	  // 0 = pressed, 1 = unpressed
	{0x08,5, {HS7, HS3, HS7, HS1}},					// State 0
	{0x0C,5, {HS7, HS3, HS0, HS2}},					// State 1
	{0x04,5, {HS1, HS5, HS1, HS3}},					// State 2
	{0x06,5, {HS1, HS5, HS2, HS4}},					// State 3
	{0x02,5, {HS3, HS7, HS3, HS5}},					// State 4
	{0x03,5, {HS3, HS7, HS4, HS6}},					// State 5
	{0x01,5, {HS5, HS1, HS5, HS7}},					// State 6
	{0x09,5, {HS5, HS1, HS6, HS0}},					// State 7
};
unsigned long S;														// Current state value
unsigned long Input;												// Input for states
unsigned long In1;													// SW1 input
unsigned long In2;													// SW2 input

// ****************************** 3. Subroutines Section **********************************
int main(void){
	TExaS_Init(UART_PIN_PA0,UART_PIN_PA1);
	UART_Init();
	SysTick_Init();
	PortB_Init();
	PortF_Init();
	EnableInterrupts();
	while(1){														// Loop forever
		MOTOR = FSM[S].OUTPUT;						// Set the output to the motor using the current state
		SysTick_Wait3ms(FSM[S].Time);			// Get the delay from the current state
		In1 = SENSOR;											// Read in first input from sensor (SW1)
		In2 = SENSOR >> 3;								// Read in second input from sensor (SW2)
		Input = (In1 + In2) & 0x03;				// Set the input for the next state
		S = FSM[S].Next[Input];						// Set the next state using the input
		}
	}

void PortB_Init(void){
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000002;     	// 1) B clock
  delay = SYSCTL_RCGC2_R;           	// delay   
  GPIO_PORTB_LOCK_R = 0x4C4F434B;   	// 2) unlock   
  GPIO_PORTB_CR_R = 0x3F;           	// allow changes to PB5-0       
  GPIO_PORTB_AMSEL_R = 0x00;        	// 3) disable analog function
  GPIO_PORTB_PCTL_R = 0x00000000;   	// 4) GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R = 0x3F;          	// 5) PB5-0 out   
  GPIO_PORTB_AFSEL_R = 0x00;        	// 6) no alternate function
  GPIO_PORTB_PUR_R = 0x00;          	// No internal resistor      
  GPIO_PORTB_DEN_R = 0x3F;          	// 7) enable digital pins PB5-0
}

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     	// 1) F clock
  delay = SYSCTL_RCGC2_R;           	// 	  delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   	// 2) unlock PortF PF0(SW2)  
  GPIO_PORTF_CR_R = 0x1F;           	// 	  allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;       	 	// 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   	// 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          	// 5) Inputs PF4(SW1),PF0(SW2)
																			//	  Outputs PF3(Green),PF2(Blue),PF1(Red) LEDs   
  GPIO_PORTF_AFSEL_R = 0x00;        	// 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          	// 	  enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          	// 7) enable digital pins PF4-PF0        
}

// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
}

// Time delay using busy wait.
// The delay parameter is in units of the core clock. (units of 20 nsec for 50 MHz clock)
void SysTick_Wait(unsigned long delay){
  volatile unsigned long elapsedTime;
  unsigned long startTime = NVIC_ST_CURRENT_R;
  do{
    elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }
  while(elapsedTime <= delay);
}

// Time delay using busy wait.
// This assumes 50 MHz system clock.
void SysTick_Wait3ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    SysTick_Wait(150000);  // wait 3ms (assumes 50 MHz clock)
  }
}
