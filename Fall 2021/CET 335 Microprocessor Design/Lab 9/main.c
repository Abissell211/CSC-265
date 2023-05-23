// ****************************** 0. Documentation Section ********************************
// main.c
// Runs on TM4C123
// Lab 9: PWM and Servo Motor Control
// Authors: Andrew D. Bissell
// Date: November 4, 2021

// Off Board hardware:
// Using breadboard
// Jumper Cables
// Power Supply Module, 9V 1A Power Supply, Servo Motor
// ****************************** 1. Pre-processor Directives Section *********************
//#include "TExaS.h"
//#include "uart.h"

// SysTick BASE = 							 0xE000E---
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Counter load value

// Pulse Width Modulation BASE = 0x40028---
#define PWM0_0_CTL_R						(*((volatile unsigned long *)0x40028040))	// PWMn_n_CTL,  n=(0 = 0x040, 1 = 0x080, 2 = 0x0C0, 3 = 0x100)
#define PWM0_0_GENB_R						(*((volatile unsigned long *)0x40028064))	// PWMn_n_GENB, n=(0 = 0x064, 1 = 0x0A4, 2 = 0x0E4, 3 = 0x124)
#define PWM0_0_LOAD_R						(*((volatile unsigned long *)0x40028050))	// PWMn_n_LOAD, n=(0 = 0x050, 1 = 0x090, 2 = 0x0D0, 3 = 0x110)
#define PWM0_0_CMPB_R						(*((volatile unsigned long *)0x4002805C))	// PWMn_n_CMPB, n=(0 = 0x05C, 1 = 0x09C, 2 = 0x0DC, 3 = 0x11C)
#define PWM0_ENABLE_R						(*((volatile unsigned long *)0x40028008))

// Clock Registers BASE = 			 0x400FE---
#define SYSCTL_RCGC0_R					(*((volatile unsigned long *)0x400FE100))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGCGPIO_R				(*((volatile unsigned long *)0x400FE608))
#define SYSCTL_RCC_R						(*((volatile unsigned long *)0x400FE060))

// PortB BASE =									 0x40005---
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x40005520))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
#define Output									(*((volatile unsigned long *)0x40005200))

// PortF BASE = 								 0x40025---
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
#define LED											(*((volatile unsigned long *)0x40025038))
	
// PLL requirements
//(Clock Register Base) =				 0x400FE---
#define SYSCTL_RCC2_R           (*((volatile unsigned long *)0x400FE070))
#define SYSCTL_RCC_R            (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RIS_R            (*((volatile unsigned long *)0x400FE050))
// N+1 = 400 MHz / Set Frequency
#define SYSDIV2    							 4                                
	
// ****************************** 2. Declarations Section *********************************
void PWM0B_Init(unsigned int period, unsigned int duty);
void PortF_Init(void);													// Initializes PortF
void EnableInterrupts(void);
void SysTick_Init(void);												// Initializes Systick Timer
void SysTick_Wait(unsigned long delay);					// Initializes Systick Delay using busy wait
																								// The delay parameter is in units of the core clock.
																								// (units of 20 nsec for 50 MHz clock)
void SysTick_Wait3ms(unsigned long delay);			// Initializes Systick Delay using busy wait
																								// This assumes 50 MHz system clock.
void PLL_INIT(void);														// Initializes the phase lock loop.

// ****************************** 3. Subroutines Section **********************************
int main(void){
	SysTick_Init();
	PortF_Init();
	PLL_INIT();
	EnableInterrupts();
	PWM0B_Init(50000, 3150);						// Initialize the PWM and send the servo to 0°
	while(1){		
	switch(GPIO_PORTF_DATA_R&0x11){			// Input PF4(SW1) Left bit, PF0(SW2) Right Bit
		
			case (0x11):										// SW1 not pressed, SW2 unpressed
				GPIO_PORTF_DATA_R = 0x02;			// Red output light for testing
				PWM0_0_CMPB_R = 3150 - 1;			// Send the servo to 0°
				SysTick_Wait3ms(1);						// Delay
				break;
			
			case (0x01):										// SW1 pressed, SW2 unpressed 
				GPIO_PORTF_DATA_R = 0x04;			// Blue output light for testing
				PWM0_0_CMPB_R = 5550 - 1;			// Send the servo to -90°
				SysTick_Wait3ms(1);						// Delay
				break;
			
			case (0x10):										// SW1 unpressed, SW2 pressed
				GPIO_PORTF_DATA_R = 0x08;			// Green output light for testing
				PWM0_0_CMPB_R = 1275 - 1;			// Send the servo to +90°
				SysTick_Wait3ms(1);						// Delay
				break;
			
			case (0x00):										// SW1 and SW2 pressed
				GPIO_PORTF_DATA_R = 0x0E;			// White output light for testing
				PWM0_0_CMPB_R = 5550 - 1;			// Send the servo to -90°
				SysTick_Wait3ms(500);					// Long delay to give time for the servo to make the full movement
				PWM0_0_CMPB_R = 1275 - 1;			// Send the servo to +90°
				SysTick_Wait3ms(500);					// Long delay to give time for the servo to make the full movement
				break;
		}
	}
}

void PWM0B_Init(unsigned int period, unsigned int duty){	// Output on PB7/M0PWM1
	volatile unsigned long delay;
	SYSCTL_RCGC0_R |= 			0x00100000;							// 1) Activate PWM0
	SYSCTL_RCGCGPIO_R |= 		0x02;										// 2) Activate port B
	delay = SYSCTL_RCGCGPIO_R;											// Allow time to finish activating
	GPIO_PORTB_AFSEL_R |= 	0x80;										// 3) Enable alt funtion on PB7
	GPIO_PORTB_PCTL_R &= 	 ~0xF0000000;							// 4) Configure PB7 as M0PWM1
	GPIO_PORTB_PCTL_R |= 		0x40000000;
	GPIO_PORTB_AMSEL_R &=  ~0x80;										// Disable analog funtionality on PB7
	GPIO_PORTB_DEN_R |= 		0x80;										// Enable digital I/O on PB7
	SYSCTL_RCC_R &= 			~(0x000E0000);						// 5) Clearing first
	SYSCTL_RCC_R |= 			 (0x00080000);						// The writing in the 19:17 with PWMDIV 0x3 configure for /32 divider
	SYSCTL_RCC_R |= 				0x00100000;							// Use PWM divider
	PWM0_0_CTL_R = 					0x00;										// 6) Re-loading down-counting mode
	PWM0_0_GENB_R = 			 (0x00000C00|0x00000008);	// 0xC8 in lesson		// PB7 goes low on LOAD, PB7 goes high on CMPB down
	PWM0_0_LOAD_R = 				period - 1;							// 7) Cycles needed to count down to 0
	PWM0_0_CMPB_R = 				duty - 1;								// 9) Count value when output rises
	PWM0_0_CTL_R |= 				0x00000001;							// 10) Start PWM0
	PWM0_ENABLE_R |= 				0x00000002;							// 11) Enable PB7/M0PWM1
}

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 		0x00000020; // 1) F clock
  delay = SYSCTL_RCGC2_R;           // 	  delay   
  GPIO_PORTF_LOCK_R = 	0x4C4F434B; // 2) unlock PortF PF0(SW2)  
  GPIO_PORTF_CR_R = 		0x1F;       // 	  allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 	0x00;       // 3) disable analog function
  GPIO_PORTF_PCTL_R = 	0x00000000; // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 		0x0E;       // 5) Inputs PF4(SW1),PF0(SW2)
																		//	  Outputs PF3(Green),PF2(Blue),PF1(Red) LEDs   
  GPIO_PORTF_AFSEL_R = 	0x00;       // 6) no alternate function
  GPIO_PORTF_PUR_R = 		0x11;       // 	  enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 		0x1F;       // 7) enable digital pins PF4-PF0        
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

void PLL_INIT(void){        
// 0) Use RCC2
SYSCTL_RCC2_R |=  0x80000000;  // USERCC2
// 1) bypass PLL while initializing
SYSCTL_RCC2_R |=  0x00000800;  // BYPASS2, PLL bypass
// 2) select the crystal value and oscillator source
SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)   // clear XTAL field, bits 10-6
+ 0x00000540;   // 10101, configure for 16 MHz crystal
SYSCTL_RCC2_R &= ~0x00000070;  // configure for main oscillator source
// 3) activate PLL by clearing PWRDN
SYSCTL_RCC2_R &= ~0x00002000;
// 4) set the desired system divider
SYSCTL_RCC2_R |= 0x40000000;   // use 400 MHz PLL
SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)  // clear system clock divider
+ (4<<22);      // configure for 80 MHz clock
// 5) wait for the PLL to lock by polling PLLLRIS
while((SYSCTL_RIS_R&0x00000040)==0){};  // wait for PLLRIS bit
// 6) enable use of PLL by clearing BYPASS
SYSCTL_RCC2_R &= ~0x00000800;
}
