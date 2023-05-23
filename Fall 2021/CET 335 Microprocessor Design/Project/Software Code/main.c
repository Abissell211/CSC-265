// ****************************** 0. Documentation Section ********************************
// main.c
// Runs on TM4C123
// Project: Range Finder
// Authors: Andrew D. Bissell, Charles Krug
// Date: November 11/2021 - 

// Off Board hardware:
// Breadboard, jumper cables, red led, yellow led, green led, white led
// Power Supply Module, 9V 1A Power Supply, HC-SR04 Ultrasonic Ranging Module
// Resistors: 220ohm x4
// ----------------------------------------------------------------------------------------
// ****************************** 1. Pre-processor Directives Section *********************
// ----------------------------------------------------------------------------------------
#include <stdio.h>   						// standard C library 
#include "uart.h"								// Uart for outputing to user
#include "tm4c123gh6pm.h"				// Magical library of amazing #define's

#define Trigger									(*((volatile unsigned long *)0x40005100))
#define Echo										(*((volatile unsigned long *)0x50005200))	
#define LED											(*((volatile unsigned long *)0x40025038))
#define SW1											(*((volatile unsigned long *)0x40025040))
#define SW2											(*((volatile unsigned long *)0x40025004))

// FSM Variables
#define LIGHT		 								(*((volatile unsigned long *)0x4000503C))		// PortB for LEDs all outputs
// ********************************** a. STATES *******************************************
#define RLED  0
#define YLED  1
#define GLED  2
#define WLED  3
// ----------------------------------------------------------------------------------------
// ****************************** 2. Declarations Section *********************************
// ----------------------------------------------------------------------------------------
// ******************************** a. FSM Declarations ***********************************
typedef struct StateStructure {
	unsigned long Out; 					// 4-bit pattern to output
	unsigned long Time; 				// delay in 1ms units
	unsigned long Next[4];
}State; 					

typedef const struct State STyp;

State FSM[4] =
{//Outp,D, { 000,  001,  010,  011,}},	  
	{0x08,5, {RLED, YLED, GLED, WLED,}}, // RLED 0
	{0x04,5, {RLED, YLED, GLED, WLED,}}, // YLED 1
	{0x02,5, {RLED, YLED, GLED, WLED,}}, // GLED 2
	{0x01,5, {RLED, YLED, GLED, WLED,}}, // WLED 3
//					 ERR,	 >1m, 1to3m, <3m,}},
};
// ****************************** b. Function Prototypes **********************************
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
unsigned int Distance_Input(unsigned int);
// ******************************** c. Global Variables ***********************************
unsigned long S;
unsigned long Input;
unsigned int Difference;
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
		LIGHT = FSM[S].Out; 								// Set output for FSM before new cycle
// ****************************** a. Toggle Range Finder **********************************
		LED = 0x08;						// GREEN LED FLAG
    if(SW1 == 0x00){
			average = 0;											// Reset average
			
			for(i=0;i<3;i++){									// Three samples, gets average to have better data.
				LED = 0x00;				// CLEAR LED FLAG
				echo_time = 0;									// Reset echo
				Trigger |= 0x40;								// Set trigger high
				SysTick_Wait10us(1);						// 10 µs delay using systick
				Trigger &= ~0x40;								// Set trigger low
				
				while((GPIO_PORTB_DATA_R&0x80)==0);				// Search for high transition
				while((GPIO_PORTB_DATA_R&0x80)==0x80){		// Search for low transition
					SysTick_Wait(3);
					echo_time++;														// Count echo_time
				}
				average += echo_time;											// Add the echo_time to the average
			}
			average /= 3;																// After three samples take the average
			LED = 0x02;				// RED LED FLAG			
// ****************************** b. Calculate Range(cm) **********************************
			Distance = average*0.01175;				
// ************************************* c. FSM *******************************************
			printf("\n Distance: %d cm\n",Distance);
			
			Input = Distance_Input(Distance);
			SysTick_Wait1ms(500);
			SysTick_Wait1ms(FSM[S].Time);
			S = FSM[S].Next[Input];
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
// ----------------------------------------------------------------------------------------
// ********************************** 6. PWM Initialization *******************************
// ----------------------------------------------------------------------------------------
void PWM0A_Init(unsigned int period, unsigned int duty){	// Output on PB7/M0PWM1
	volatile unsigned long delay;
	SYSCTL_RCGC0_R |= 			0x00100000;							// 1) Activate PWM0
	SYSCTL_RCGCGPIO_R |= 		0x01;										// 2) Activate port A
	delay = SYSCTL_RCGCGPIO_R;											// Allow time to finish activating
	GPIO_PORTA_AFSEL_R |= 	0x80;										// 3) Enable alt funtion on PB7
	GPIO_PORTA_PCTL_R &= 	 ~0xF0000000;							// 4) Configure PB7 as M0PWM1
	GPIO_PORTA_PCTL_R |= 		0x40000000;
	GPIO_PORTA_AMSEL_R &=  ~0x80;										// Disable analog funtionality on PB7
	GPIO_PORTA_DEN_R |= 		0x80;										// Enable digital I/O on PB7
	SYSCTL_RCC_R &= 			~(0x000E0000);						// 5) Clearing first
	SYSCTL_RCC_R |= 			 (0x00080000);						// The writing in the 19:17 with PWMDIV 0x3 configure for /32 divider
	SYSCTL_RCC_R |= 				0x00100000;							// Use PWM divider
	PWM0_0_CTL_R = 					0x00;										// 6) Re-loading down-counting mode
	PWM0_0_GENA_R = 			 (0x00000C00|0x00000008);	// 0xC8 in lesson		// PB7 goes low on LOAD, PB7 goes high on CMPB down
	PWM0_0_LOAD_R = 				period - 1;							// 7) Cycles needed to count down to 0
	PWM0_0_CMPB_R = 				duty - 1;								// 9) Count value when output rises
	PWM0_0_CTL_R |= 				0x00000001;							// 10) Start PWM0
	PWM0_ENABLE_R |= 				0x00000002;							// 11) Enable PB7/M0PWM1
}
// ----------------------------------------------------------------------------------------
// ******************************** 7. Main Program Functions *****************************
// ----------------------------------------------------------------------------------------
// Sets the right output for the FSM using the distance from the sensor.
// Takes in the Distance and returns the state the FSM needs to be.
unsigned int Distance_Input(unsigned int Distance){
	if((Distance > 400) || (Distance < 1)){  // Red LED
		return 0;
	}
	else if(Distance <= 100){								 // Yellow LED
		return 1;
	}
	else if(Distance <= 200){								 // Green LED
		return 2;
	}
	else if(Distance > 200){								 // White LED
		return 3;
	}
		return 0;
}
