#include "student.h"
//CONSTRUCTOR

/*==============================
		Person Constructor
===============================*/

Person::Person() 		
{	FName = "ERROR";
	LName = "ERROR";
	Address = "ERROR";
}

//MODIFICATION MEMBER FUNCTIONS

/*==============================
		Person SetFName()
===============================*/

void Person::SetFName(string N)
{ int space = N.find(" ", 0);
 	if(N.length() <= 15 && N.length() > 0 && space == -1) // checks for length of the First name, as well as if there is a space within the string
		FName = N;										// if first name is good data, it is assigned
	else
		FName = "ERROR"; 								// if not, suppliments error as the name
}

/*==============================
		Person SetLName()
===============================*/

void Person::SetLName(string LN)
{ int space = LN.find(" ", 0);
	if(LN.length() <= 15 && LN.length() > 0 && space == -1)  //checks for length of the last name, as well as if there is a space within the string
		LName = LN;										//if Last name is good data, it is assigned
	else
		LName = "ERROR"; 								//if not, suppliments error as the name
}	

/*==============================
		Person SetAddress()
===============================*/

void Person::SetAddress(string Add)
{ if(Add.length() <= 20 && Add.length() > 0) 			//checks for length of the Address
	Address = Add;										// if sufficient, it adds the address to the private data
}

//CONSTANT MEMBER FUNCTIONS

/*==============================
		Person GetFName()
===============================*/

string Person::GetFName() const
{ return FName;											//returns the First name string
}

/*==============================
		Person GetLName()
===============================*/

string Person::GetLName() const
{ return LName;											//returns the last name string
}

/*==============================
		Person GetPerson()
===============================*/

string Person::GetPerson() const
{ 
	string person = LName + ", " + FName;				//creates the string with the person's first name and last name for future cout's
 	return person;
}

//CONSTRUCTOR

/*==============================
		Student Constructor
===============================*/

Student::Student()										//creates student class with filler data
{ 	Id = 0;	
	Gpa = 5.0;
	CredComp = 0;
	QualPts = 0;
}

//MODIFICATION MEMBER FUNCTIONS

/*==============================
		Student SetId()
===============================*/

void Student::SetId(string ID)
{ int c = atoi(ID.c_str());								//checks the int value of the string after converting it
	if(c <= 9999 && c >= 0)
	Id = c;												//if good data, it stores the ID in private member variables
}

/*==============================
		Student SetCredComp()
===============================*/

void Student::SetCredComp(string Cred)
{ int c = atoi(Cred.c_str());							//creates int to process to verify the credits completed number
	if(c <= 199 && c >= 0)								//checks the int to see if the values are within range
	CredComp = c;	
}


/*==============================
		Student SetQualPts()
===============================*/

void Student::SetQualPts(string QPts)
{ int c = atoi(QPts.c_str());							//creates int to procees for verification with quality points
	if(c <= 796 && c >= 0)								//checks the int versus data parameters in assignement
	QualPts = c;	
}

/*==============================
		Student SetGpa()
===============================*/

void Student::SetGpa()
{ float GPA;
 	GPA = static_cast<float> (QualPts)/CredComp;		//takes 2 ints, converts one to a float, then does division for GPA calculation
 	if(GPA <= 4.0 && GPA >= 0.0)
		Gpa = GPA;
}

//CONSTANT MEMBER FUNCTIONS

/*==============================
		Student GetId()
===============================*/

int Student::GetId() const								//returns int value for Id
{
	return Id;
}

/*==============================
		Student GetCredComp()
===============================*/

int Student::GetCredComp() const						//returns int value for CredComp
{
	return CredComp;
}

/*==============================
		Student GetQualPts()
===============================*/

int Student::GetQualPts() const							//returns int value for QualPts
{
	return QualPts;
}

/*==============================
		Student GetGpa()
===============================*/

float Student::GetGpa() const							//returns float value for GPA
{
	return Gpa;
}

/*==============================
		Student GetStudent()
===============================*/

string Student::GetStudent() const
{ 
  string student = GetLName() + ", " + GetFName(); 		// creates single sting for person's name, will be used in final display
  return student;
}

/*==============================
		Person Display()
===============================*/

void Person::Display() const
{ cout << left << setw(7) << "Name:  " << setw(34) << GetPerson() << "Address: " << Address << endl; //left justifies all data, sets various width parameters, and prints all data out based on assignment
}

/*==============================
		Student Display()
===============================*/

void Student::Display() const
{
	cout << left << "Student ID: " << setw(7) << Id << "Name: " << setw(34) << GetStudent() << " GPA: " << fixed << setprecision(1) << Gpa << endl;
}
