include "all_different.mzn";

% This parameter set defines the range of the numbers
set of int: DIGIT = 1..9;

% We define one variable per letter of the anagram
var DIGIT: X11;
var DIGIT: X12;
var DIGIT: X13;
var DIGIT: X21;
var DIGIT: X22;
var DIGIT: X23;
var DIGIT: X31;
var DIGIT: X32;
var DIGIT: X33;

% We put all the variables into an array for using the all_different global constraint
array[1..9] of var int: Allnums = [X11,X12,X13,X21,X22,X23,X31,X32,X33];

% Constraints for rows, columns, and diagonals being equal to 15 
constraint   X11 + X12 + X13 = 15;
constraint   X11 + X22 + X33 = 15;
constraint   X11 + X21 + X31 = 15;
constraint   X12 + X22 + X32 = 15;
constraint   X13 + X23 + X33 = 15;
constraint   X13 + X22 + X31 = 15;
constraint   X21 + X22 + X23 = 15;
constraint   X31 + X32 + X33 = 15;
 
% Constraint that all variables are different between them
constraint all_different(Allnums);

solve satisfy;