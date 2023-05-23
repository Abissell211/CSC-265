#include "matrix.h"

using namespace std;

int main() {
	int l = 0;						// integers for array storing
	Matrix mat1, mat2, mat3;		// Matrices
	int arr1[2][2], arr2[2][2];		// Arrays for storing
	ifstream file;					// Input file
	file.open ("input.txt");		// File to be used
	while(l != 4){					// Loop for program to compute until a Quit option(4) is given
	file >> l;						// get first line for menu option
	for(int j = 0; j < 2; j++)		// Outside loop for storing operation
		for(int k = 0; k < 2; k++)	// Inside loop for storing operation
		{ 
			file >> arr1[j][k];		// Gets line to store in array1
			mat1.setMatrix(arr1);	// Sets array1 elements to elements in matrix1
		}
	for(int j = 0; j < 2; j++)		// Outside loop for storing operation
		for(int k = 0; k < 2; k++)	// Inside loop for stroing operation
		{ 
			file >> arr2[j][k];		// Gets line to store in array2
			mat2.setMatrix(arr2);	// Sets array2 elements to elements in matrix2
		}
		
	switch (l) 
		{
			case 1 :				// Compares l to menu options (addition)
				cout << "Menu option 1: Addition.\n" << endl;
				mat3 = mat1 + mat2;		// Adds matrices
				cout << mat3 << endl;	// Displays the result (in matrix form)
				system("pause");
				break;					// breaks out of switch statement
			case 2 :				// Compares l to menu options (Subtract)
				cout << "Menu option 2: Subtraction.\n" << endl;
				mat3 = mat1 - mat2;		// Subtracts matrices
				cout << mat3 << endl;	// Displays the result (in matrix form)
				system("pause");
				break;					// breaks out of switch statement
			case 3 :				// Compares l to menu options (Multiply)
				cout << "Menu option 3: Multiplication.\n" << endl;
				mat3 = mat1 * mat2;		// Multiplies matrices 
				cout << mat3 << endl;	// Displays the result (in matrix form)
				system("pause");
				break;					// breaks out of switch statement
			case 4 :				// Else (quit)
				cout << "Menu option 4: Quit.\n" << endl;
				cout << "Quit!" << endl; // Displays Quit
				break;					 // breaks out of switch statement
		}
	}
	file.close();						 // Closes the file
	return 0;							 // returns 0 if good operations
}
