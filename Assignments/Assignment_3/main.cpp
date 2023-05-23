#include "student.h"

using namespace std;

/*	
*************************NUMCHECK********************* 
General:		Converts a string to an int
Preconditions:	must pass string with numeric characters
Postconditions:	will output an integer value for future processing
*/

int numcheck(string Id); 											//function prototype for numcheck

/*==============================
		 Main()
===============================*/

int main() 
{ Student S[SIZE]; 													// Declares S of class Student, creates array for all students to be stored
  string FName = ""; 												// First name...holds 15 characters
  bool tFName = true;												// sets initial flag to true
  string LName = ""; 												// Last name...holds 15 characters
  bool tLName = true;												// sets initial flag to true
  string Address = ""; 												// Address...holds 20 characters
  bool tAddress = true;												// sets initial flag to true
  string Id = ""; 													// ID...holds 4 characters
  bool tId = true;													// sets initial flag to true
  string CredComp = ""; 											// Credits completed...holds 3 characters
  bool tCredComp = true;											// sets initial flag to true
  string QualPts = ""; 												// Quality Points...holds 3 characters
  bool tQualPts = true;												// sets initial flag to true
  float Gpa = 0.0; 													// Declare float GPA
  bool tGpa = true;													// sets initial flag to true
  ifstream InpFile; 												// Input stream class to operate input file
  int i = 0;														// accumulator variable for setting student array

  InpFile.open("input.txt"); 										// Opens Input File
  assert(!InpFile.fail()); 											// Asserts if file cannot be opened
  
  while (!InpFile.eof()) 											// While the file isn't at the end of file
  	{ 																// First Name read and checked.
	  getline(InpFile, FName); 										// Gets first line and sets it to string First Name
  		if(FName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) // if...FName isn't of type alphabetical
 			tFName = false;											//if FName is not correct values, sets tFName flag to bool false
		if(FName.length() > 15 || FName.length() <= 0) 				// if...FName isn't of correct length
 			tFName = false;											//if FName is not correct length, sets tFName flag to bool false
		  	  
	  getline(InpFile, LName); 										// Gets second line and sets it to string Last Name
	  	if(LName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) // if...FName isn't of type alphabetical
 			tLName = false;											//if LName is not alpha, sets tLName flag to bool false 
		if(LName.length() > 15 || LName.length() <= 0)				// if...LName isn't of correct length
 			tLName = false;											// if LName is not correct Length, sets tLName flag to bool false
		  	  
  	  getline(InpFile, Address); 									// Gets third line and sets it to char string Address
  	  	if(Address.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .") != string::npos) // if...Address isn't of type alphanumerical
 			tAddress = false; 										//if Address is not alpha or numeric, sets tAddress flag to bool false
 		if(Address.length() > 20 || Address.length() <= 0) 			// if...Address isn't of correct length
 			tAddress = false;										//if Address is not correct length, sets tAddress flag to bool false

	  getline(InpFile, Id); 										// Gets fourth line and sets it to char string ID
	  	if(Id.find_first_not_of("0123456789") != string::npos) 		// if...Id isn't of type numerical
 			tId = false;											// if Id is not numeric, sets tId flag to bool false
      	if(numcheck(Id) > 9999 || numcheck(Id) < 0)  				// if...Id isn't of correct length/value
 			tId = false;											// if Id is not correct numberic value, sets tId flag to bool false
		  	   
      getline(InpFile, CredComp); 									// Gets fifth line and sets it to string credits completed
	  	if(CredComp.find_first_not_of("0123456789") != string::npos) // if...CredComp isn't of type numerical
 			tCredComp = false;										// if CredComp is not numeric, sets tCredComp flag to bool false
		if(numcheck(CredComp) > 199 || numcheck(CredComp) < 0) 		// if...CredComp isn't of correct length/value
 			tCredComp = false;										// if CredComp is not correct value range, sets tCredComp flag to bool false
			    
      getline(InpFile, QualPts); 									// Gets sixth line and sets it to char string Quality Points
	  	if(QualPts.find_first_not_of("0123456789") != string::npos) // if...QualPts isn't of type numerical
 			tQualPts = false;										// if QualPts is not numeric sets tQualPts flag to bool false
		if(numcheck(QualPts) > 796 || numcheck(QualPts) < 0) 		// if...QualPts isn't of correct length/value	      
 			tQualPts = false;										// if Qualpts is not correct value, sets tQual flag to false

	  if(tFName == true) 											// if flag remains true
  	  		S[i].SetFName(FName); 									// Sets student class S's FName to FName
  	  		
  	  if(tLName == true)											// if flag remains true
  	  		S[i].SetLName(LName); 									// Sets student class S's LName to LName
  	  		
  	  if(tId == true)												// if flag remains true
  	  		S[i].SetId(Id); 										// Sets Id to student class S's Id
  	  		
  	  if(tCredComp == true)											// if flag remains true
  	  		S[i].SetCredComp(CredComp); 							// Sets CredComp to student class S's CredComp
  	  		
  	  if(tQualPts == true)											// if flag remains true
  	  		S[i].SetQualPts(QualPts); 								// Sets QualPts to student class S's Qualpts
  	  
	  if(tQualPts == true && tCredComp == true)						// if flags are both true
  	  		S[i].SetGpa(); 											// Sets Gpa to student class S's Gpa
  			
	  if(S[i].GetGpa() > 4.0 || S[i].GetGpa() < 0.0) 				// if...Gpa isn't within correct values
  	  		tGpa = false;											// sets tGpa flag to Bool False
  	  		
	  if(tFName == true && tLName == true && tId == true && tCredComp == true && tQualPts == true && tGpa == true) 	//if... all flags are true
      		S[i].Display(); 										// Displays student (1, 2, 3...)
      		
      if(tFName == false || tLName == false || tId == false || tCredComp == false || tQualPts == false || tGpa == false) // if... any flag is returned as false from bad input data
      		cout << "Error in processing " << LName << ", " << FName << endl;											// displays an error message for the appropriate student
      	
      cout << endl; 												// Prints a single line
      i++;															// accumulator is used for array setting
      
      tFName = true, tLName = true, tId = true, tCredComp = true, tQualPts = true, tGpa = true;							// resets all flags to true for the next loop
  	}
  InpFile.close(); 													// Closes file
  assert(!InpFile.fail()); 											// Fails if file cannot be closed
  return 0; 														// Returns 0 if no errors in processing
}

/*==============================
		Function numcheck()
===============================*/
int numcheck(string Id) 											// function numcheck with parameter string
    { int c = atoi(Id.c_str()); 									// converts string to integer
      return c;  													// returns integer value c
    } 																// end function...numcheck
