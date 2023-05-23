// Author: 
// Summary:
// Inputs: 
// Outputs: 
// DATE
//=====================================================================================//

/*==============|           0. Description                              |==============//
/- - - - - - - - - - - - -  0A.ISSUES:   - - - - - - - - - - - - - - - - - - - - - - - //
			
/- - - - - - - - - - - - -  0A.SUGGESTIONS:  - - - - - - - - - - - - - - - - - - - - - //

/- - - - - - - - - - - - -  0A.TODO:   - - - - - - - - - - - - - - - - - - - - - - - - //

	*Requirements of Part A:
	For left motor:
		Motor starts in stall position
		Pressing SW1 once causes motor to rotate CW
		Pressing SW1 again causes motor to rotate CW faster
		If at full speed, Pressing SW1 again results in motor being brought to stall
		
		Pressing SW2 once causes motor to rotate in CCW direction
		Pressing SW2 again causes motor to rotate in CCW direction faster
		If at full speed, Pressing SW2 again results in motro being brought to stall
	*Requirements of Part B:
		Repeat Part A for right motor.
	*Completed file should control left and right motor
		

			> L298N (Motor Driver)
				> IN1,IN2 - Control direction of Motor A [Output:PB0 as IN1, PB1 as IN2]
					> IN1 = 1, IN2 = 0 -> Forward movement
					  IN1 = 0, IN2 = 1 -> Backward Movement
					  IN1 = IN2 -> Motor OFF
				> ENA - Controls speed of Motor A (Pulse Width)[Output: Pulse Width on PB6]
				
				> IN3,IN4 - Control direction of Motor B [Output:PB2 as IN3, PB3 as IN4]
					> IN3 = 1, IN4 = 0 -> Forward movement
					  IN3 = 0, IN4 = 1 -> Backward Movement
					  IN3 = IN4 -> Motor OFF
				> ENB - Controls speed of Motor B (Pulse Width)[Output: Pulse Width on PB7]
			
			> TM4C123GH6PM (Board)
				> SW1, SW2 - Control direction and speed of motor [Input: PF0, PF4]
				  SW1 as PF4,
				  SW2 as PF0	
				 > Global variable to track Switch press
				 > Interrupt Driven
				
			> 9V 25GA-370 (Motor)
				> S1, S2 (1st and 2nd Hall Sensor information

					
			>74HC04 (NOT Gate)
				
/- - - - - - - - - - - - -  0A.DONE:   - - - - - - - - - - - - - - - - - - - - - - - - //
			
 - - - - - - - - - - - - - 0E.PROBLEMS SOLVED: - - - - - - - - - - - - - - - - - - - - //		

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*=====================================================================================*/
/*==============|           1. Pre-processor Directive Section          |==============*/
//---------------------------------------------------------SysTick-------------------------------------------------------------//
#define SysTick_Base					0xE000E000
#define STCTRL								0x010
#define STRELOAD							0x014
#define STCURRENT							0x018

#define NVIC_ST_CTRL_R				(*((volatile unsigned long *)(SysTick_Base | STCTRL)))
#define NVIC_ST_RELOAD_R			(*((volatile unsigned long *)(SysTick_Base | STRELOAD)))
#define NVIC_ST_CURRENT_R			(*((volatile unsigned long *)(SysTick_Base | STCURRENT)))
#define NVIC_ST_CTRL_COUNT		0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC  0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN    0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE   0x00000001  // Counter mode
#define NVIC_ST_RELOAD_M      0x00FFFFFF  // Counter load value
#define THOUSANDTH_CLK_FREQ		80000
//-------------------------------------------------Pulse Width Modulation------------------------------------------------------//
#define PWM_BASE							0x40028000
#define PWM0CTL								0x040
#define PWM0GENB							0x064
#define PWM0LOAD							0x050
#define PWM0CMPB							0x05C
#define PWM0ENABLE						0x008

#define PWM0GENA							0x060
#define PWM0CMPA							0x058

#define PWM0_0_CTL_R					(*((volatile unsigned long *)(PWM_BASE | PWM0CTL)))		// PWMn_n_CTL,  n=(0 = 0x040, 1 = 0x080, 2 = 0x0C0, 3 = 0x100)
#define PWM0_0_GENB_R					(*((volatile unsigned long *)(PWM_BASE | PWM0GENB)))	// PWMn_n_GENB, n=(0 = 0x064, 1 = 0x0A4, 2 = 0x0E4, 3 = 0x124)
#define PWM0_0_LOAD_R					(*((volatile unsigned long *)(PWM_BASE | PWM0LOAD)))	// PWMn_n_LOAD, n=(0 = 0x050, 1 = 0x090, 2 = 0x0D0, 3 = 0x110)
#define PWM0_0_CMPB_R					(*((volatile unsigned long *)(PWM_BASE | PWM0CMPB)))	// PWMn_n_CMPB, n=(0 = 0x05C, 1 = 0x09C, 2 = 0x0DC, 3 = 0x11C)
#define PWM0_ENABLE_R					(*((volatile unsigned long *)(PWM_BASE | PWM0ENABLE)))
	
#define PWM0_0_GENA_R					(*((volatile unsigned long *)(PWM_BASE | PWM0GENA)))
#define PWM0_0_CMPA_R					(*((volatile unsigned long *)(PWM_BASE | PWM0CMPA)))
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
	
#define PORTF_BASE						0x40025000
#define SW1										(*((volatile unsigned long *)(PORTF_BASE | 0x040)))
#define SW2										(*((volatile unsigned long *)(PORTF_BASE | 0x004)))
#define LED										(*((volatile unsigned long *)(PORTF_BASE | 0x038)))

#define DATA									0x3FC
#define DIR										0x400
#define AFSEL									0x420
#define PUR										0x510
#define DEN										0x51C
#define LOCK									0x520
#define CR										0x524
#define AMSEL									0x528
#define PCTL									0x52C

#define GPIO_PORTB_DATA_R			(*((volatile unsigned long *)(PORTB_BASE | DATA)))
#define GPIO_PORTB_DIR_R			(*((volatile unsigned long *)(PORTB_BASE | DIR)))
#define GPIO_PORTB_AFSEL_R		(*((volatile unsigned long *)(PORTB_BASE | AFSEL)))
#define GPIO_PORTB_PUR_R			(*((volatile unsigned long *)(PORTB_BASE | PUR)))
#define GPIO_PORTB_DEN_R			(*((volatile unsigned long *)(PORTB_BASE | DEN)))
#define GPIO_PORTB_LOCK_R			(*((volatile unsigned long *)(PORTB_BASE | LOCK)))
#define GPIO_PORTB_CR_R				(*((volatile unsigned long *)(PORTB_BASE | CR)))
#define GPIO_PORTB_AMSEL_R		(*((volatile unsigned long *)(PORTB_BASE | AMSEL)))
#define GPIO_PORTB_PCTL_R			(*((volatile unsigned long *)(PORTB_BASE | PCTL)))
	
#define GPIO_PORTF_DATA_R			(*((volatile unsigned long *)(PORTF_BASE | DATA)))
#define GPIO_PORTF_DIR_R			(*((volatile unsigned long *)(PORTF_BASE | DIR)))
#define GPIO_PORTF_AFSEL_R		(*((volatile unsigned long *)(PORTF_BASE | AFSEL)))
#define GPIO_PORTF_PUR_R			(*((volatile unsigned long *)(PORTF_BASE | PUR)))
#define GPIO_PORTF_DEN_R			(*((volatile unsigned long *)(PORTF_BASE | DEN)))
#define GPIO_PORTF_LOCK_R			(*((volatile unsigned long *)(PORTF_BASE | LOCK)))
#define GPIO_PORTF_CR_R				(*((volatile unsigned long *)(PORTF_BASE | CR)))
#define GPIO_PORTF_AMSEL_R		(*((volatile unsigned long *)(PORTF_BASE | AMSEL)))
#define GPIO_PORTF_PCTL_R			(*((volatile unsigned long *)(PORTF_BASE | PCTL)))
//-----------------------------------------------------PORTF Interrupt---------------------------------------------------------//
#define PORTFIS								0x404
#define PORTFIBE							0x408
#define PORTFIEV							0x40C
#define PORTFIM								0x410
#define PORTFMIS							0x418
#define PORTFICR							0x41C

#define GPIO_PORTF_IS_R				(*((volatile unsigned long *)(PORTF_BASE | PORTFIS)))
#define GPIO_PORTF_IBE_R			(*((volatile unsigned long *)(PORTF_BASE | PORTFIBE)))
#define GPIO_PORTF_IEV_R			(*((volatile unsigned long *)(PORTF_BASE | PORTFIEV)))
#define GPIO_PORTF_IM_R				(*((volatile unsigned long *)(PORTF_BASE | PORTFIM)))
#define GPIO_PORTF_MIS_R			(*((volatile unsigned long *)(PORTF_BASE | PORTFMIS)))
#define GPIO_PORTF_ICR_R			(*((volatile unsigned long *)(PORTF_BASE | PORTFICR)))
//--------------------------------------------Nested Vectored Interrupt Controller---------------------------------------------//
#define PRI30									0x478
#define EN0										0x100

#define NVIC_PRI30_R					(*((volatile unsigned long *)(SysTick_Base | PRI30)))
#define NVIC_EN0_R						(*((volatile unsigned long *)(SysTick_Base | EN0)))	
//----------------------------------------------------------PLL----------------------------------------------------------------//
#define SYSCTL_RCC2_R					(*((volatile unsigned long *)(SYSCTL | RCC2)))
#define SYSCTL_RIS_R					(*((volatile unsigned long *)(SYSCTL | RIS)))
#define SYSDIV2								4
/*--------------            1__SUBSECTION                               ---------------*/
/*- - - - - - - - - - - - - SUB-SUBSECTION- - - - - - - - - - - - - - - - - - - - - - -*/
//		.STARTCODE
													//.STARTCOMMENT
/*=====================================================================================*/
/*==============|           2. Declaration Section                      |==============*/
/*--------------            2__GLOBAL FUNCT PROTOTYPE                   ---------------*/
void PWM0B_Init(unsigned int period, unsigned int duty);
void PWM0A_Init(unsigned short period, unsigned short duty);
void PORTF_Init(void);
void PORTB_Init(void);
void PLL_INIT(void);
void SYSTICK_INIT(void);
void SYSTICK_DELAY(unsigned long msec);

/*--------------            2__GLOBAL VARIABLE PROTOTYPE                ---------------*/

unsigned long tracking_variable[5] = {45000, 25000, 0, 25000, 45000};
unsigned long tracking_index = 2;

unsigned long direction = 0x0;

unsigned long SW1_Press = 0;
unsigned long SW2_Press = 0;

/*=====================================================================================*/
/*==============|           3. Main Program Section                     |==============*/
int main(void){
/*--------------            3__VARIABLES INIT                           ---------------*/

/*--------------            3__FUNCTION INIT                            ---------------*/
SYSTICK_INIT();
PORTF_Init();
PORTB_Init();
PLL_INIT();
PWM0B_Init(50000, 3150);			// PB7
//PWM0A_Init(50000, 0);			// PB6
/*--------------            3__STATUS INIT                              ---------------*/

/*--------------            3__RUNNING WHILE LOOP                       ---------------*/
	while(1){
		
		
		if (SW1_Press != 0){					// If the switch1 press happened
			SW1_Press = 0;								// Mark flag as done
			direction = 0x1;
			if (tracking_index == 4){		// If motor is at max speed (CW)
				tracking_index = 2;					// Set speed to stall (2)
				}
			else{												// Otherwise
				tracking_index++;						// Increase CW speed
			}
		}
		else if(SW2_Press != 0){			// If the switch2 press happened
			SW2_Press = 0;								// Mark flag as done
			direction = 0x0;
			if (tracking_index == 0){		// If motor is at max speed (CCW)
				tracking_index = 2;					// Set speed to stall(2)
				}			
			else{												// Otherwise
				tracking_index--;						// Increase CCW speed
			}
		}
		
		GPIO_PORTB_DATA_R |= direction;						// PB0, IN1
		GPIO_PORTB_DATA_R &= direction;						// PB0, IN1
				
		GPIO_PORTB_DATA_R |= ((~direction)<<1);			//PB1, IN2
		GPIO_PORTB_DATA_R &= ((~direction)<<1);			//PB1, IN2		
		
		PWM0_0_CMPB_R = tracking_variable[tracking_index] - 1;		
		/*
	> L298N (Motor Driver)
		> IN1,IN2 - Control direction of Motor A [Output:PB0 as IN1, PB1 as IN2]
			> IN1 = 1, IN2 = 0 -> Forward movement
			  IN1 = 0, IN2 = 1 -> Backward Movement
			  IN1 = IN2 -> Motor OFF
		> ENA - Controls speed of Motor A (Pulse Width)[Output: Pulse Width on PB6]
		
		> IN3,IN4 - Control direction of Motor B [Output:PB2 as IN3, PB3 as IN4]
			> IN3 = 1, IN4 = 0 -> Forward movement
			  IN3 = 0, IN4 = 1 -> Backward Movement
			  IN3 = IN4 -> Motor OFF
		> ENB - Controls speed of Motor B (Pulse Width)[Output: Pulse Width on PB7]
	
	> TM4C123GH6PM (Board)
		> SW1, SW2 - Control direction and speed of motor [Input: PF0, PF4]
		  SW1 as PF4,
		  SW2 as PF0	
		 > Global variable to track Switch press
		 > Interrupt Driven
		
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
void GPIOPortF_Handler(void){
	if(GPIO_PORTF_MIS_R & 0x10){		// check if interrupt was caused by PF4(SW1)
		GPIO_PORTF_DATA_R &= ~0x0A;		// turn off red and green LEDs
		GPIO_PORTF_DATA_R |= (1<<3);	// turn on Green LED
		SW1_Press = 1;
		GPIO_PORTF_ICR_R = 0x10;			// clear the interrupt flag
	}
	else{
		if(GPIO_PORTF_MIS_R & 0x01){		// check if interrupt was caused by PF0(SW2)
			GPIO_PORTF_DATA_R &= ~0x0A;		// turn off red and green LEDs
			GPIO_PORTF_DATA_R |= (1<<1);	// turn on Red LED
			SW2_Press = 1;
			GPIO_PORTF_ICR_R |= 0x01;			// clear the interrupt flag
		}
	}
}



void PORTB_Init(void){				// For PB0-3
	volatile unsigned long delay;
	SYSCTL_RCGCGPIO_R  |= 0x00000002;     // 1) B clock
	delay = SYSCTL_RCGC2_R;           // delay   
	GPIO_PORTB_CR_R |= 0x0F;          // allow changes to PB3-0       
	GPIO_PORTB_AMSEL_R &= ~0x0F;      // 3) disable analog function
	GPIO_PORTB_PCTL_R &= ~0x0000FFFF; // 4) GPIO clear bit PCTL  
	GPIO_PORTB_DIR_R |= 0x0F;         // 5) PB3-0 out   
	GPIO_PORTB_AFSEL_R &= ~0x0F;      // 6) no alternate function
	GPIO_PORTB_PUR_R &= ~0x0F;        // No internal resistor      
	GPIO_PORTB_DEN_R |= 0x0F;         // 7) enable digital pins PB5-0
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

void PWM0A_Init(unsigned short period, unsigned short duty){	//Output on PB6 / M0PWM0 [Page 1233] where period = 20 ms in clock cycles using PWM clock divider, and duty = period*dutycycle
volatile unsigned long delay;
	
// Step 1: Enable PWM clock [Page 455]

	SYSCTL_RCGC0_R |= 0x00100000;
	
// Step 2: Enable clock to appropriate GPIO module (Port B)
	SYSCTL_RCGCGPIO_R |= 0x02;		// clock for port B
	delay = SYSCTL_RCGCGPIO_R;		// delay for set up
	
// Step 3: In GPIO module, enable appropriate pins for their alternate function using GPIO_AFSEL register
	GPIO_PORTB_AFSEL_R |= 0x40; // Activates alt funct PB6
	
// Step 4: Configure the PWMn fields in GPIOPCTL register to assign the PWM signals to the appropriate pins
	GPIO_PORTB_PCTL_R &= ~0x0F000000;	// config PB6 as M0PWM0, first clear
	GPIO_PORTB_PCTL_R |= 0x04000000;	// sets PB6 as M0PWM0
	GPIO_PORTB_AMSEL_R &= ~0x40;			// Disable analong on PB6
	GPIO_PORTB_DEN_R |= 0x40;			// enable digital I/O on PB6
	
// Step 5: Configure the Run-Mode Clock configuration (RCC) register in the System Control module to use the PWM divide (USEPWMDIV) and set the dividier (PWMDIV) to divide by the approrpaite value from the table.
	SYSCTL_RCC_R |= (0x00100000);		// use PWM divider
	SYSCTL_RCC_R &= ~(0x000E0000);		// clear first the division section
	SYSCTL_RCC_R |= (0x00080000);		// PMDIV 0x3 [Page 222] configure for /32 divider

// Step 6: Disable PWM generator by writing 0x00000000 to PWMnCTL register
	PWM0_0_CTL_R = 0x00;			// Reload down-count mode

// Step 7: Configure PWM generator (PWMnGENA) to Do Nothing / Invert / Drive Low / Drive High, based on the load and zero output pulses from the counter
	PWM0_0_GENA_R = 0xC8;			// PB6 goes low on LOAD, PB6 high on CMPB down

// Step 8: Use the formula to set the timer LOAD (in PWMnLOAD) value to the required period. PWM f = System Clock / PWMDIV; Period = LOAD value = PWM f / Required f
// For instance, if sysclock is 16MHz and PWMDIV is 0, which is /2, results in PWM f of 8MHz. If desiring a f of 20kHz, LOAD value will be 8 Mhz / 20 kHz = 400
// Value for compare register depends on how the generator was set up to operate: Do nothing, invert, drive low, or drive high
// Drive high and 25% duty cycle wanted for count down mode, the COmpare would be loaded with value = (100% - desired duty cycle) * PWMnLOAD = 75% * 400 = 300
	PWM0_0_LOAD_R = period - 1;		// cycles needed to count down to 0
	PWM0_0_CMPA_R = duty - 1;		// count value when output rises

// Step 9: Enable PWM generator by writing 1 to appropriate bit in the PWMnCTL register
	PWM0_0_CTL_R |= 0x00000001;		// start PWM0

// Step 10: Enable PWM output by enabling the appropriate pins in the PWMENABLE register
	PWM0_ENABLE_R |= 0x00000001;	// Enable PB6 / M0PWM0
}

void PORTF_Init(void){ 
//--------------------------------------UNLOCK PORTF BIT 0----------------------------------------//
	SYSCTL_RCGCGPIO_R |= (1<<5);		// Set bit5 of RCGCGPIO to enable PORTF clock page 340
// PORTF bit 0 has special function, need to unlock to modify
	GPIO_PORTF_LOCK_R = 0x4C4F434B;	// unlock commit register page 684
	GPIO_PORTF_CR_R = 0x01;					// make PORTF bit 0 configurable page 685
	GPIO_PORTF_LOCK_R = 0;					// lock commit register page 684
//---------------------------------------CONFIGURE PORTF------------------------------------------//
// Initialize PF3 and PF1 as a digital output, PF0 and PF4 as digital input pins
	GPIO_PORTF_DIR_R &= ~(1<<4)|~(1<<0);	// Set PF4 and PF0 as a digital input pins Page 663
	GPIO_PORTF_DIR_R |= (1<<3)|(1<<1);		// Set PF3 as digital output for green LED Page 664
																				//  and PF1 as digital output for red LED
	GPIO_PORTF_DEN_R |= (1<<4)|(1<<3)|(1<<1)|(1<<0);	// make bits 4,3,1 and 0 digital pins page 684
	GPIO_PORTF_PUR_R |= (1<<4)|(1<<0);		// enable pull up for bits 4 & 0 page 677
//--------------------------------CONFIGURE PORTF FOR INTERRUPTS----------------------------------//
// configure PORTF bits 4 and 0 for falling edge trigger interrupt
	GPIO_PORTF_IM_R |= (1<<4)|(1<<0);			// unmask interrupt page 667
	GPIO_PORTF_IS_R &= ~(1<<4)|~(1<<0);		// make bit 4 and 0 edge sensitive page 664
	GPIO_PORTF_IEV_R &= ~(1<<4)|~(1<<0);	// falling edge trigger page 666
	GPIO_PORTF_IBE_R &= ~(1<<4)|~(1<<0);	// turn off both edges page 665
	GPIO_PORTF_ICR_R |= (1<<4)|(1<<0);		// clear any prior interrupt page 670
//---------------------------------------ENABLE INTERRUPT-----------------------------------------//
// enable interrupt in NVIC and set priority to 3
	NVIC_PRI30_R = 3<<5;		// set interrupt priority to 3 page 154
	NVIC_EN0_R |= (1<<30);	// enable IRQ30 page 142     
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

void SYSTICK_INIT(void){
// 1 Disable SYSTICK during set up
NVIC_ST_CTRL_R = 0;
// 2 MAX reload value
NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;
// 3 Clear CURRENT by simply writing to it (any write to it clears it)
NVIC_ST_CURRENT_R = 0;
// 4 Enable SYSTICK timer with core clock
NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;

}

void SYSTICK_DELAY(unsigned long msec){
unsigned long i;																						
for (i=0; i<msec; i++){																	//wanted delay given as msec
volatile unsigned long elapsedTime;										// Define an elapsed time for Each loop, since we want elapsed time to be = (1/1000) * frequency
unsigned long startTime = NVIC_ST_CURRENT_R;					// Copy the current value, since NVIC_ST_CURRENT_R decrements with every bus cycle and instruction
do{
elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;		// Measures the difference between start and what it currently is, followed immediately by comparing to desired time difference
																		// elapsed time is always set, then updated to be a larger value, then updated, etc.
}while(elapsedTime <= THOUSANDTH_CLK_FREQ);							// Each loop is 1/Frequency, so doing it as many times as the frequency would yield 1 s. So doing it by 1/1000 of the frequency yields 1ms
}
}
