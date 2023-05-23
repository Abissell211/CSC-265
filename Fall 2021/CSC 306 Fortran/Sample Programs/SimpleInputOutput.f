c234567
      program circle
c implicit none tells the compiler I need to specify the data declarations
      implicit none
c DATA (using the Real Data Type)      
      real r, area, pi
c Assigning pi variable as a constant
      parameter (pi=3.14159)
c FORMATTING
5     FORMAT(F13.2)
10    FORMAT(' ','Radius = ',F10.2,' Area = ',F10.2)
15    FORMAT(' ',A)
c This program reads a real number r and prints c the area of a circle with radius r.
c PROMPT (defaulted)
      write(*,15) 'Enter the radius of a circle, r:'
c INPUT (defaulted)
      read (*,5) r
c CALCULATION
      area = pi * r ** 2
c OUTPUT
      write (*,10) r,area
c The output format of A accepted a string of any size.
c The input format statements litterly look at the column positions that are specified.
c This input took the number from column 1 through 13.
c The output format printed a string, then used 10 spaces for the number with two decimal digits,
c then printed a string, finally printed a real number in the next 10 spaces. 
      end