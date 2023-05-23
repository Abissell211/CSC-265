c234567
c FORTRAN Program 1
c Grade Averaging Program
c Andrew Bissell, Andrew Spate, Justin Gunderson
c Group #2

      PROGRAM Average
      IMPLICIT NONE
c     Variable for number of grades(n) and loop count(Count).
      INTEGER n,Count
c     Variables to calculate current grade(Current), sum(Sum), average(Ave), divisor for average(c).
      REAL Current,Sum,Ave,c
c     Variable for the name of the student.
      CHARACTER*20 Student
c     FORMATs for all write statements.
5     FORMAT(' ',A)
10    FORMAT(' ',A,I2,A)
15    FORMAT(' ','Gradebook for:',A20)
20    FORMAT(' ',2(A,F6.2,X))
c     FORMATs for all read statements.
2     FORMAT(A20)
4     FORMAT(I2)
6     FORMAT(F6.2)
c     Prompt for student name.
      write(*,5) 'Enter the name of the student:'
      read (*,2) Student 
c     Prompt for number of grades.
      write(*,5) 'Enter the number of grades:'
      read (*,4) n
c     Set count to 1 and divisor to the number of grades.
      Count=1
      c=n
c     Loop to enter grades based on what user entered for variable n.
      DO(n.GT.0)
c        Prompt for grade.
         write(*,10) 'Enter grade #',Count,':'
         read (*,*) Current
c        Add current grade to the sum.
         Sum = Sum + Current
c        Step count and decrement n for loop.
         Count=Count+1         
         n=n-1
c     End of loop for grade entering.
      END DO
c     Calculation to get average(Ave). 
      Ave = Sum/c
c     End Statement that displays the student, average, and sum.
      write(*,15) Student
      write(*,20) 'Average:',Ave,'Sum:',Sum
      END