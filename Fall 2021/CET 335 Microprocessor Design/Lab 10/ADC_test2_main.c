// ****************************** 0. Documentation Section ********************************
// main.c
// Runs on TM4C123
// Lab 10: ADC on LaunchPad
// Authors: Andrew D. Bissell, Charles Krug
// Date: November 11, 2021

// Off Board hardware:
// Jumper Cables
// 10k Ohm potentiometer
// ****************************** 1. Pre-processor Directives Section *********************
#include "tm4c123gh6pm.h"
#include "ADCSWTrigger.h"
#include "PLL.h"

// DEFINE
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// bit specefic addressing
// swtiches 1 and 2 on PF4 and PF0 respectively
#define Switch_1         				(*((volatile unsigned long *)0x40025040))
#define Switch_2         				(*((volatile unsigned long *)0x40025004))	

// LEDs RED, BLUE and GREEN on PF1, PF2 and PF3 respectively
#define RED_LED         				(*((volatile unsigned long *)0x40025008))
#define BLUE_LED         				(*((volatile unsigned long *)0x40025010))
#define GREEN_LED         			(*((volatile unsigned long *)0x40025020))
	

// ****************************** 2. Declarations Section *********************************
//GLOBAL VARIABLES
unsigned long SW1,SW2;  // input from PF4,PF0
unsigned long In; 
unsigned long Out;      // outputs to PF3,PF2,PF1 (multicolor LED)
unsigned long Led;      // outputs to PF3,PF2,PF1 (multicolor LED)

volatile unsigned long ADCvalue;
volatile float result;

void PortF_Init(void); 
void ADC0_InitSWTriggerSeq3_Ch1(void);
unsigned long ADC0_InSeq3(void);

// ****************************** 3. Subroutines Section **********************************
int main(void)
{
	PLL_Init();   
  ADC0_InitSWTriggerSeq3_Ch1();         // ADC initialization PE2/AIN1
	PortF_Init();  												// PortF initialization	
	while(1){ 
    ADCvalue = ADC0_InSeq3();
		if(4095 - ADCvalue < 1737)
			GPIO_PORTF_DATA_R = 0x02;
		if(4095 - ADCvalue > 1737 && ADCvalue < 3102)
			GPIO_PORTF_DATA_R = 0x04;
		if(4095 - ADCvalue > 3102)
			GPIO_PORTF_DATA_R = 0x08;
	}
}


void PortF_Init(void)
{
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0

}
