#include "matrix.h"

using namespace std;

/*==============================
		Matrix Constructor
===============================*/
Matrix::Matrix()
{ 
	int mat[2][2] = {0};				// Initalizes the Private array mat[2][2] array slots to zero
}

/*==============================
		Matrix setMatrix()
===============================*/
void Matrix::setMatrix(int arr[2][2])
{
	for(int j = 0; j < 2; j++)			// Loop for first demension of an array
		for (int k = 0; k < 2; k++)		// Loop for second demension of an array
			mat[j][k] = arr[j][k];		// Sets the input array's (int arr[2][2]) values to the private array (int mat[2][2])
}


/*==============================
		Matrix getMatrix()
===============================*/
int Matrix::getMatrix() const
{
	int i, h, k = 0;
	for(i = 0; i < 2; i++)				// Loop for first demension of an array
		for (h = 0; h < 2; h++)			// Loop for second demension of an array
		{  
			cout << mat[i][h] << " ";	// Displays the value of the array slot depending on the step of each array demension
			k++;						// increases count variable k by 1
			if (k=2)					
				cout << endl;
		}
}

/*==============================
		Matrix display()
===============================*/
void Matrix::display() const
{
	for ( int i = 0; i < 2; i++) 		// Loop for first demension of an array
		for (int j = 0; j < 2; j++)		// Loop for second demension of an array
		{
			cout << mat[i][j] << " ";	// Displays the value of the array slot depending on the step of each array demension
		}
		cout << endl;
}

/*==============================
		Matrix Operators
===============================*/
ostream& operator<< (ostream& outp, Matrix& x)
{
	outp << x.mat[0][0] << " " << x.mat[0][1] << endl;	// Sets up the output of the first line of a matrix		ex:	cout << mat1 << endl;    1 2
	outp << x.mat[1][0] << " " << x.mat[1][1] << endl;	// sets up the output of the second line of a matrix 								 3 4
	
	return outp;
}

istream& operator>> (istream& inp, Matrix& x)
{
	string temp;					// temp string for the getline.
	int num1;						// int value to transfer the string to.
	getline(inp, temp);				// Gets the next line and assigns it to the temp variable
	num1 = atoi(temp.c_str());		// Changes the temp variable string to int and sets it to num1
	
	return inp;
}

Matrix operator+ (const Matrix& x, const Matrix& y)
{
	Matrix addAnswer;											 // stores the sum of Matrices
	
	for (int i = 0; i < 2; i++)									// Loop for first demension of an array
		for (int j = 0; j < 2; j++)								// Loop for second demension of an array
			addAnswer.mat[i][j] = x.mat[i][j] + y.mat[i][j];	// Adds the two same array slot locations and sets it to the same array slot location of addAnswer
	return addAnswer;											// Returns the final calculated array
}

Matrix operator- (const Matrix& x, const Matrix& y)
{
	Matrix subAnswer;											// stores the subtraction of Matrices
	
	for(int i = 0; i < 2; i++)									// Loop for first demension of an array
		for(int j = 0; j < 2; j++)								// Loop for second demension of an array
			subAnswer.mat[i][j] = x.mat[i][j] - y.mat[i][j];	// Subtracts the two same array slot locations and sets it to the same array slot location of addAnswer
	
	return subAnswer;											// Returns the final calculated array
}

Matrix operator* (const Matrix& x, const Matrix& y)
{
	Matrix multAnswer;													// stores the multiplication of Matrices
	
	for(int i = 0; i < 2; i++)											// Loop for first demension of an array
		for(int j = 0; j < 2; j++)										// Loop for second demension of an array
		{
			multAnswer.mat[i][j] = 0;									// Sets all slots in multAnswer equal to zero
			for(int k = 0; k < 2; k++)									// Loop for setting the correct multiplication slots
			{
				multAnswer.mat[i][j] += x.mat[i][k] * (y.mat[k][j]);	// Multiplies the correct values, adds them together and sets to the corrosponding array slot
			}
		}
	return multAnswer;													// Returns the final calculated array
}
