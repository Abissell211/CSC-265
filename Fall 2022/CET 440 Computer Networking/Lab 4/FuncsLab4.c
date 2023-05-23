/*
 *  Client: Data Share Program
 *
 *  	10-Oct-22 : 
 *		Andrew Bissell
 *		Joshua Hughes
 *		Noah Proctor
 *
 *		Contains the functions used in the lab4.c
 */
 
#include "Lab4.h"

Students_Averages(struct students *z){
	
	int i = 0, j = 0;							// Loop Variables
	int SumAge = 0;								// Varaibles to compute the average age/gpa and to store the values
	float SumGpa = 0.0f, AveGpa = 0.0f, AveAge = 0.0f;
	int year_day_accessed;	int current_day;
	int diff_time;

	// Loop through strudents to get sum of age and gpa	
	for(i=0;i<NumStudents;i++){					
		SumGpa += z->students[i].gpa;
		SumAge += z->students[i].age;
	}
	
	// Average Calcs
	AveGpa = SumGpa/NumStudents;				
	AveAge = SumAge/NumStudents;				
	
	// Data output
	printf("Average Student GPA: %.2f \n", AveGpa);
	printf("Average Student Age: %.2f \n", AveAge);
	printf("Active Users: \n");

	time(&current);
	current_time = localtime(&current);
	current_day = (short int)current_time->tm_yday;

	// Loop through students to get active users
	for(i=0;i<NumStudents;i++){					
		if(z->students[i].status == ACTIVE){
			printf("\t\t %s", z->students[i].name);			
		}
	}

	for(i=0;i<NumStudents;i++){
		copy_time = z->students[i].lastLoginTime;
		convert_time = localtime(&copy_time);
		year_day_accessed = convert_time->tm_yday;
		diff_time = current_day - year_day_accessed;
		//printf("\n Current YD %d",current_day);
		//printf("\n Login YD %d",year_day_accessed);
		switch(diff_time){
			case 0:
				login_statistics[0] += 1;
				break;
			case 1:
				login_statistics[1] += 1;
				break;
			case 2:
				login_statistics[2] += 1;
				break;
			default:
				break;
		}
	

	}
	printf("\nToday there were %d logins, Yesterday had %d logins, Two days ago had %d logins",login_statistics[0],login_statistics[1],login_statistics[2]);
}

Show_Struct_Info (struct students *z){
int i;
for(i=0;i<NumStudents;i++){
	printf("\n");
	printf("%f",z->students[i].gpa);
}
printf("\n");


}
