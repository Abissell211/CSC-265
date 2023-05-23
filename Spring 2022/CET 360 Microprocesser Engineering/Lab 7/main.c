// ****************************** 0. Documentation Section ********************************
// main.c
// Runs on TM4C123
// Project: Ultrasonic Rangefinder
// Authors: Andrew Bissell, Noah Proctor
// Date: 03/31/2022 

// Off Board hardware:
// Breadboard, jumper cables
// Power Supply Module, 9V 1A Power Supply, HC-SR04 Ultrasonic Ranging Module
// ----------------------------------------------------------------------------------------
// ****************************** 1. Pre-processor Directives Section *********************
// ----------------------------------------------------------------------------------------
#include <stdio.h>   						// standard C library 
#include "uart.h"								// Uart for outputing to user

#define SysTick_Base					0xE000E000
#define CTRL									0x010
#define RELOAD								0x014
#define CURRENT								0x018

#define NVIC_ST_CTRL_R				(*((volatile unsigned long *)(SysTick_Base | CTRL)))
#define NVIC_ST_RELOAD_R			(*((volatile unsigned long *)(SysTick_Base | RELOAD)))
#define NVIC_ST_CURRENT_R			(*((volatile unsigned long *)(SysTick_Base | CURRENT)))
#define THOUSANDTH_CLK_FREQ		80000
#define NVIC_ST_RELOAD_M      0x00FFFFFF  // Reload Value
#define NVIC_ST_CTRL_ENABLE   0x00000001  // Enable
#define NVIC_ST_CTRL_CLK_SRC  0x00000004  // Clock Source
//----------------------------------------------------Clock Registers----------------------------------------------------------//
#define SYSCTL								0x400FE000
#define RCGC0									0x100
#define RCGC2									0x108
#define RCGCGPIO							0x608
#define RCC										0x060

#define RCC2									0x070
#define RIS										0x050

#define SYSCTL_RCGC0_R				(*((volatile unsigned long *)(SYSCTL | RCGC0)))
#define SYSCTL_RCGC2_R				(*((volatile unsigned long *)(SYSCTL | RCGC2)))
#define SYSCTL_RCGCGPIO_R			(*((volatile unsigned long *)(SYSCTL | RCGCGPIO)))
#define SYSCTL_RCC_R					(*((volatile unsigned long *)(SYSCTL | RCC)))
#define SYSCTL_RCC2_R					(*((volatile unsigned long *)(SYSCTL | RCC2)))
#define SYSCTL_RIS_R					(*((volatile unsigned long *)(SYSCTL | RIS)))
//-----------------------------------------------------GPIO Constants----------------------------------------------------------//
#define PORTB_BASE						0x40005000
#define PORTB_Output					(*((volatile unsigned long *)(PORTB_BASE | 0x200)))
#define PIN_B3								0x08
#define PIN_B4								0x10

#define PORTF_BASE						0x40025000
#define PORTF									0x20
#define RED										0x02
#define GREEN									0x08

#define DATA									0x3FC
#define DIR										0x400
#define AFSEL									0x420
#define PUR										0x510
#define DEN										0x51C
#define GCR										0x524
#define LOCK									0x520
#define AMSEL									0x528
#define PCTL									0x200

#define GPIO_PORTB_DATA_R			(*((volatile unsigned long *)(PORTB_BASE | DATA)))
#define GPIO_PORTB_DIR_R			(*((volatile unsigned long *)(PORTB_BASE | DIR)))
#define GPIO_PORTB_AFSEL_R		(*((volatile unsigned long *)(PORTB_BASE | AFSEL)))
#define GPIO_PORTB_PUR_R			(*((volatile unsigned long *)(PORTB_BASE | PUR)))
#define GPIO_PORTB_DEN_R			(*((volatile unsigned long *)(PORTB_BASE | DEN)))
#define GPIO_PORTB_LOCK_R			(*((volatile unsigned long *)(PORTB_BASE | LOCK)))
#define GPIO_PORTB_AMSEL_R		(*((volatile unsigned long *)(PORTB_BASE | AMSEL)))
#define GPIO_PORTB_PCTL_R			(*((volatile unsigned long *)(PORTB_BASE | PCTL)))
	
#define GPIO_PORTF_DATA_R			(*((volatile unsigned long *)(PORTF_BASE | DATA)))
#define GPIO_PORTF_DIR_R			(*((volatile unsigned long *)(PORTF_BASE | DIR)))
#define GPIO_PORTF_DEN_R			(*((volatile unsigned long *)(PORTF_BASE | DEN)))
#define GPIO_PORTF_LOCK_R			(*((volatile unsigned long *)(PORTF_BASE | LOCK)))
#define GPIO_PORTF_CR_R				(*((volatile unsigned long *)(PORTF_BASE | GCR)))
#define GPIO_PORTF_PUR_R			(*((volatile unsigned long *)(PORTF_BASE | PUR)))
#define GPIO_PORTF_PCTL_R			(*((volatile unsigned long *)(PORTF_BASE | PCTL)))
#define GPIO_PORTF_AFSEL_R		(*((volatile unsigned long *)(PORTF_BASE | AFSEL)))
#define GPIO_PORTF_AMSEL_R		(*((volatile unsigned long *)(PORTF_BASE | AMSEL)))

#define Trigger								(*((volatile unsigned long *)0x40005100))
#define Echo									(*((volatile unsigned long *)0x50005200))	
#define LED										(*((volatile unsigned long *)0x40025038))
#define SW1										(*((volatile unsigned long *)0x40025040))
#define SW2										(*((volatile unsigned long *)0x40025004))

// FSM Variables
#define LIGHT		 							(*((volatile unsigned long *)0x4000503C))		// PortB for LEDs all outputs
// ********************************** a. STATES *******************************************
#define RLED  0
#define YLED  1
#define GLED  2
#define WLED  3
// ----------------------------------------------------------------------------------------
// ****************************** 2. Declarations Section *********************************
// ----------------------------------------------------------------------------------------
// ****************************** a. Function Prototypes **********************************
void PortF_Init(void);													// Initializes PortF
void PortB_Init(void);													// Initializes PortB
void EnableInterrupts(void);										// Allow interrupts in the program to occur
void SysTick_Init(void);												// Initializes Systick Timer
void SysTick_Wait(unsigned long delay);					// Initializes Systick Delay using busy wait
void SysTick_Wait1ms(unsigned long delay);
																								// The delay parameter is in units of the core clock.
																								// (units of 20 nsec for 50 MHz clock)
void SysTick_Wait10us(unsigned long delay);			// Initializes Systick Delay using busy wait
																								// This assumes 50 MHz system clock.
void PLL_INIT(void);														// Initializes the phase lock loop.
int Find_Range(unsigned long Echo_PIN, unsigned long Trigger_PIN);
// ******************************** b. Global Variables ***********************************
unsigned int Distance;
unsigned int echo_time;
unsigned int average;
unsigned int i;
// ----------------------------------------------------------------------------------------
// ******************************** 3. Subroutines Section ********************************
// ----------------------------------------------------------------------------------------
int main(void){
  UART_Init();    											 // initialize UART for printing
	SysTick_Init();
	PLL_INIT();
	PortB_Init();
	PortF_Init();
	EnableInterrupts();
	while(1){
		LED = 0x08;
		if(SW1 == 0x00){
			Distance = Find_Range(0x80, 0x40);
			printf("\n Distance: %d cm\n",Distance);
		}
	}
}
// ----------------------------------------------------------------------------------------
// *************************** 4. Port Initializations Functions **************************
// ----------------------------------------------------------------------------------------
void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 		0x00000020; // 1) F clock
  delay = SYSCTL_RCGC2_R;           // 	  delay   
  GPIO_PORTF_LOCK_R = 	0x4C4F434B; // 2) unlock PortF PF0(SW2)  
  GPIO_PORTF_CR_R = 		0x1F;       // 	  allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 	0x00;       // 3) disable analog function
  GPIO_PORTF_PCTL_R = 	0x00000000; // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 		0x0E;       // 5) Inputs PF4(SW1),PF0(SW2)
																		//	  Outputs PF3(Green),PF2(White),PF1(Red) LEDs   
  GPIO_PORTF_AFSEL_R = 	0x00;       // 6) no alternate function
  GPIO_PORTF_PUR_R = 		0x11;       // 	  enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 		0x1F;       // 7) enable digital pins PF4-PF0        
}

void PortB_Init(void){
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 		0x00000002; // 1) B clock
  delay = SYSCTL_RCGC2_R;           // 		delay    
  GPIO_PORTB_DIR_R = 			0x7F;       // 5) 0 = output, 1 = input
																			//     0		 1		 1		 1  .  1     1     1     1 
																			//		PB7   PB6   PB5   PB4 . PB3   PB2   PB1   PB0
	GPIO_PORTB_DEN_R = 			0xFF;       // 7) enable digital pins PB7-PB0
// ********************************** a. Unused Registers *********************************
//  GPIO_PORTB_LOCK_R = 	0x4C4F434B; // 2) unlock PortB  
//  GPIO_PORTB_CR_R = 		0xFF;       // 		allow changes to PB7-PB0       
//  GPIO_PORTB_AMSEL_R = 	0x00;       // 3) disable analog function
//  GPIO_PORTB_PCTL_R = 	0x00000000; // 4) GPIO clear bit PCTL 
//  GPIO_PORTB_AFSEL_R |= 0xC0;       // 6) PB6 use alternate function
//  GPIO_PORTB_PUR_R = 		0x00;       // 		disable pullup resistor      
//  GPIO_PORTB_DEN_R = 		0xFF;       // 7) enable digital pins PB7-PB0
}
// ----------------------------------------------------------------------------------------
// ******************************** 5. Systick/PLL Functions ******************************
// ----------------------------------------------------------------------------------------
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
void SysTick_Wait10us(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    SysTick_Wait(750);  // wait 10µs (assumes 50 MHz clock)
  }
}

// Time delay using busy wait.
// This assumes 50 MHz system clock.
void SysTick_Wait1ms(unsigned long delay){
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

int Find_Range(unsigned long Echo_PIN, unsigned long Trigger_PIN) {
	SysTick_Wait1ms(50);
	int Distance = 0;
	// ****************************** a. Toggle Range Finder **********************************
		LED = 0x08;						// GREEN LED FLAG
		average = 0;											// Reset average
		
		for(i=0;i<3;i++){									// Three samples, gets average to have better data.
			LED = 0x00;											// CLEAR LED FLAG
			echo_time = 0;									// Reset echo
			GPIO_PORTB_DATA_R |= Trigger_PIN;		// Set trigger high
			SysTick_Wait10us(1);						// 10 µs delay using systick
			GPIO_PORTB_DATA_R &= ~Trigger_PIN;	// Set trigger low
			
			while((GPIO_PORTB_DATA_R&Echo_PIN)==0);				// Search for high transition
			while((GPIO_PORTB_DATA_R&Echo_PIN)==Echo_PIN){		// Search for low transition
				SysTick_Wait(3);
				echo_time++;														// Count echo_time
			}
			average += echo_time;											// Add the echo_time to the average
		}
		average /= 3;																// After three samples take the average
		LED = 0x02;				// RED LED FLAG			
// ****************************** b. Calculate Range(cm) **********************************
		Distance = average*0.01175;
		return Distance;
}
