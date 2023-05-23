include "all_different.mzn";

int: base;

% This parameter set defines the range of the letters
set of int: DIGIT = 0..base-1;
% instead of putting in a constraint we can just alter the range to not allow zeros
set of int: DIGIT1 = 1..base-1; 

% We define one variable per letter of the anagram
var DIGIT1: S;
var DIGIT: E;
var DIGIT: N;
var DIGIT: D;
var DIGIT1: M;
var DIGIT: O;
var DIGIT: R;
var DIGIT: Y;

% We put all the letters of the anagram into an array for using the all_different global constraint
array[1..8] of var int: letters = [S,E,N,D,M,O,R,Y];

% Constraints of the sum SEND+MORE=MONEY
constraint   base^3*S + base^2*E + base*N + D
           + base^3*M + base^2*O + base*R + E
 = base^4*M + base^3*O + base^2*N + base*E + Y;
 
% Constraint that all variables are different between them
constraint all_different(letters);

solve minimize S+E+N+D;

output["S:", show(S)," E:", show(E)," S:", show(N)," S:", show(D),
  " M:", show(M)," O:", show(O)," R:", show(R)," Y:", show(Y),
  "\n\n",
  "    \(S)\(E)\(N)\(D)\n",
  " +  \(M)\(O)\(R)\(E)\n",
  " = \(M)\(O)\(N)\(E)\(Y)\n"
  ];