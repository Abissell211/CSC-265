// CLASS PROVIDED:  Person
//
// CONSTRUCTOR for the Person class:
//   Fraction()
//     Description: Constructor for the class Person.
//     Preconditions: Private data types intialization: FName, LName, and Address.
//     Postcondition: Applies a default value for each private data above (ERROR).
//
// MODIFICATION MEMBER FUNCTIONS for the Person class:
//   void setFName (string N)
//     Description: Checks if N data is correct and sets variable N to private variable FName. 
//     Precondition: FName must be initialized.
//     Postcondition: If data passes the if check FName will equal user inputed data through variable N.
//
//   void setLName(string LN)
//     Description: Checks if LN data is correct and sets variable LN to private variable LName. 
//     Precondition: LName must be initialized.
//     Postcondition: If data passes the if check LName will equal user inputed data through variable LN.
//
//   void setAddress(string Add)
//     Description: Checks if Add data is correct and sets variable Add to private variable Address.
//     Precondition: Address must be intialized.
//     Postcondition: If data passes the if check Address will equal user inputed data through variable Address.
//
// CONSTANT MEMBER FUNCTIONS for the Person class
//   string GetFName() const
//     Description: Returns the value of the private variable FName.
//     Preconditions: FName must be initalized.
//     Postcondition: Returns the value of FName.
//
//   string GetLName() const
//     Description: Returns the value of the private variable LName.
//     Preconditions: LName must be intialized.
//     Postcondition: Returns the value of LName.
//
//   string GetPerson() const
//     Description: Sets up a string person.
//     Preconditions: LName and FName must be initalized.
//     Postcondition: Creates a layout of "LName, FName" into one string and returns the value. 
//
//   void Display() const
//     Description: Displays a person to the user.
//     Preconditions: Private variables must be initialized and preferably hold values to use/test.
//     Postcondition: Displays a person's FName, LName, Address. 
//
//
// CLASS PROVIDED:  Student (Using Class Person)
//
// CONSTRUCTOR for the Student class:
//   Fraction()
//     Description: Constructor for the class Student.
//     Preconditions: Private data types intialization: Id, Gpa, CredComp, QualPts.
//     Postcondition: Applies a default value for each private data above (max number of characters for program read).
//
// MODIFICATION MEMBER FUNCTIONS for the Student class:
//   void setId (string ID)
//     Description: Converts the string ID to temp int value checks for good data then applies to private variable Id.  
//     Precondition: Id must be initialized and string must be passed to convert to temp variable c.
//     Postcondition: String ID is converted to temp variable c and if the data check is true the c is applied to private varible Id.
// 
//   void setCredComp (string Cred)
//     Description: Converts the string Cred to temp int value checks for good data then applies to private variable CredComp.  
//     Precondition: CredComp must be initialized and string must be passed to convert to temp variable c.
//     Postcondition: String Cred is converted to temp variable c and if the data check is true the c is applied to private varible CredComp. 
//
//   void setQualPts (string QPts)
//     Description: Converts the string QPts to temp int value checks for good data then applies to private variable QualPts.  
//     Precondition: QualPts must be initialized and string must be passed to convert to temp variable c.
//     Postcondition: String QPts is converted to temp variable c and if the data check is true the c is applied to private varible QualPts. 
//
//   void setGpa ()
//     Description: Calculates the Gpa of a student from the private variables QualPts and CredComp. 
//     Precondition: QualPts and CredComp must be initalized and hold values to compute. 
//     Postcondition: Using QualPts and CredComp converted to float to create value for varible Gpa. 
//
// CONSTANT MEMBER FUNCTIONS for the Student class
//   int GetId() const
//     Description: Returns the value of the private variable Id.
//     Preconditions: Id must be initalized.
//     Postcondition: Returns the value of Id.
//
//   int GetCredComp() const
//     Description: Returns the value of the private variable CredComp.
//     Preconditions: CredComp must be intialized.
//     Postcondition: Returns the value of CredComp.
//
//   int GetQualPts() const
//     Description: Returns the value of the private variable QualPts.
//     Preconditions: QualPts must be intialized.
//     Postcondition: Returns the value of QualPts.
//
//   float GetGpa() const
//     Description: Returns the value of the private variable Gpa.
//     Preconditions: Gpa must be intialized.
//     Postcondition: Returns the value of Gpa.
//
//   string GetStudent() const
//     Description: Sets up a string student.
//     Preconditions: Functions GetLName and GetFName must be created.
//     Postcondition: Creates a layout of "LName, FName" into one string and returns the value.
//
//   void Display() const
//     Description: Displays a student to the user.
//     Preconditions: Private variables must be initialized and preferably hold values to use/test.
//     Postcondition: Displays a student's ID, student(LName, FName), GPA.

#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <cstdlib>
#include <iomanip>
#include <sstream>

#ifndef PERSON_H
#define PERSON_H
#include <string>

using namespace std;

const int SIZE = 20;

/*==============================
		Class Person
===============================*/

class Person
{ public:
	Person();
	void Display() const;
	string GetPerson() const;
	string GetFName() const;
	string GetLName() const;
	void SetFName(string N);
	void SetLName(string LN);
	void SetAddress(string Add);
	
  private:
  	string FName;
  	string LName;
  	string Address;
};

/*==============================
		Class Student
===============================*/

class Student: public Person
{ public:
	Student();
	void Display() const;
	string GetStudent() const;
	void SetId(string ID);
	void SetCredComp(string Cred);
	void SetQualPts(string QPts);
	void SetGpa();
	int GetId() const;
	int GetCredComp() const;
	int GetQualPts() const;
	float GetGpa() const;
	
  private:
	int Id;
	float Gpa;
	int CredComp;
	int QualPts;
	Person S[SIZE];
};


#endif
