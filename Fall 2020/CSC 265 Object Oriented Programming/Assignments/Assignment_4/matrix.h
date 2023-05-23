// CLASS PROVIDED:  Matrix
//
// CONSTRUCTOR for the Matrix class:
//   Matrix()
//     Description: Constructor for the class Matrix.
//     Preconditions: Private data type initialization: int mat[2][2].
//     Postcondition: Sets the private data area values to zero.
//
// MODIFICATION MEMBER FUNCTIONS for the Matrix class:
//   void setMatrix (int mat[2][2])
//     Description: Takes input array(int arr[][]) and applies each array slot equal to the corresponding slot for int mat[2][2]
//     Precondition: int mat[2][2] must be initialized.
//     Postcondition: int mat[2][2] is equal to the input array(int arr[][])
//
// CONSTANT MEMBER FUNCTIONS for the Matrix class
//   int getMatrix() const
//     Description: Returns the array of the private data int mat[2][2]
//     Preconditions: int mat[2][2] must be initialized.
//     Postcondition: Returns the value of int mat[2][2]
//
//   void Display() const
//     Description: Displays a Matrix to the user.
//     Preconditions: Private variables must be initialized and preferably hold values to use/test.
//     Postcondition: Displays each array slot one after the other (not in a matrix layout) 
//
// OVERLOADED OPERATOR FUNCTIONS for the Matrix class
//   friend ostream& operator<< (ostream& outp, Matrix& x)
//     Description: Overloads the << operator for a Matrix
//     Preconditions: Class Matrix must be complete
//     Postcondition: Displays the values of a Matrix in a matrix format (ex: [2][2] = 1 2 /n 3 4 )
//
//   friend istream& operator>> (istream& inp, Matrix& x)
//     Description: Overloads the >> operator for a Matrix
//     Preconditions: Must have file available to work, not an input from user in the .exe
//     Postcondition: Takes data from a file and changes from a string to int for calculations.
//
//   friend Matrix operator+ (const Matrix&, const Matrix&)
//     Description: Overloads the + operator for a Matrix
//     Preconditions: Class Matrix must be complete
//     Postcondition: Adds the values from one matrix to another and sets it to a final matrix.
//
//   friend Matrix operator- (const Matrix&, const Matrix&)
//     Description: Overloads the - operator for a Matrix
//     Preconditions: Class Matrix must be complete
//     Postcondition: Subtracts the values from one matrix to another and sets it to a final matrix.
//
//   friend Matrix operator* (const Matrix&, const Matrix&)
//     Description: Overloads the * operator for a Matrix
//     Preconditions: Class Matrix must be complete
//     Postcondition: Multiplies the values from one matrix to another and sets it to a final matrix.
//

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

class Matrix
{
	public:
		Matrix();
		void setMatrix(int mat[2][2]);
		int getMatrix() const;
		void display() const;
		friend ostream& operator<< (ostream& outp, Matrix& x);
		friend istream& operator>> (istream& inp, Matrix& x);
		friend Matrix operator+ (const Matrix&, const Matrix&);
		friend Matrix operator- (const Matrix&, const Matrix&);
		friend Matrix operator* (const Matrix&, const Matrix&);
	private:
		int mat[2][2];
};
#endif
