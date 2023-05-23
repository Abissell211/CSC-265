/*
 *  DC.c - example C program to create a digital clock with name of the day, name of the month and full date
 *
 *	Digital Clock Program:
 *  	08-Sep-22 : Andrew D. Bissell
 *
 *	qt.c, alarm.c, alarm2.c used to aid in program completion
 *
 *  System main pages time(2) and localtime(3C) used to aid in program completion
 *
 *  Refresher on char data type using https://www.tutorialspoint.com/cprogramming/c_data_types.htm
 *  Refresher on char to string using https://www.tutorialspoint.com/cprogramming/c_strings.htm
 *
 *  NOTES: - When used in the Dev C++ compiler the system("clear"); needs commented out and the (\n)'s in the
 *		     printf's need to be changed to \r. When used in unix on draco1 there where issues with it not displaying
 *			 the time at all. So system("clear"); with (\n)'s in the printf where used to fix the issue.
 *		   - Clock is accurate and the checks will change over the string in the char[] data types correctly in both
 *			 the Dev C++ compiler and the unix Draco1 compiler.
 */
#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#define SIZE 20			// Size for our arrays
int main()
{
	int dayofweek, month, day, year;
	int hour, minute, second;
	
    char dayweek[SIZE] = {0};	// Char array to display the actual day of the week
	char wmonth[SIZE] = {0};	// Char array to display the actual month
	
    time_t sec;
    struct tm* c_time;
 
    sec = time(NULL);			// time in seconds
    c_time = localtime(&sec);	// to get current time
    
    // get all the specific data needed from the current time and store it in a seperate variable
	dayofweek 	= c_time->tm_wday;		// 0 - 6
	month 		= c_time->tm_mon;		// 0 - 11
	day 		= c_time->tm_mday;		// 0 - 31
	year 		= c_time->tm_year+1900;	// since this is a count of how many years since 1900 we have to add the count to 1900
    hour 		= c_time->tm_hour;		// 0 - 23
	minute 		= c_time->tm_min;		// 0 - 59
	second 		= c_time->tm_sec;		// 0 -59
	
	// Send data to function for the pre-printf statement
	ChkWeekMonth(dayofweek, month, dayweek, wmonth);

    printf("\nToday is %s - %s %02d, %d. Current Time is %02d:%02d:%02d", dayweek, // day of the week
	wmonth, day, year,		// actual month day, then year
	hour, minute, second);	// Hour:Minute:Second
 
	// Loop to count and reset the clocks hours, minutes, and seconds
    while(1)
    {
        second++;
 
        //update hour, minute and second
        if(second == 60){
            minute += 1;
            second = 0;
        }
        if(minute == 60){
            hour += 1;
            minute = 0;
        }
        if(hour == 24){
        	dayofweek += 1;
        	day += 1;
            hour = 0;
            minute = 0;
            second = 0;
            memset(dayweek, 0 ,SIZE);
            ChkWeekMonth(dayofweek, month, dayweek, wmonth);	// change the char array for new day of week
        }
        // update day of the week, day of the month and month
        if(dayofweek == 7)
        	dayofweek = 0;
        if(day == 32){
        	month += 1;
        	day = 0;
        	memset(wmonth, 0 ,SIZE);
        	ChkWeekMonth(dayofweek, month, dayweek, wmonth);	// change the char array for new month
		}
		if(month == 12){
			year += 1;
			month = 0;
		}
		
		system("clear");			//clear output screen
		
	    printf("\nToday is %s - %s %02d, %d. Current Time is %02d:%02d:%02d", dayweek, // day of the week
		wmonth, day, year,		// actual month day, then year
		hour, minute, second);	// Hour:Minute:Second
         
        sleep(1);   //wait till 1 second
    }
    return 0;
}

int ChkWeekMonth(int week, int month, char Aweek[], char Amonth[]){
	// Checks to change the day of the week
    if(week == 0)
    	strcat(Aweek, "Sunday");
    if(week == 1)
    	strcat(Aweek, "Monday");
    if(week == 2)
    	strcat(Aweek, "Tuesday");
    if(week == 3)
    	strcat(Aweek, "Wednesday");
    if(week == 4)
    	strcat(Aweek, "Thursday");
    if(week == 5)
    	strcat(Aweek, "Friday");
    if(week == 6)
    	strcat(Aweek, "Saturday");
    
    // Checks to change the Month
    if(month == 0)
    	strcat(Amonth, "January");
    if(month == 1)
    	strcat(Amonth, "February");
    if(month == 2)
    	strcat(Amonth, "March");
    if(month == 3)
    	strcat(Amonth, "April");
    if(month == 4)
    	strcat(Amonth, "May");
    if(month == 5)
    	strcat(Amonth, "June");
    if(month == 6)
    	strcat(Amonth, "July");
    if(month == 7)
    	strcat(Amonth, "August");
    if(month == 8)
    	strcat(Amonth, "September");
    if(month == 9)
    	strcat(Amonth, "October");
    if(month == 10)
    	strcat(Amonth, "November");
    if(month == 11)
    	strcat(Amonth, "December");
    	
    return 0;
}
