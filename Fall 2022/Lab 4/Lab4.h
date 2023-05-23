/*
 *  Client: Data Share Program
 *
 *  	10-Oct-22 : 
 *		Andrew Bissell
 *		Joshua Hughes
 *		Noah Proctor
 *
 *		Contains the struct used in Lab4.c and FuncsLab4.c and all the prototypes for
 *			the functions found in FuncsLab4.c
 */

#ifndef LAB4_H
#define LAB4_H
#include <time.h>

#define ACTIVE 1			// User is ACTIVE
#define INACTIVE 0			// User is INACTIVE
#define NumStudents 27		// Number of students


typedef struct  {

    char userID[10];		// User ID, the PennWest Email ID   
    char name[50];			// Name of the User, in "FirstName LastName" format
    int age;				// Random Age, interval [18,22]   
    float gpa;			    // Random GPA, interval [2.5,4]
    int status;			    // Active Status, boolean value, ACTIVE/INACTIVE   
    time_t lastLoginTime;   // Last Time Logged into Server
    int totalActiveTime;   	// Total Time spent Active on Server

}student;

struct students {
    student students[NumStudents];
};

int login_statistics[3];
struct tm *convert_time;
time_t copy_time;
time_t current;
struct tm *current_time;

Students_Averages(struct students *z);

#endif

