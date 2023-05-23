// ****************************** 0. Documentation Section ********************************
// main.c
// Runs on TM4C123
// Lab 7: Traffic Light Controller
// Authors: Andrew D. Bissell
// Date: October 27, 2021

// Off Board hardware
// Using breadboard
// Switch x3, Green LED x3, Red LED x3, Yellow LED x3, Jumper Cables
// Resistor: 10k ohm, 330 ohm
// ****************************** 1. Pre-processor Directives Section *********************
#include "TExInitStop.h"
// #include "tm4c123gh6pm.h"

#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x40005520))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
	
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *)0x40024520))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
	
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))

#define SENSOR 									(*((volatile unsigned long *)0x4002401C))		// PortE for switches all input
#define LIGHT		 								(*((volatile unsigned long *)0x400050FC))		// PortB for LEDs all outputs
#define PED 										(*((volatile unsigned long *)0x40025328))		// PortF for PED combination in/out
	
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
	
// ********************************** a. PhInitStope Lock Loop **********************************
#define SYSCTL_RCC2_R						(*((volatile unsigned long *)0x400FE070))
#define SYSCTL_RCC_R						(*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RIS_R						(*((volatile unsigned long *)0x400FE050))
#define SYSDIV2	4								// N+1 = 400 MHz / Set Frequency

// ********************************** b. SYSTICK Timer ************************************
#define NVIC_ST_CTRL_R					(*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R				(*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R				(*((volatile unsigned long *)0xE000E018))
#define THOUSANDTH_CLK_FREQ	80000

// ********************************** c. STATES *******************************************
#define InitStop  0
#define North     1
#define NorthWait 2
#define AllStop   3
#define East      4
#define EastStop  5
#define Ped       6
#define PedWait   7
#define Flash1    8
#define Flash2    9
#define Flash3    10
#define Flash4    11
#define Flash5    12
#define Flash6    13
// ****************************** 2. Declarations Section *********************************

struct State {
	unsigned long Out; 					// 6-bit pattern to output
	unsigned long OutP;
	unsigned long Time; 				// delay in 10ms units
	unsigned long Next[8];
}; 														// next state for inputs 0,1,2,3

typedef const struct State STyp;
 
void DisableInterrupts(void); 						// Disable interrupts
void EnableInterrupts(void);  						// Enable interrupts
void PORTB_Init(void);        						// Initializes PortB
void PORTE_Init(void);        						// Initializes PortE
void PORTF_Init(void);        						// Initializes PORTF
void PLL_Init(void);          						// Initializes PLL, referenced from internet      
void SYSTICK_Init(void);      						// Initializes SysTick, referenced from the internet 
void SYSTICK_DELAY(unsigned long msec);  	// Delay for SysTick

// ****************************** 3. Subroutines Section **********************************
 STyp FSM[14]={
	// {PortBoutput, PortFoutput, delay, {noCarnoPed,EWcarNoPed, NScarNoPed,NWcarNoPed, noCarYesPed, EWcarYesPed, NScarYesPed, NWcarYesPed} 
	// {X,Y,T,		 {000,				001,				010,				011,				100,				101,				110,				111}},
	{0x24,0x02,300,{North,			East,				North,			North,			Ped,				Ped,				Ped,				Ped}},																				// North 1
	{0x21,0x02,300,{NorthWait,	NorthWait,	North,			NorthWait,	NorthWait,	NorthWait,	NorthWait,	NorthWait}},	// NorthWait 2
	{0x22,0x02,300,{AllStop,		AllStop,		InitStop,		AllStop,		AllStop,		AllStop,		AllStop,		AllStop}},  						// second all stop 3
	{0x24,0x02,300,{East,				East,				North,			East,				Ped,				Ped,				Ped,				Ped}},																					// East 4
	{0x0C,0x02,300,{EastStop,		East,				EastStop,		EastStop,		EastStop,		EastStop,		EastStop,		EastStop}},					// EastStop 5
	{0x14,0x02,300,{InitStop,		InitStop,		InitStop,		InitStop,		InitStop,		InitStop,		InitStop,		InitStop}},			// Ped 
	{0x24,0x08,300,{PedWait,		PedWait,		PedWait,		PedWait,		PedWait,		PedWait,		PedWait,		PedWait}}, 							// PedWait
	{0x24,0x00,300,{Flash1,			Flash1,			Flash1,			Flash1,			Flash1,			Flash1,			Flash1,			Flash1}},											// Flash end -4
	{0x24,0x08,50, {Flash2,			Flash2,			Flash2,			Flash2,			Flash2,			Flash2,			Flash2,			Flash2}},
	{0x24,0x00,50, {Flash3,			Flash3,			Flash3,			Flash3,			Flash3,			Flash3,			Flash3,			Flash3}},
	{0x24,0x08,50, {Flash4,			Flash4,			Flash4,			Flash4,			Flash4,			Flash4,			Flash4,			Flash4}},
	{0x24,0x00,50, {Flash5,			Flash5,			Flash5,			Flash5,			Flash5,			Flash5,			Flash5,			Flash5}},
	{0x24,0x08,50, {Flash6,			Flash6,			Flash6,			Flash6,			Flash6,			Flash6,			Flash6,			Flash6}},
	{0x24,0x00,50, {North,			East,				North,			North,			Ped,				East,				North,			North}},
};

unsigned long S; 							// index to the current state
unsigned long Input;
int main(void){ volatile unsigned long delay;
	PLL_Init(); 								// 80 MHz, Program 10.1
	SYSTICK_Init(); 						// Program 10.2
	SYSCTL_RCGC2_R |= 0x22; 		// 1) B E F
	PORTB_Init();
	PORTE_Init();
	PORTF_Init(); 
	S = North; 										// all stop state
	
 while(1){
	LIGHT = FSM[S].Out; 				// set lights
	PED = FSM[S].OutP;
	SYSTICK_DELAY(FSM[S].Time);
	Input = SENSOR; 						// read sensors
	S = FSM[S].Next[Input]; 
 }
}

void PLL_INIT(void){		
  SYSCTL_RCC2_R |=  0x80000000;   							// 0) Use RCC2, USERCC2
  SYSCTL_RCC2_R |=  0x00000800;    							// 1) bypInitStops PLL while initializing, BYPInitStopS2, PLL bypInitStops
  SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)		// 2) select the crystal value and oscillator source, clear XTAL field, bits 10-6
  + 0x00000540;   															// 		10101, configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~0x00000070;  								// 		configure for main oscillator source
  SYSCTL_RCC2_R &= ~0x00002000;									// 3) activate PLL by clearing PWRDN
  SYSCTL_RCC2_R |= 0x40000000;   								// 4) set the desired system divider, use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)  // 		clear system clock divider
  + (4<<22);      															// 		configure for 80 MHz clock
  while((SYSCTL_RIS_R&0x00000040)==0){};  		  // 5) wait for the PLL to lock by polling PLLLRIS, wait for PLLRIS bit
  SYSCTL_RCC2_R &= ~0x00000800;									// 6) enable use of PLL by clearing BYPInitStopS
}


void SYSTICK_Init(void){
	NVIC_ST_CTRL_R = 0;								// 1) Disable SYSTICK during set up
	NVIC_ST_RELOAD_R = 0x00FFFFFF;		// 2) MAX reload value
	NVIC_ST_CURRENT_R = 0;						// 3) Clear CURRENT by simply writing to it (any write to it clears it)
	NVIC_ST_CTRL_R = 0x00000005;			// 4) Enable SYSTICK timer with core clock
	
}

void SYSTICK_DELAY(unsigned long msec){
	unsigned long i;
	for (i=0; i<msec; i++){
		volatile unsigned long elapsedTime;
		unsigned long startTime = NVIC_ST_CURRENT_R;
		do{
			elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
		}
		while(elapsedTime <= THOUSANDTH_CLK_FREQ);
	}
}

void PORTB_Init(void){
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000002;     // 1) B clock
  delay = SYSCTL_RCGC2_R;           // 		delay   
  GPIO_PORTB_LOCK_R = 0x4C4F434B;   // 2) unlock PortB  
  GPIO_PORTB_CR_R = 0x3F;           // 		allow changes to PB5-PB0       
  GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R = 0x3F;          // 5) PB5-PB0 Output   
  GPIO_PORTB_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTB_PUR_R = 0x00;          // 		disable pullup resistor      
  GPIO_PORTB_DEN_R = 0x3F;          // 7) enable digital pins PB5-PB0
}

void PORTE_Init(void){
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010;     // 1) E clock
  delay = SYSCTL_RCGC2_R;           // 		delay   
  GPIO_PORTE_LOCK_R = 0x4C4F434B;   // 2) unlock PortE  
  GPIO_PORTE_CR_R = 0x07;           // 		allow changes to PE2-PE0       
  GPIO_PORTE_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTE_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R = 0x00;          // 5) Set all to Inputs   
  GPIO_PORTE_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTE_PUR_R = 0x00;          // 		disable pullup resistor      
  GPIO_PORTE_DEN_R = 0x07;          // 7) enable digital pins PF4-PF0  
}

void PORTF_Init(void){ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // 		delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF 
  GPIO_PORTF_CR_R = 0x1F;           // 		allow changes to PF4-PF0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 Input, PF3,PF2,PF1 Output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // 		enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}
