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
10    FORMAT(' ',A,X,F10.2,X,A,X,F10.2)
15    FORMAT(' ',A)
c This program reads a real number r and prints c the area of a circle with radius r.
c PROMPT (defaulted)
      write(*,15) 'Enter the radius of a circle, r:'
c INPUT (defaulted)
      read (*,5) r
c CALCULATION
      area = pi * r ** 2
c OUTPUT
      write (*,10) 'Radius = ',r,'Area = ',area
c Notice, the strings "Radius =" and "Area =" were printed through the A specifier in the Format statement.
c Spaces are inserted with the X specifier.
      end