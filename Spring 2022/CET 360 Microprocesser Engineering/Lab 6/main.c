// Author: Andrew Bissell, Noah Proctor
// Summary:	Busy Wait/PortB Interrupt with IR proximity sensor
// Inputs: IR proximity sensor
// Outputs: none
// DATE 03/03/2022
//=====================================================================================//

/*==============|           0. Description                              |==============//
/- - - - - - - - - - - - -  0A.ISSUES:   - - - - - - - - - - - - - - - - - - - - - - - //
			
/- - - - - - - - - - - - -  0A.SUGGESTIONS:  - - - - - - - - - - - - - - - - - - - - - //

/- - - - - - - - - - - - -  0A.TODO:   - - - - - - - - - - - - - - - - - - - - - - - - //
				
/- - - - - - - - - - - - -  0A.DONE:   - - - - - - - - - - - - - - - - - - - - - - - - //
			
 - - - - - - - - - - - - - 0E.PROBLEMS SOLVED: - - - - - - - - - - - - - - - - - - - - //		

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*=====================================================================================*/
/*==============|           1. Pre-processor Directive Section          |==============*/
//---------------------------------------------------------SysTick-------------------------------------------------------------//
#define SysTick_Base					0xE000E000
#define CTRL									0x010
#define RELOAD								0x014
#define CURRENT								0x018

#define NVIC_ST_CTRL_R				(*((volatile unsigned long *)(SysTick_Base | CTRL)))
#define NVIC_ST_RELOAD_R			(*((volatile unsigned long *)(SysTick_Base | RELOAD)))
#define NVIC_ST_CURRENT_R			(*((volatile unsigned long *)(SysTick_Base | CURRENT)))
#define THOUSANDTH_CLK_FREQ		80000
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
//-----------------------------------------------------GPIO Constants----------------------------------------------------------//
#define PORTB_BASE						0x40005000
#define PORTB_Output					(*((volatile unsigned long *)(PORTB_BASE | 0x200)))
#define PIN_B0								0x01;

#define PORTF_BASE						0x40025000
#define PORTF									0x20
#define RED										0x02
#define GREEN									0x08

#define DATA									0x3FC
#define DIR										0x400
#define AFSEL									0x420
#define PUR										0x510
#define DEN										0x51C
#define CR										0x524
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
#define GPIO_PORTF_CR_R				(*((volatile unsigned long *)(PORTF_BASE | CR)))
#define GPIO_PORTF_PUR_R			(*((volatile unsigned long *)(PORTF_BASE | PUR)))
#define GPIO_PORTF_PCTL_R			(*((volatile unsigned long *)(PORTF_BASE | PCTL)))
#define GPIO_PORTF_AFSEL_R		(*((volatile unsigned long *)(PORTF_BASE | AFSEL)))
#define GPIO_PORTF_AMSEL_R		(*((volatile unsigned long *)(PORTF_BASE | AMSEL)))
//-----------------------------------------------------PORTF Interrupt---------------------------------------------------------//
#define IS										0x404
#define IBE										0x408
#define IEV										0x40C
#define IM										0x410
#define ICR										0x41C

#define GPIO_PORTB_IS_R				(*((volatile unsigned long *)(PORTB_BASE | IS)))
#define GPIO_PORTB_IBE_R			(*((volatile unsigned long *)(PORTB_BASE | IBE)))
#define GPIO_PORTB_IEV_R			(*((volatile unsigned long *)(PORTB_BASE | IEV)))
#define GPIO_PORTB_IM_R				(*((volatile unsigned long *)(PORTB_BASE | IM)))
#define GPIO_PORTB_ICR_R			(*((volatile unsigned long *)(PORTB_BASE | ICR)))
//--------------------------------------------Nested Vectored Interrupt Controller---------------------------------------------//
#define PRI0									0x400
#define EN0										0x100

#define NVIC_PRI0_R						(*((volatile unsigned long *)(SysTick_Base | PRI0)))
#define NVIC_EN0_R						(*((volatile unsigned long *)(SysTick_Base | EN0)))	
//----------------------------------------------------------PLL----------------------------------------------------------------//
#define SYSCTL_RCC2_R					(*((volatile unsigned long *)(SYSCTL | RCC2)))
#define SYSCTL_RIS_R					(*((volatile unsigned long *)(SYSCTL | RIS)))
#define SYSDIV2							4						// N+1 = 400 MHz / Desired_Frequency, where Desired_Frequency = 80MHz
/*--------------            1__SUBSECTION                               ---------------*/
/*- - - - - - - - - - - - - SUB-SUBSECTION- - - - - - - - - - - - - - - - - - - - - - -*/
//		.STARTCODE
													//.STARTCOMMENT
/*=====================================================================================*/
/*==============|           2. Declaration Section                      |==============*/
/*--------------            2__GLOBAL FUNCT PROTOTYPE                   ---------------*/
void PORTF_Init(void);
void PORTB_Init(void);
void GPIOPortB_Handler(void);
void SYSTICK_INIT(void);
void SYSTICK_DELAY(unsigned long msec);
void PLL_INIT(void);
/*--------------            2__GLOBAL VARIABLE PROTOTYPE                ---------------*/

/*=====================================================================================*/
/*==============|           3. Main Program Section                     |==============*/
int main(void){
/*--------------            3__VARIABLES INIT                           ---------------*/

/*--------------            3__FUNCTION INIT                            ---------------*/
PORTF_Init();
PORTB_Init();
/*--------------            3__STATUS INIT                              ---------------*/

/*--------------            3__RUNNING WHILE LOOP                       ---------------*/
	while(1){
		// Busy Wait
/*		while((GPIO_PORTB_DATA_R&0x01) == 0x00)
			GPIO_PORTF_DATA_R = RED;
		GPIO_PORTF_DATA_R = GREEN;
*/
	}
}

/*=====================================================================================*/
/*==============|           4. Subroutines and Functions                |==============*/
/*--------------            4__SUBSECTION/FUNCT NAME                    ---------------*/

//-----------------------------------INTERRUPT SERVICE ROUTINE------------------------------------//
// The ISR must have the correct name that startup.s used for the interrupt vector.
// For PORTF the name is GPIOPortF_Handler.
// Remember ISR's do not receive any parameters nor do they return any parameters
void GPIOPortB_Handler(void){
	GPIO_PORTB_ICR_R = PIN_B0;    					// acknowledge flag
	
	if((GPIO_PORTB_DATA_R&0x01) == 0x00)
		GPIO_PORTF_DATA_R = GREEN;
	else if ((GPIO_PORTB_DATA_R&0x01) == 0x01)
		GPIO_PORTF_DATA_R = RED;
}

void PORTB_Init(void){				// For PB0-3
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000002;   				// 1) activate clock for Port A
	GPIO_PORTB_LOCK_R = 0x4C4F434B;   			//  unlock 
	delay = SYSCTL_RCGC2_R;           			// delay   
	GPIO_PORTB_DIR_R &= ~PIN_B0;          	//  PA2 as input
	GPIO_PORTB_AFSEL_R &= ~PIN_B0;        	//  no alternate function
	GPIO_PORTB_DEN_R |= PIN_B0;          		//  enable digital pins PE5
	GPIO_PORTB_PCTL_R &= ~0x0000000F;   		//  GPIO clear bit PCTL  
	GPIO_PORTB_AMSEL_R &= ~PIN_B0;        	//  disable analog function
	GPIO_PORTB_PUR_R &= ~PIN_B0;          	// no pullup  
	
	

	
	// PIN SPECIFIC: FOLLOWING FOR PA2 WHICH IS 0x04
	GPIO_PORTB_IS_R  	&= ~PIN_B0;        		// GPIOIS-Interrupt Sense [664]: Edge Sensitive {clear as 0}
	GPIO_PORTB_IBE_R 	&= ~PIN_B0;       		// GPIOIBE-Interrupt Both Edges [665]: Not both edges {clear as 0}
	GPIO_PORTB_IEV_R 	|= PIN_B0;       			// GPIOIVE-Interrupt Event [666]: Rising Edge {set as 1}
	GPIO_PORTB_ICR_R 	|= PIN_B0;          	// GPIOICR-Interrupt Clear [670]: Clear flag {1 = clear}
	GPIO_PORTB_IM_R  	|= PIN_B0;       			// GPIOIM-Interrupt Mask [667]: Arm the interrupt by allowing pin to send
	//	interrupt {set as 1}

	// NVIC_PRI0_R deals with priority interrupt for GPIO Port A through D
	// Want to clear the specific range and then reassign it
	//[Book 357]
	NVIC_PRI0_R	= (NVIC_PRI0_R&0xFFFFFF0F)| (1<<13); // bits 7-5 as target, Priority 4, Shift priority value into the 
	//location (5 here)
	NVIC_EN0_R 	|= 0x00000002;							// Port A is bit 0 [Page 104] for NVIC Enable, EN0 is bit 
																					//  numbers 0-31 [140]
}

void PORTF_Init(void){ volatile unsigned long delay;
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
