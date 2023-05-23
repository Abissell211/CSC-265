// Author: 
// Summary:
// Inputs: 
// Outputs: 
// DATE
//=====================================================================================//
/* 			0.INFO: 
// ## !! NEED TO ADJUST POTENTIOMETERS FOR LIGHT CONDITIONS
// ## !! MAY BE OBSTACLES IN THE WAY, WILL NEED TO ACCOUNT FOR THIS
// so if there is something immediately infront, wait a little bit and then turn and try to go around

Drive from point A, follow the walls and return to point A by making left turns.
	A) Need to move forward/backward
	
	TO L298N MOTOR CONTROLLER:
	MOTOR: 	9V 25GA-370
	FROM MOTOR - HALL SENSOR:
	ULTRA-SONIC: HC-SR04
	INFRA-RED: HW-201
	
	B) Need to turn
	C) Need to measure distance from bot to obstacle
		a)Sonar? Infrared?
	D) Need to track distance travelled / offset from start
		a) Hall sensor for velocity -> Can find distance using wheel circumference and time
			1)	Use distance from track face that contacts the ground and the center of the gear
		b) IR Encoder Wheel for distance
		c) Can track offset via X and Z distance
	E) Method 1:
			Forward for C meters
			Turn Left
			Forward for D meters
			Turn Left
			Forward for C meters
			Turn Left
			Forward for D meters
	F) Method 2:
			Points: (0,0), (C,0), (C,-D), (0,-D)
			Path starts at Point 0
			Path to Point 1 by making total offset between Current Position and Point 1 be 0.
			Update Path to for next point
			Repeat previous 2 steps until Current Position = Point 0
No external interference nor external control (no helping it along, no guiding it)
It will not contact/bump into anything
	A)	Need to detect collision / distance to collision
		a)	Can use Infrared Sensor or Echo Detection
		ULTRASONIC:
		PROXY:
	B) Need to update movement to stop/slow down/avoid obstacle
In event that it is completely blocked, the vehicle will stop and indicate it cannot proceed
	A)	If it cant go left, right, forward, backward -> Indicate blockage
SPECIFIC PIN ASSIGNMENTS^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
		ULTRASONIC:
			=> Front ULTRASONIC
				PD0 = US Output [digital, output]
				PD1 = US Input		~~Need to get time-span of high level when signal returns
			=> Right ULTRASONIC
				PD2 = US Output [digital, output]
				PD3 = US Input
			=> Rear ULTRASONIC
				PA4 = US Output [digital, output]
				PA5 = US Input 
			=> Left ULTRASONIC
				PD6 = US Output [digital, output]
				PD7	= US Input
		PROXY:
			=> Front SENSOR
				PB2 = IR Sensor Input [digital, input][interrupt on rising edge]
			=> Right SENSOR
				PB3 = IR Sensor Input [digital, input][interrupt on rising edge]
			=> Rear SENSOR 
				PB4 = IR Sensor Input [digital, input][interrupt on rising edge]
			=> Left SENSOR
				PB5 = IR Sensor Input [digital, input][interrupt on rising edge]
		FROM MOTOR - HALL SENSOR:
				PC4 = HALLSENSEA1
				PC5 = HALLSENSEA2
				PC6 = HALLSENSEB1
				PC7 = HALLSENSEB2		
		TO L298N MOTOR CONTROLLER:
				PB0 = FRONT MOTOR ENABLE [digital, output] (CW = FORWARD for LEFT TRACK
					uses 74HC04 (NOT Gate)
				PB6 = FRONT MOTOR SPEED [digital, output][Pulse-Width Modulated]
			
				PB1 = REAR MOTOR ENABLE[digital, output] (CCW = FORWARD for RIGHT TRACK)
					uses 74HC04 (NOT Gate)
				PB7 = REAR MOTOR SPEED [digital, output][Pulse-Width Modulated]

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//
 			ISSUES and SUGGESTIONS: 	
		If there is an object on the left hand or right hand side, IR probably won't detect
		but there is a chance that the UltraSonic does. 

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//
			TODO:
			
			[X] get movement working (move forward, move backwards, turn)
			[~] get movement working for specific distances (move 1 ft, turn 90 degrees)
				[ ] Hall sensor input
				[X] Specific distance for signal input
			[ ] get movement for specific path required (move forward, turn left, move forward, turn left, move forward, turn left, move forward, turn right)
			
			[ ] Ultrasonic sensor returning information
			[ ] Ultrasonic sensor returning usable information in cm

			[ ] Infrared returning information
			[ ] Infrared causing interrupt
			
			[ ] FIX THE HALL SENSOR

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//
			DONE/SOLVED:
		"Solved" as of 4/13/22 (no longer using the board these issues occurred on):
			[] PB7? with simple for loop to increment speed by 10, wait 1 second, continue
			the REAR motor controlling RIGHT track doesn't change speed like PB6 does.
			PB7 steadily increases and PB6 steadily increases in terms of output rms BUT
			there is a voltage differential between them that only grows as the duty cycle
			increases. At supposedly 90% duty cycle, PB6 outputs 2.6 V and PB7 outputs 1.7 V
			I don't know why...
			[] PB7? Rear Motor will randomly reverse direction
			[] PB7? Rear motor speed is inconsistent
			
			Honestly, i don't know. At maximum duty cycle (99%, for some reason it won't
			do 100%) PB6 will output 3.2 V (which is basically the max that can be output)
			and PB7 will output 2.13 V. There is a consistent ratio between PB6 and PB7 of
			about 1.5, where PB6 is 1.5x greater than PB7.
			
			Even further odd, PB0 and PB1 (controlling the direction of motors) are the same
			value. Which means one motor SHOULD be going in the same rotation as the other,
			and if both motors are rotating CW or CCW, then the robot should be turning,
			not moving forward. It'd be one thing if there was reduced efficiency for
			moving one direction compared to the other. The outputs PB6 and PB7 are Not what
			they should be
		"Solution" was to ignore PB7, instead send PB6 to handle both PWM.
======================================================================================*/
//=====================================================================================//
/*===================|  1. Pre-processor Directive Section   |========================*/
/*----------------------1__PIN DEFINES------------------------------------------------*/
#define PIN_0										0x01
#define PIN_1										0x02
#define PIN_2										0x04
#define PIN_3										0x08
#define PIN_4										0x10
#define PIN_5										0x20
#define PIN_6										0x40
#define PIN_7										0x80
/*----------------------1__ PORT A DEFINES--------------------------------------------*/
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
/*----------------------1__ PORT B DEFINES--------------------------------------------*/
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x40005520))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
/*- - - - - - - - - - - PORT B INTERRUPTS- - - - - - - - - - - - - - - - - - - - - - -*/
#define GPIO_PORTB_IS_R         (*((volatile unsigned long *)0x40005404))
#define GPIO_PORTB_IBE_R        (*((volatile unsigned long *)0x40005408))
#define GPIO_PORTB_IEV_R        (*((volatile unsigned long *)0x4000540C))
#define GPIO_PORTB_IM_R         (*((volatile unsigned long *)0x40005410))
#define GPIO_PORTB_RIS_R        (*((volatile unsigned long *)0x40005414))
#define GPIO_PORTB_MIS_R        (*((volatile unsigned long *)0x40005418))
#define GPIO_PORTB_ICR_R        (*((volatile unsigned long *)0x4000541C))
#define NVIC_PRI0_R             (*((volatile unsigned long *)0xE000E400))
#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))
/*----------------------1__ PORT C DEFINES--------------------------------------------*/
#define GPIO_PORTC_DATA_R       (*((volatile unsigned long *)0x400063FC))
#define GPIO_PORTC_DIR_R        (*((volatile unsigned long *)0x40006400))
#define GPIO_PORTC_AFSEL_R      (*((volatile unsigned long *)0x40006420))
#define GPIO_PORTC_PUR_R        (*((volatile unsigned long *)0x40006510))
#define GPIO_PORTC_DEN_R        (*((volatile unsigned long *)0x4000651C))
#define GPIO_PORTC_LOCK_R       (*((volatile unsigned long *)0x40006520))
#define GPIO_PORTC_CR_R         (*((volatile unsigned long *)0x40006524))
#define GPIO_PORTC_AMSEL_R      (*((volatile unsigned long *)0x40006528))
#define GPIO_PORTC_PCTL_R       (*((volatile unsigned long *)0x4000652C))
/*----------------------1__ PORT D DEFINES--------------------------------------------*/
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x40007520))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))
/*----------------------1__ PORT F DEFINES--------------------------------------------*/
#define PORTF_BASE							0x40025000
#define SW1											(*((volatile unsigned long *)(PORTF_BASE | 0x040)))
#define SW2											(*((volatile unsigned long *)(PORTF_BASE | 0x004)))
#define LED											(*((volatile unsigned long *)(PORTF_BASE | 0x038)))
#define DATA										0x3FC
#define DIR											0x400
#define AFSEL										0x420
#define PUR											0x510
#define DEN											0x51C
#define LOCK										0x520
#define CR											0x524
#define AMSEL										0x528
#define PCTL										0x52C
#define GPIO_PORTF_DATA_R				(*((volatile unsigned long *)(PORTF_BASE | DATA)))
#define GPIO_PORTF_DIR_R				(*((volatile unsigned long *)(PORTF_BASE | DIR)))
#define GPIO_PORTF_AFSEL_R			(*((volatile unsigned long *)(PORTF_BASE | AFSEL)))
#define GPIO_PORTF_PUR_R				(*((volatile unsigned long *)(PORTF_BASE | PUR)))
#define GPIO_PORTF_DEN_R				(*((volatile unsigned long *)(PORTF_BASE | DEN)))
#define GPIO_PORTF_LOCK_R				(*((volatile unsigned long *)(PORTF_BASE | LOCK)))
#define GPIO_PORTF_CR_R					(*((volatile unsigned long *)(PORTF_BASE | CR)))
#define GPIO_PORTF_AMSEL_R			(*((volatile unsigned long *)(PORTF_BASE | AMSEL)))
#define GPIO_PORTF_PCTL_R				(*((volatile unsigned long *)(PORTF_BASE | PCTL)))
	
#define PORTFIS									0x404
#define PORTFIBE								0x408
#define PORTFIEV								0x40C
#define PORTFIM									0x410
#define PORTFMIS								0x418
#define PORTFICR								0x41C
#define GPIO_PORTF_IS_R					(*((volatile unsigned long *)(PORTF_BASE | PORTFIS)))
#define GPIO_PORTF_IBE_R				(*((volatile unsigned long *)(PORTF_BASE | PORTFIBE)))
#define GPIO_PORTF_IEV_R				(*((volatile unsigned long *)(PORTF_BASE | PORTFIEV)))
#define GPIO_PORTF_IM_R					(*((volatile unsigned long *)(PORTF_BASE | PORTFIM)))
#define GPIO_PORTF_MIS_R				(*((volatile unsigned long *)(PORTF_BASE | PORTFMIS)))
#define GPIO_PORTF_ICR_R				(*((volatile unsigned long *)(PORTF_BASE | PORTFICR)))

/*----------------------1__ SYSTICK---------------------------------------------------*/
#define NVIC_ST_CTRL_R					(*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R				(*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R				(*((volatile unsigned long *)0xE000E018))
#define THOUSANDTH_CLK_FREQ			80000
/*- - - - - - - - - - - PULSE-WIDTH MODULATION - - - - - - - - - - - - - - - - - - - -*/
#define PWM0_0_CTL_R       	   	(*((volatile unsigned long *)0x40028040))
#define PWM0_0_GENB_R     	   	(*((volatile unsigned long *)0x40028064))
#define PWM0_0_LOAD_R     	  	(*((volatile unsigned long *)0x40028050))
#define PWM0_0_CMPB_R     	   	(*((volatile unsigned long *)0x4002805C))
#define PWM0_0_GENA_R      	   	(*((volatile unsigned long *)0x40028060))
#define PWM0_0_CMPA_R      	   	(*((volatile unsigned long *)0x40028058))
#define PWM0_ENABLE_R      	   	(*((volatile unsigned long *)0x40028008))

#define SYSCTL_RCGCPWM_R        (*((volatile unsigned long *)0x400FE640))
#define PWM1_ENABLE_R           (*((volatile unsigned long *)0x40029008))
#define PWM1_1_CTL_R            (*((volatile unsigned long *)0x40029080))
#define PWM1_1_INTEN_R          (*((volatile unsigned long *)0x40029084))
#define PWM1_1_RIS_R            (*((volatile unsigned long *)0x40029088))
#define PWM1_1_ISC_R            (*((volatile unsigned long *)0x4002908C))
#define PWM1_1_LOAD_R           (*((volatile unsigned long *)0x40029090))
#define PWM1_1_COUNT_R          (*((volatile unsigned long *)0x40029094))
#define PWM1_1_CMPA_R           (*((volatile unsigned long *)0x40029098))
#define PWM1_1_CMPB_R           (*((volatile unsigned long *)0x4002909C))
#define PWM1_1_GENA_R           (*((volatile unsigned long *)0x400290A0))
#define PWM1_1_GENB_R           (*((volatile unsigned long *)0x400290A4))
#define PWM1_1_DBCTL_R          (*((volatile unsigned long *)0x400290A8))
#define PWM1_1_DBRISE_R         (*((volatile unsigned long *)0x400290AC))
#define PWM1_1_DBFALL_R         (*((volatile unsigned long *)0x400290B0))
#define PWM1_1_FLTSRC0_R        (*((volatile unsigned long *)0x400290B4))
#define PWM1_1_FLTSRC1_R        (*((volatile unsigned long *)0x400290B8))
#define PWM1_1_MINFLTPER_R      (*((volatile unsigned long *)0x400290BC))
/*----------------------1__ CLOCK REGISTERS-------------------------------------------*/
#define SYSCTL_RCGC0_R        	(*((volatile unsigned long *)0x400FE100))
#define SYSCTL_RCGC2_R       	 	(*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGCGPIO_R    	 	(*((volatile unsigned long *)0x400FE608))
#define SYSCTL_RCC_R         	 	(*((volatile unsigned long *)0x400FE060))
/*- - - - - - - - - - - PHASE LOCK LOOP -- - - - - - - - - - - - - - - - - - - - - - -*/
#define SYSCTL_RCC2_R         	(*((volatile unsigned long *)0x400FE070))
#define SYSCTL_RIS_R          	(*((volatile unsigned long *)0x400FE050))
#define SYSDIV2									4
/*- - - - - - - - - - - GPIO WIDE TIMER  - - - - - - - - - - - - - - - - - - - - - - -*/
#define SYSCTL_RCGCWTIMER_R     (*((volatile unsigned long *)0x400FE65C))
#define WTIMER0_CFG_R           (*((volatile unsigned long *)0x40036000))
#define WTIMER0_TAMR_R          (*((volatile unsigned long *)0x40036004))
#define WTIMER0_TBMR_R          (*((volatile unsigned long *)0x40036008))
#define WTIMER0_CTL_R           (*((volatile unsigned long *)0x4003600C))
#define WTIMER0_TAMATCHR_R      (*((volatile unsigned long *)0x40036030))
#define WTIMER0_TAR_R           (*((volatile unsigned long *)0x40036048))
/*--------------|           1__TIMER0A DEFINES                        |--------------*/
#define			SYSCTL_RCGCTIMER_R      (*((volatile unsigned long *)0x400FE604))
#define			TIMER0_CTL_R            (*((volatile unsigned long *)0x4003000C))
#define			TIMER0_CFG_R            (*((volatile unsigned long *)0x40030000))
#define			NVIC_PRI4_R             (*((volatile unsigned long *)0xE000E410))
#define			TIMER0_TAMR_R           (*((volatile unsigned long *)0x40030004))
#define			TIMER0_TAILR_R          (*((volatile unsigned long *)0x40030028))
#define			TIMER0_ICR_R            (*((volatile unsigned long *)0x40030024))
#define			TIMER0_IMR_R            (*((volatile unsigned long *)0x40030018))
#define 		TIMER0_TAPR_R           (*((volatile unsigned long *)0x40030038))
//=====================================================================================//
/*===================|  2. Declaration Section               |========================*/
/*----------------------2__GLOBAL VARIABLES-------------------------------------------*/

unsigned int 	SW1_Press = 0;
unsigned int 	SW2_Press = 0;
unsigned int 	PERIOD = 50000;
double				track_diameter = 47.88;	// in mm
double 				Circumference = 150.419;				// in mm
double				Center_Rectangle_Length = 13741.4;
double				Length_Wise_Trip	=	13741.4 + 1943.1;	// check second addition (1941.) width of hallyway
double 				Center_Rectangle_Width	=	8597.9;
double 				Width_Wise_Trip	=	8597.9 + 1778;	// check second addition (1778) for width of hallways

unsigned int 	echo_time;
unsigned int 	average;
unsigned int 	i;
unsigned int 	TripComplete;	// 1 = TRUE, 0 = FALSE
unsigned int 	flag;					// 1 = TRUE, 0 = FALSE
unsigned long distance_left_in_clock_cycles = 0;
volatile unsigned int	Timer0_Flag = 0;	// this value is subject to change by interrupt
/*----------------------2__GLOBAL FUNCT ----------------------------------------------*/
// funct name
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
REQUIRES:
INPUTS:
RESULTS: 
- - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - -*/
void DisableInterrupts(void);
void EnableInterrupts(void);
void Move_Set_Speed(unsigned long duty);

void 		SYSTICK_DELAY	(unsigned long msec){
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

void 		Move_Forward	(void){
	GPIO_PORTB_DATA_R |= PIN_0;
	GPIO_PORTB_DATA_R |= PIN_1;
}
void		Move_Stop(){

// The bot has some inertia when moving forward. Possibly add here functionality such:

/*
Move_Reverse();
Move_Set_Speed(50000);
SYSTICK_DELAY(20);

//Set Speed back to 0
	PWM1_1_CMPB_R = 			 1;
	PWM1_1_CMPA_R = 			 1;

Move_Forwards();
*/


	unsigned long duty = 1;
	PWM1_1_CMPB_R = 			duty - 1;
	PWM1_1_CMPA_R = 			duty - 1;
}

void		Move_Reverse(void){
	GPIO_PORTB_DATA_R &= ~PIN_0;
	GPIO_PORTB_DATA_R &= ~PIN_1;
}	

void 		Move_Turn_Right(void){
	GPIO_PORTB_DATA_R &= ~PIN_0;
	GPIO_PORTB_DATA_R |= PIN_1;
}

void		Move_Turn_Right_90(void){
		Move_Turn_Right();
		Move_Set_Speed(25000);
		SYSTICK_DELAY(580);		// Was 680, changed to reflect actual movement of Move_Turn_Left_90
}

void 		Move_Turn_Left(void){
	GPIO_PORTB_DATA_R |= PIN_0;
	GPIO_PORTB_DATA_R &= ~PIN_1;
}

void		Move_Turn_Left_90(void){
		LED = 0x02;
		Move_Stop();		// Want Bot to be stopped before turning
		SYSTICK_DELAY(2000);		// Wait  a second to ensure stoppage
	
		LED = 0x08;
		Move_Turn_Left();
		Move_Set_Speed(25000);
		SYSTICK_DELAY(580);		// Time to make a 90 degree rotation
	
		LED = 0x02;
		Move_Stop();		// 
		SYSTICK_DELAY(2000);
		Move_Forward();				// Bot was moving some direction, want to be moving 90 degree left in relation to that original direction
	
		
}

void		Move_Turn_Left_90_MAIN(void){
		LED = 0x02;
		Move_Stop();		// Want Bot to be stopped before turning
		SYSTICK_DELAY(2000);		// Wait  a second to ensure stoppage
	
		LED = 0x08;
		Move_Turn_Left();
		Move_Set_Speed(25000);
		SYSTICK_DELAY(300);		// Time to make a 90 degree rotation
	
		LED = 0x02;
		Move_Stop();		// 
		SYSTICK_DELAY(2000);
		Move_Forward();				// Bot was moving some direction, want to be moving 90 degree left in relation to that original direction
	
		
}

void 		Move_Right_Track_Speed(unsigned long duty){
	PWM1_1_CMPB_R = 			duty - 1;								// count value when output rises
	

}
void 		Move_Left_Track_Speed(unsigned long duty){
	// IF duty here becomes 0, make the minimum 1
	PWM1_1_CMPA_R = 			(duty - 1500) - 1;								// count value when output rises, trying to reduce listing via offset (Note: Pretty sure this is for the Right_track)

}


void 		Move_Set_Speed(unsigned long duty){
	Move_Left_Track_Speed(duty);
	Move_Right_Track_Speed(duty);
}

// Put in the distance to convert to number of rotations using the Circumference
void 		Move_Distance(double Distance) {	// in mm
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/////NOTE!!!\\\\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\	
 *	- For 1 m input distance the actually covered distance will be 0.95 m 
 *	- That is about a 50mm subtraction to the actually distance, can not multiple below 14% or subtract from the distance or the bot will not move at all!
 *	- make sure to account for this for planning the trips.
*/
	
//	unsigned int Rotation_Count_Left = 0;		// Count for left hall sensor 
//	unsigned int Rotation_Count_Right = 0;	// Count for Right hall sensor





// If using Ultrasonics and timers:
/*
	distance_left_in_clock_cycles =

*/
 


	unsigned int Rotation_Count = 0;				// Count for how many full revolutions of the motor
	unsigned int Required_Rotations = 0;		// Require number of full revolutions to complete the trip length
	
	Distance *= 0.2;
	
	Required_Rotations = Distance/Circumference;				// Required_Rotations = (distance of trip requested)/(Circumference)
	Required_Rotations *= 75;														// Gearbox Ratio of 75:1, where track rotates once(1) for every 75 motor rotations
	Required_Rotations *= 12;														// Using Rising/Falling Edge Count, where 1 rotation is 12 Falling or Rising edges (So counting H->L AND L->H means you counted 1 Rising OR 1 Falling Edge

	LED = 0x02;
	while (Rotation_Count <= Required_Rotations){
		while( (GPIO_PORTC_DATA_R & PIN_4) == PIN_4 ){};		// Hold until Falling Edge (each EDGE indicates a movement of 15 deg FOR THE MOTOR
		while( (GPIO_PORTC_DATA_R & PIN_4) != PIN_4 ){};		// Hold until Rising Edge (When it transitions, it becomes low. )
		// Big note: risingB + risingA + fallingB + fallingA = period, 4 counts per 1 period (which is also determined by risingA to risingA)
		// hightimeA =/= lowtimeA
		
		// If the second check isn't here, the Rotation Count would be like thus: 
		//nothing(pin high) ---->|, exit while (...==PIN_4) and update Rotation_count, check Rcount vs Rrot, check while(...==PIN_4) (pin is low still), update Rotation_count
		// Ensure that when the outside while (...!= Rrot) starts, it starts with the first while (...==PIN_4) being true and thus getting captured in it
		LED ^= 0x04;
		Rotation_Count++;																// 
	
	}
	LED = 0x08;
	Move_Stop();
	
	// issue with Move_Distance is: how to poll for distances from UltraSonic?
		// Interrupt that keeps track of rotations
		// Timer Interrupt that allows loop of checking all 4 UltraSonics, where the loop condition is if the distance has been surpassed
		// Timer as Counter? Issue of possibly misinterpretting edges due to current spikes/draw
		// Specifically with the way the current systick delay is set up right now, would need to change for Move for X seconds, and we measure how far it travelled
			// Change Systick Delay such that it interrupts instead of being a while loop
				// SYSTICK_DELAY can instead be SYSTICK_DELAY_10ms initialize it for interrupts, the SYSTICK_Handler will space it do the elapsed_time comparison
				// SYSTICK_DELAY_10ms will be in 
		// Similarly: Whenever the SYSTICK delay is going and an interrupt occurs, it breaks OUT of the Systick_delay. 
		// When it goes to resume its comparison, elapsed_time will be updated to a new (and unwanted) value.
		
}

void 			Timer0_Init_Specific(unsigned int delay_time,unsigned long freq_div){		// 80000000, 1 for 1 second interrupt
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
REQUIRES: Timer0A Defines
RESULTS: Setup Timer0 for interrupt every 1 second
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

volatile unsigned long delay;
//TIMER0_TAR_R is the actual value of timer 0A
Timer0_Flag = 0;

// USING TIMER0A, 16/32 bit
	SYSCTL_RCGCTIMER_R      |= 0x1;	// set bit 0
	delay = SYSCTL_RCGCTIMER_R;	// clock stabilization allowance
// disable timer, [P737], bit 0 is TimerA enable. clear disables, set enables
	TIMER0_CTL_R            &= ~0x1;
// TIMER0A in 32 BIT MODE
	TIMER0_CFG_R            &= ~0x7;	// Bits 2-1-0 = 000, so 0b0111 = 0x7, clear these bits
// ONESHOT DOWN COUNTER
	TIMER0_TAMR_R           |= 0x1;	// Oneshot down counter
// 16M clock cycles for 16MHz operation, less by one for load cycle
	TIMER0_TAILR_R          = (freq_div - 1);	
	TIMER0_TAPR_R  					= (delay_time - 1);											// Essentially, the core clock DIVIDED by this value is the frequency "used" for TAILR
	// if core clock = 80MHz, and TAILR = 80M-1, then if TAPR = (2-1), the frequency used by TAILR is 40MHz (80MHz/2) and the time is effectively doubled
	TIMER0_ICR_R            = 0x1;	// clears timer0 timeout flag
	TIMER0_IMR_R            |= 0x1;	// Arm Timer0 timeout interrupt		

	NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)| (2<<29);
// bits 31-29 as target, Priority 2, Shift priority value into the location (29 here)
// [P140] NVIC_EN0 handles interrupt numbers 0-31
	NVIC_EN0_R |= (0x1 << 19);	// Timer0A is bit 19 [Page 102] for NVIC Enable
	
	TIMER0_CTL_R |= 0x1;			// Enable timer
}


void			Timer0A_Handler(){
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
REQUIRES: Timer0A Defines, Timer0_Init(), Timer0_Start()
RESULTS: Toggle Red LED
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
Timer0_Flag = 1;
TIMER0_ICR_R |= 0x01;			// Acknowledge Timer0 timeeout


}
unsigned long 	speed_get(void){

// This function will set up Pin4 of PortC to be a counter, utilizing the TIMER peripheral


Timer0_Init_Specific(1000,THOUSANDTH_CLK_FREQ);	// 1000 ms = 1 s
WTIMER0_CTL_R |= 0x1;	// Enable TimerA for counting

while (Timer0_Flag == 0){};	// busy-wait loop for however long (want 1 second of time pass and X many counts to find rotational speed easily)
return WTIMER0_TAR_R;				// this is wide timer A, will only be incremented when a rising edge detected



}

void start_distance_tracking(void){

WTIMER0_CTL_R |= 0x1;	// Enable TimerA for counting

}


unsigned long return_distance(void){

return WTIMER0_TAR_R;				// this is wide timer A, will only be incremented when a rising edge detected

}




void 	WTimer0ACounter_Init(void){

// This function will count the number of pulses from Pin4 of PortC
// WT0CCP0 [P 651]

// note for reading/writing to this if its concatenated and 64 bits [P 720], ignorable
volatile unsigned long delay;
SYSCTL_RCGCWTIMER_R |= 0x1;
delay = SYSCTL_RCGCWTIMER_R ;
SYSCTL_RCGCGPIO_R |= 0x04;	// port c bit
GPIO_PORTC_DIR_R &= ~PIN_4;
GPIO_PORTC_DEN_R |= PIN_4;
GPIO_PORTC_AFSEL_R |= PIN_4;
GPIO_PORTB_PCTL_R &= ~(15<<16);
GPIO_PORTC_PCTL_R |= (7<<16);
WTIMER0_CTL_R &= ~0x1;
WTIMER0_CFG_R |= (0x4);	// select 32 bit timer config [P 728]
WTIMER0_TAMR_R = 0x13;		// up-count, edge-count, capture mode (bit 1 to 0 is 11, bit 2 is 0, bit 4 is 1)
WTIMER0_TAMATCHR_R = 0xFFFF; // set count limit

WTIMER0_CTL_R &= ~(3<<2);		// 0x0 is positive edge for Timer A event

WTIMER0_CTL_R |= 0x1;		// Enable timer A 


}

void 		test_Move_Distance(unsigned int test_rot) {	// in mm
//	unsigned int Rotation_Count_Left = 0;		// Count for left hall sensor 
//	unsigned int Rotation_Count_Right = 0;	// Count for Right hall sensor
	unsigned int Rotation_Count = 0;				// Count for how many full revolutions of the motor
	
	LED = 0x02;
	while (Rotation_Count <= test_rot){
		while( (GPIO_PORTC_DATA_R&PIN_4)==PIN_4 ){};		// Hold until Falling Edge (each EDGE indicates a movement of 15 deg FOR THE MOTOR
		while( (GPIO_PORTC_DATA_R&PIN_4)!= PIN_4){};		// Hold until Rising Edge (When it transitions, it becomes low. )
		// Big note: risingB + risingA + fallingB + fallingA = period, 4 counts per 1 period (which is also determined by risingA to risingA)
		// hightimeA =/= lowtimeA
		
		// If the second check isn't here, the Rotation Count would be like thus: 
		//nothing(pin high) ---->|, exit while (...==PIN_4) and update Rotation_count, check Rcount vs Rrot, check while(...==PIN_4) (pin is low still), update Rotation_count
		// Ensure that when the outside while (...!= Rrot) starts, it starts with the first while (...==PIN_4) being true and thus getting captured in it
		LED ^= 0x04;
		Rotation_Count++;																// 
	
	}
	LED = 0x08;
}

void 		V2_Move_Distance(unsigned int Distance) {	// in mm
	unsigned int Rotation_Count_Left = 0;		// Count for left hall sensor 
	unsigned int Rotation_Count_Right = 0;	// Count for Right hall sensor
	unsigned int Rotation_Count = 0;				// Count for how many full revolutions of the motor
	unsigned int Required_Rotations = 0;		// Require number of full revolutions to complete the trip length
		
	Required_Rotations = Distance/Circumference;				// Required_Rotations = (distance of trip requested)/(Circumference)
	//Required_Rotations *= 75;														// Gearbox Ratio of 75:1, where track rotates once(1) for every 75 motor rotations
	//Required_Rotations *= 12;														// Using Rising/Falling Edge Count, where 1 rotation is 12 Falling or Rising edges (So counting H->L AND L->H means you counted 1 Rising OR 1 Falling Edge
	LED = 0x02;
	while (Rotation_Count != Required_Rotations){
		while( (GPIO_PORTC_DATA_R&PIN_4)==PIN_4 ){};		// Hold until Falling Edge (each EDGE indicates a movement of 15 deg FOR THE MOTOR
		while( (GPIO_PORTC_DATA_R&PIN_4)!= PIN_4){};		// Hold until Rising Edge (When it transitions, it becomes low. )
		Rotation_Count_Left++;
		LED = 0x04;
		while( (GPIO_PORTC_DATA_R&PIN_5)==PIN_5){};		// Hold until Falling Edge (each EDGE indicates a movement of 15 deg FOR THE MOTOR
		while( (GPIO_PORTC_DATA_R&PIN_5)!= PIN_5){};		// Hold until Rising Edge (When it transitions, it becomes low. )
		Rotation_Count_Right++;
		LED = 0x08;
		// Big note: risingB + risingA + fallingB + fallingA = period, 4 counts per 1 period (which is also determined by risingA to risingA)
		// hightimeA =/= lowtimeA
		
		// If the second check isn't here, the Rotation Count would be like thus: 
		//nothing(pin high) ---->|, exit while (...==PIN_4) and update Rotation_count, check Rcount vs Rrot, check while(...==PIN_4) (pin is low still), update Rotation_count
		// Ensure that when the outside while (...!= Rrot) starts, it starts with the first while (...==PIN_4) being true and thus getting captured in it
		if(Rotation_Count_Left == 12 && Rotation_Count_Right == 12) {
			Rotation_Count++;																// 
			Rotation_Count_Left = 0;
			Rotation_Count_Right = 0;
			LED = 0x0A;
		}
	}
}
/*	PORT A INFO

		=> Rear ULTRASONIC
			PA4 = US Output [digital, output]
			PA5 = US Input 
*/
void 		PORTA_Init(void){							
volatile unsigned long delay;
SYSCTL_RCGCGPIO_R |= 0x01;    				// 1) A clock   											###
delay = SYSCTL_RCGCGPIO_R;          	// delay  													 	###
GPIO_PORTA_DIR_R &= ~(PIN_5);         // 5) PA5 Input     									###
GPIO_PORTA_DIR_R |= (PIN_4);        	// 5) PA4 Output     									###
GPIO_PORTA_DEN_R |= (PIN_4 | PIN_5);   // 7) enable digital pins PA4 and PA5###
}

/*	PORT B INFO
	TO MOTOR CONTROLLER:
		PB0 = FRONT MOTOR ENABLE [digital, output] (CW = FORWARD for LEFT TRACK
		PB6 = FRONT MOTOR SPEED [digital, output][Pulse-Width Modulated]
		
		PB1 = REAR MOTOR ENABLE[digital, output] (CCW = FORWARD for RIGHT TRACK)
		PB7 = REAR MOTOR SPEED [digital, output][Pulse-Width Modulated]
		PROXY:
		=> Front SENSOR
			PB2 = IR Sensor Input [digital, input][interrupt on rising edge]
		=> Right SENSOR
			PB3 = IR Sensor Input [digital, input][interrupt on rising edge]
		=> Rear SENSOR 
			PB4 = IR Sensor Input [digital, input][interrupt on rising edge]
		=> Left SENSOR
			PB5 = IR Sensor Input [digital, input][interrupt on rising edge]
			
*/
void 		PORTB_Init		(void){	// ONLY HANDLES NON-PWM PINS
volatile unsigned long delay;
SYSCTL_RCGCGPIO_R |= 0x02;     // 1) B clock
delay = SYSCTL_RCGCGPIO_R;           // delay   
GPIO_PORTB_LOCK_R = 0x4C4F434B;   // 2) unlock   
GPIO_PORTB_CR_R |= 0x3F;           // allow changes to PB0-5    
GPIO_PORTB_AFSEL_R &= ~(PIN_0 | PIN_1 | PIN_2 | PIN_3 | PIN_4 | PIN_5 );        // 6) no alternate function for PB0-5
GPIO_PORTB_AMSEL_R &= ~0x3F;        // 3) disable analog function for PB0-5
GPIO_PORTB_PCTL_R &=    // 4) GPIO clear bit PCTL  for PB0-5
	 ~((15<<0) | (15<<4) | (15<<8) | (15<<16) | (15<<20) | (15<<24) );
GPIO_PORTB_DIR_R &= ~(PIN_2 | PIN_3 | PIN_4 | PIN_5 );          // 5) PB2-5 input
GPIO_PORTB_DIR_R |= (PIN_0 | PIN_1);          // 5) PB0,1 output      
GPIO_PORTB_DEN_R |= 0x3F;          // 7) enable digital pins PB0-5
//--------------------------------CONFIGURE PORTB FOR INTERRUPTS----------------------------------//
// configure PORTF bits 4 and 0 for high level trigger
// IR sensors are in negative logic, always high returns low when triggered
	GPIO_PORTB_IS_R |= (PIN_2);			// make bit 4 and 0 edge sensitive page 664
	GPIO_PORTB_IBE_R &= ~(PIN_2);		// turn off both edges page 665
	GPIO_PORTB_IEV_R &= ~(PIN_2);		// Rising edge trigger page 666
	GPIO_PORTB_ICR_R |= (PIN_2);		// clear any prior interrupt page 670
	GPIO_PORTB_IM_R |= (PIN_2);			// unmask interrupt page 667
//---------------------------------------ENABLE INTERRUPT-----------------------------------------//
// enable interrupt in NVIC and set priority to 3
// [P104] for interrupt number. GPIO PORT B is interrupt number 1,
	NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFFFF0F)| (3<<13);	// set interrupt priority to 3 page 154. Using PRIn, 4n+1-> bits are 15:13, so shift 13
	NVIC_EN0_R |= (1<<1);	// enable IRQ1 page 142   
}

void 		GPIOPortB_Handler(void){					// HANDLES PORTB INTERRUPTS
		// Front sensor Interrupt
	SYSTICK_DELAY(1);															// Wait a little bit to account for current jumps and draw (i.e. switch debouncing)
	if ((GPIO_PORTB_DATA_R&PIN_2) == PIN_2){
		GPIO_PORTB_ICR_R = PIN_2;
	}
	else{
	if ((GPIO_PORTB_MIS_R&PIN_2) == PIN_2){	// if FRONT sensor interrupts
		// want to immediately stop
		// IF/ELSE for obstacle avoidance or trip completion (TripComplete, 1 = TRUE, 0 = FALSE)
// STOP THE BOT
		LED = 0x02;
		Move_Stop();										// ## WANT TO CHECK IF IT GETS TO THIS POINT AND IF IT WORKS
		SYSTICK_DELAY(2000);		// in milliseconds
		
// TURN THE BOT LEFT
		LED = 0x08;
		Move_Turn_Left_90();
		
// STOP THE BOT
		LED = 0x02;
		Move_Stop();
		SYSTICK_DELAY(2000);		// in milliseconds
		flag = 0;
		GPIO_PORTB_ICR_R |= PIN_2;    				// acknowledge flag
		Move_Set_Speed(18000);	// Let bot move again
		LED = 0x00;
	}
}

		// Return from interrupt
}


void 		PWM0AB_Init		(unsigned int period, unsigned int duty){	// Output on PB7/M0PWM1 and PB7/M0PWM0
	volatile unsigned long delay;
	SYSCTL_RCGC0_R |= 			0x00100000;							// 1) Activate PWM0
	SYSCTL_RCGCGPIO_R |= 		0x02;										// 2) Activate port B
	delay = SYSCTL_RCGCGPIO_R;											// Allow time to finish activating
/* - - - - - PB7 - - - - -*/
	GPIO_PORTB_AFSEL_R |= 	0x80;										// 3) Enable alt funtion on PB7
	GPIO_PORTB_PCTL_R &= 	 ~0xF0000000;							// 4) Configure PB7 as M0PWM1
	GPIO_PORTB_PCTL_R |= 		0x40000000;
	GPIO_PORTB_AMSEL_R &=  ~0x80;										// Disable analog funtionality on PB7
	GPIO_PORTB_DEN_R |= 		0x80;										// Enable digital I/O on PB7
/* - - - - - PB6 - - - - -*/
	GPIO_PORTB_AFSEL_R |= 	0x40;										// 3) Enable alt funtion on PB6
	GPIO_PORTB_PCTL_R &= 	 ~0x0F000000;							// 4) Configure PB6 as M0PWM0
	GPIO_PORTB_PCTL_R |= 		0x04000000;
	GPIO_PORTB_AMSEL_R &=  ~0x40;										// Disable analog funtionality on PB6
	GPIO_PORTB_DEN_R |= 		0x40;										// Enable digital I/O on PB6
	
	SYSCTL_RCC_R &= 			~(0x000E0000);						// 5) Clearing first
	SYSCTL_RCC_R |= 			 (0x00080000);						// The writing in the 19:17 with PWMDIV 0x3 configure for /32 divider
	SYSCTL_RCC_R |= 				0x00100000;							// Use PWM divider
	PWM0_0_CTL_R = 					0x00;										// 6) Re-loading down-counting mode
	
	PWM0_0_GENB_R = 			 (0x00000C00|0x00000008);	// [P1285]		// PB7 goes low on LOAD, PB7 goes high on CMPB down
	PWM0_0_GENA_R = 			 (0x000000C0|0x00000008);	// 0xC8 in lesson		// PB6 goes low on LOAD, PB6 goes high on CMPA down
	
	PWM0_0_LOAD_R = 				period - 1;							// 7) Cycles needed to count down to 0

	PWM0_0_CMPB_R = 				duty - 1;								// 9) Count value when output rises
	PWM0_0_CMPA_R = 				duty - 1;		// count value when output rises

	PWM0_0_CTL_R |= 				0x00000001;							// 10) Start PWM0
	PWM0_ENABLE_R |= 				(0x00000002|0x00000001);							// 11) Enable PB7/M0PWM1 and PB6/M0PWM0
}

void 		PWM0A_Init		(unsigned int period, unsigned int duty){	//Output on PB6 / M0PWM0 [Page 1233] where period = 20 ms in clock cycles using PWM clock divider, and duty = period*dutycycle
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
	
	GPIO_PORTB_AFSEL_R |= 	0x80;										// 3) Enable alt funtion on PB7
	
	GPIO_PORTB_PCTL_R &= 	 ~0xF0000000;							// 4) Configure PB7 as M0PWM1
	GPIO_PORTB_PCTL_R |= 		0x40000000;
	GPIO_PORTB_AMSEL_R &=  ~0x80;										// Disable analog funtionality on PB7
	GPIO_PORTB_DEN_R |= 		0x80;										// Enable digital I/O on PB7
	
// Step 5: Configure the Run-Mode Clock configuration (RCC) register in the System Control module to use the PWM divide (USEPWMDIV) and set the dividier (PWMDIV) to divide by the approrpaite value from the table.
	SYSCTL_RCC_R &= ~(0x000E0000);		// clear first the division section
	SYSCTL_RCC_R |= (0x00080000);		// PMDIV 0x3 [Page 222] configure for /32 divider
	SYSCTL_RCC_R |= (0x00100000);		// use PWM divider

// Step 6: Disable PWM generator by writing 0x00000000 to PWMnCTL register
	PWM0_0_CTL_R = 0x00;			// Reload down-count mode

// Step 7: Configure PWM generator (PWMnGENA) to Do Nothing / Invert / Drive Low / Drive High, based on the load and zero output pulses from the counter
	PWM0_0_GENA_R = 0xC8;			// PB6 goes low on LOAD, PB6 high on CMPA down
	PWM0_0_GENB_R = (0x00000C00|0x00000008);	// [P1285]		// PB7 goes low on LOAD, PB7 goes high on CMPB down

// Step 8: Use the formula to set the timer LOAD (in PWMnLOAD) value to the required period. PWM f = System Clock / PWMDIV; Period = LOAD value = PWM f / Required f
// For instance, if sysclock is 16MHz and PWMDIV is 0, which is /2, results in PWM f of 8MHz. If desiring a f of 20kHz, LOAD value will be 8 Mhz / 20 kHz = 400
// Value for compare register depends on how the generator was set up to operate: Do nothing, invert, drive low, or drive high
// Drive high and 25% duty cycle wanted for count down mode, the COmpare would be loaded with value = (100% - desired duty cycle) * PWMnLOAD = 75% * 400 = 300
	PWM0_0_LOAD_R = period - 1;		// cycles needed to count down to 0
	
	PWM0_0_CMPA_R = duty - 1;		// count value when output rises
	PWM0_0_CMPB_R = 				duty - 1;								// 9) Count value when output rises


// Step 9: Enable PWM generator by writing 1 to appropriate bit in the PWMnCTL register
	PWM0_0_CTL_R |= 0x00000001;		// start PWM0

// Step 10: Enable PWM output by enabling the appropriate pins in the PWMENABLE register
	PWM0_ENABLE_R |= 				(0x00000002|0x00000001);							// 11) Enable PB7/M0PWM1 and PB6/M0PWM0
}
void 		PWM1A_Init(unsigned int period, unsigned int duty){
	
// PA6 : M1PWM2 with PCTL = 5, PA7 : M1PWM3 with PCTL = 5	[P 1351]
	volatile unsigned long delay;
	SYSCTL_RCGCPWM_R |= 			0x2;							// 1) Activate PWM
	SYSCTL_RCGCGPIO_R |= 		0x01;										// 2) Activate port A
	delay = SYSCTL_RCGCGPIO_R;											// Allow time to finish activating
	GPIO_PORTA_AFSEL_R |= 	0x80;										// 3) Enable alt funtion on PA7
	GPIO_PORTA_PCTL_R &= 	 ~0xF0000000;							// 4) Configure PA7 as M1PWM3
	GPIO_PORTA_PCTL_R |= 		0x50000000;
	GPIO_PORTA_AMSEL_R &=  ~0x80;										// Disable analog funtionality on PA7
	GPIO_PORTA_DEN_R |= 		0x80;										// Enable digital I/O on PA7
	
	GPIO_PORTA_AFSEL_R |= 	0x40;										// 3) Enable alt funtion on PA6
	GPIO_PORTA_PCTL_R &= 	 ~0x0F000000;							// 4) Configure PA6 as M1PWM2
	GPIO_PORTA_PCTL_R |= 		0x05000000;
	GPIO_PORTA_AMSEL_R &=  ~0x40;										// Disable analog funtionality on PA7
	GPIO_PORTA_DEN_R |= 		0x40;										// Enable digital I/O on PA7
	
	GPIO_PORTA_CR_R |=	(PIN_7 | PIN_6);					// PUR is protected by CR, need to enable changes first
	GPIO_PORTA_PUR_R |= (PIN_7 | PIN_6);					// Enable Pull-up for PWM
	
	SYSCTL_RCC_R &= 			~(0x000E0000);						// 5) Clearing first
	SYSCTL_RCC_R |= 			 (0x00080000);						// The writing in the 19:17 with PWMDIV 0x3 configure for /32 divider
	SYSCTL_RCC_R |= 				0x00100000;							// Use PWM divider
	PWM1_1_CTL_R = 					0x00;										// 6) Re-loading down-counting mode
	PWM1_1_GENB_R = 			 (0x00000C00|0x00000008);	// 0xC8 in lesson		// PB7 goes low on LOAD, PB7 goes high on CMPB down
	PWM1_1_GENA_R = 			 (0x000000C0|0x00000008);	// 0xC8 in lesson		// PB7 goes low on LOAD, PB7 goes high on CMPB down
	PWM1_1_LOAD_R = 				period - 1;							// 7) Cycles needed to count down to 0
	PWM1_1_CMPB_R = 				duty - 1;								// 9) Count value when output rises
	PWM1_1_CMPA_R = 				duty - 1;								// 9) Count value when output rises
	PWM1_1_CTL_R |= 				0x00000001;							// 10) Start PWM1 for M1PWM2 and M1PWM3
	PWM1_ENABLE_R |= 				(1<<3)|(1<<2);							// 11) Enable PA6/M1PWM2 and PA7/M1PWM3








}

/*	PORT C INFO
	FROM MOTOR - HALL SENSOR:
		PC4 = HALLSENSEA1
		PC5 = HALLSENSEA2
		PC6 = HALLSENSEB1
		PC7 = HALLSENSEB2
*/
void 		PORTC_Init		(void){		
volatile unsigned long delay;
SYSCTL_RCGCGPIO_R |= 0x04;     // 1) C clock
delay = SYSCTL_RCGCGPIO_R;           // delay     
GPIO_PORTC_DIR_R &= ~(PIN_4 | PIN_5 | PIN_6 | PIN_7);          // 5) All PC4,5,6,7 are input (input are clear     
GPIO_PORTC_DEN_R |= (PIN_4 | PIN_5 | PIN_6 | PIN_7);          // 7) enable digital pins PC4,5,6,7

}
/*	PORT D INFO
		=> Front ULTRASONIC
			PD0 = US Output [digital, output]
			PD1 = US Input		~~Need to get time-span of high level when signal returns
		=> Right ULTRASONIC
			PD2 = US Output [digital, output]
			PD3 = US Input
		=> Left ULTRASONIC
			PD6 = US Output [digital, output]
			PD7	= US Input
			
*/
void 		PORTD_Init		(void){		// NEED UPDATED FOR PORTD
volatile unsigned long delay;
SYSCTL_RCGCGPIO_R |= 0x10;     // 1) D clock
delay = SYSCTL_RCGCGPIO_R;     // delay   
GPIO_PORTD_DIR_R &= ~(PIN_1 | PIN_3 | PIN_7);	// 5) Input PD1, 3, 7
GPIO_PORTD_DIR_R |=  (PIN_0 | PIN_2 | PIN_6);	// 5) Output PD0, 2, 6
GPIO_PORTD_DEN_R |= (PIN_0 | PIN_1 | PIN_2 | PIN_3 | PIN_6 | PIN_7);  // 7) enable digital pins PD1 - 3, 6, 7
}

void 		PORTF_Init		(void){ 
//--------------------------------------UNLOCK PORTF BIT 0----------------------------------------//
	SYSCTL_RCGCGPIO_R |= (1<<5);		// Set bit5 of RCGCGPIO to enable PORTF clock page 340
// PORTF bit 0 has special function, need to unlock to modify
	GPIO_PORTF_LOCK_R = 0x4C4F434B;	// unlock commit register page 684
	GPIO_PORTF_CR_R = 0x0E;					// make PORTF bits configurable
//---------------------------------------CONFIGURE PORTF------------------------------------------//
// Initialize PF3,PF2,PF1 as a digital output, PF0 and PF4 as digital input pins
	GPIO_PORTF_DIR_R |= (PIN_1 | PIN_2 | PIN_3 );		// Set PF3 as digital output for green LED Page 664
																				//  and PF1 as digital output for red LED, and PF2 for blue LED
	GPIO_PORTF_DEN_R |= (PIN_1 | PIN_2 | PIN_3);	// make bits 3,2,1 digital pins page 684
}

void 		PLL_INIT			(void){		
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
+ (SYSDIV2<<22);      // configure for XX MHz clock determined by sysdiv
// 5) wait for the PLL to lock by polling PLLLRIS
while((SYSCTL_RIS_R&0x00000040)==0){};  // wait for PLLRIS bit
// 6) enable use of PLL by clearing BYPASS
SYSCTL_RCC2_R &= ~0x00000800;
}

void 		SYSTICK_INIT(void){
// 1 Disable SYSTICK during set up
NVIC_ST_CTRL_R = 0;
// 2 MAX reload value
NVIC_ST_RELOAD_R = 0x00FFFFFF;
// 3 Clear CURRENT by simply writing to it (any write to it clears it)
NVIC_ST_CURRENT_R = 0;
// 4 Enable SYSTICK timer with core clock
NVIC_ST_CTRL_R = 0x00000005;
}


void 		SYSTICK_DELAY_MICRO	(unsigned long usec){
unsigned long i;																						
for (i=0; i<usec; i++){																	//wanted delay given as msec
volatile unsigned long elapsedTime;										// Define an elapsed time for Each loop, since we want elapsed time to be = (1/1000) * frequency
unsigned long startTime = NVIC_ST_CURRENT_R;					// Copy the current value, since NVIC_ST_CURRENT_R decrements with every bus cycle and instruction
do{
elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;		// Measures the difference between start and what it currently is, followed immediately by comparing to desired time difference
																		// elapsed time is always set, then updated to be a larger value, then updated, etc.
}while(elapsedTime <= (THOUSANDTH_CLK_FREQ/1000));							// Each loop is 1/Frequency, so doing it as many times as the frequency would yield 1 s. So doing it by 1/1000 of the frequency yields 1ms
}
}
void 		SYSTICK_DELAY_CLOCK_CYCLE(unsigned long delay){
  volatile unsigned long elapsedTime;
  unsigned long startTime = NVIC_ST_CURRENT_R;
  do{
    elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }
  while(elapsedTime <= delay);
}
unsigned int Find_Range_PortA (unsigned long IN_PIN, unsigned long OUT_PIN) {
	SYSTICK_DELAY(150);							// Need 100ms between calling this function, so start function with it just to be safe
	average = 0;										// Reset average
				
	for(i=0;i<3;i++){									// Three samples, gets average to have better data.
		echo_time = 0;									// Reset echo
		GPIO_PORTA_DATA_R |= OUT_PIN;								// Set trigger high
		SYSTICK_DELAY_MICRO(10);							// 10 µs delay using systick
		GPIO_PORTA_DATA_R &= ~OUT_PIN;								// Set trigger low
		
		while((GPIO_PORTA_DATA_R&(IN_PIN))==0);				// Search for high transition
		while((GPIO_PORTA_DATA_R&(IN_PIN))==(IN_PIN)){			// Search for low transition
			SYSTICK_DELAY_CLOCK_CYCLE(3);
			echo_time++;								// Count echo_time
		}
		average += echo_time;							// Add the echo_time to the average
	}
	average /= 3;										// After three samples take the average
	LED = 0x02;				// RED LED FLAG			
	// ****************************** b. Calculate Range(cm) **********************************
	return (average*0.01175);
}
unsigned int Find_Range_PortD (unsigned long IN_PIN, unsigned long OUT_PIN) {
	SYSTICK_DELAY(150);							// Need 100ms between calling this function, so start function with it just to be safe
	average = 0;										// Reset average
				
	for(i=0;i<3;i++){									// Three samples, gets average to have better data.
		echo_time = 0;									// Reset echo
		GPIO_PORTD_DATA_R |= OUT_PIN;								// Set trigger high
		SYSTICK_DELAY_MICRO(10);							// 10 µs delay using systick
		GPIO_PORTD_DATA_R &= ~OUT_PIN;								// Set trigger low
		
		while((GPIO_PORTD_DATA_R&(IN_PIN))==0);				// Search for high transition
		while((GPIO_PORTD_DATA_R&(IN_PIN))==(IN_PIN)){			// Search for low transition
			SYSTICK_DELAY_CLOCK_CYCLE(3);
			echo_time++;								// Count echo_time
		}
		average += echo_time;							// Add the echo_time to the average
	}
	average /= 3;										// After three samples take the average
	LED = 0x02;				// RED LED FLAG			
	// ****************************** b. Calculate Range(cm) **********************************
	return (average*0.01175);
}




//=====================================================================================//
/*===================|  3. Main Function                     |========================*/

int main(void){
/*------		3__VARIABLES INIT			------*/
unsigned long flag = 0;
/*------		3__FUNCTION INIT			------*/
PORTA_Init();
PORTF_Init();
//PORTB_Init();
//PWM0A_Init(50000,5000);		// NOTE: PERIOD FOR THESE TWO FUNCTIONS MUST BE EQUAL! 50,000!
PORTC_Init();
//PORTD_Init();
SYSTICK_INIT();	
PORTB_Init();	
PWM1A_Init(PERIOD,1);		// Period is 50,000. Duty is 25,000. Therefore, the duty cycle is 50%. Decreasing duty => Decrease in %
PLL_INIT();
/*------		3__STATUS INIT				------*/
// delay for placing bot and moving away
GPIO_PORTF_DATA_R |= 0x04;
SYSTICK_DELAY(5000);
Move_Forward();
/*------		3__RUNNING					------*/
	while(1){
			if(flag == 0){
				GPIO_PORTF_DATA_R |= 0x08;
				//Move_Set_Speed(18000);
			//	SYSTICK_DELAY(2*1861);			// have to recaclulate for carpet of 3rd floor
						// 1 second at 50% is 21.15 inches = 537.21 mm, so 1.861 seconds should be 1 meter (1000 mm)
						// for 50%, speed is 1m/1.646
						
	/*
	Want in 3__VARIABLE INIT:
	double speed;
	Want in 3__FUNCTION INIT :
	WTimer0ACounter_Init
	
	Using WTimer0A and Timer0:
	
	Move_Forward();						// Direction first
	Move_Set_Speed(18000);		// Speed
	SYSTICK_DELAY(20);				// Some small amount of time to let the motor get up to speed
	
	speed = ((speed_get) / (75 * 12)) * 	Circumference		
	// speed_get returns # of counts of hall-sensor for 1 second. 
	// Divide this by 12 to get 1 full rotation per second, then
	// 75 to get the speed for 1 second of the outer gear
	// This gets you rotations per second, multiply by circumference to get velocity in mm/s
	
	time = (unsigned long) (distance / speed)			// typecast this
	// if time > 2^16 - 1, then you need to change the THOUSANDTH_CLK_FREQ to a different valu
	Timer0_Init_Specific(time,THOUSANDTH_CLK_FREQ);
	
	// obstacle avoidance loop here, using condition Timer0_Flag
	// poll ultrasonic, get distance, do checks and comparisons
	// use break; when the flag is tripped
	// and IF an interrupt is caused by the front IR, make sure to REDO the ultrasonic distances
	
	// Also, I'm thinking of it in terms of X,Z coordinated
	// Ex: C to D
	// When the bot detects an obstacle, it has to move left or right
	// this should ADD or SUBTRACT from the total X distance
	// It is then able to move forward/backward again. The Distance to go has to be reset based on how far it is into the journey already
	// OR we somehow PAUSE Timer0
	
	// POINT A >> B
		Move_Forward();
		Move_Set_Speed(18000);
		setup_Move_Distance ( 1945.11 );
		Obstacle_Avoidance
	
	
	*/
	
				
				
	/*
			// POINT A >> B
				Move_Forward();
				Move_Distance(1945.11);
				Move_Turn_Right_90();
			// POINT B >> C
				Move_Set_Speed(18000);
				Move_Forward();
				Move_Distance(1336.84);
				Move_Turn_Left_90();
	*/		
	/*
			// POINT C >> D
				Move_Forward();
				Move_Set_Speed(18000);
				//Move_Distance(10694.74 * 0.5);				// Extreme overshoot? 
				
				
				Move_Turn_Left_90_MAIN();
		*/
		/*
			// test of going 2000 mm, corner turn, 2 feet
				Move_Forward();					// must assign direction first. Direction+no speed = no movement, no updated direction + speed = movement
				Move_Set_Speed(18000);	// 18000 of 50000 is relatively slow
				Move_Distance(2000);		// Aiming for 2 meters EXACT, will adjust this value. (2000)
																// For now, just a small distance
				Move_Turn_Left_90_MAIN();		// was having some issues with turn left, seemed like it moved more

				Move_Forward();
				Move_Set_Speed(18000);
				Move_Distance(200);			// Aiming for 2 feet EXACT, will adjust this value (610)
																// For now, just a small distance
		*/		
	/*
			// POINT D >> E
				Move_Set_Speed(18000);
				Move_Forward();
				Move_Distance(16549.47);
				Move_Turn_Left_90();
				
	*/
		
	// So the bot does the front interrupt poorly
	// It will activate, stop movement, but inertia keeps it
	// moving forward and into the material
	// which can bend the IR sensor
	// and then the front detection doesn't work
	// so it keeps going forward.
	
	// So Using the ultra-sonics seems necessary for
	// front object avoidance / avoiding a bump
	
	// Which means setting up the Hall-sensor for interrpt
	// And measuring speed
	
			// POINT E >> F
				Move_Set_Speed(18000);
				Move_Forward();
				Move_Distance((9892.63*0.5)); // works well
				Move_Turn_Left_90_MAIN();
			// POINT F >> B
				Move_Set_Speed(18000);
				Move_Forward();
				Move_Distance(15240*0.5); // runs short
				Move_Turn_Right_90(); // note : does 180, should be 90 deg to right
		
	/*
			// POINT B >> A
				Move_Set_Speed(18000);
				Move_Forward();
				Move_Distance(1945.11);
	*/
			
			flag++;
			}
			GPIO_PORTF_DATA_R = 0x02;
			Move_Stop();


}

}
