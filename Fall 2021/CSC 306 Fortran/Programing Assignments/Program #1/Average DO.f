c234567
      PROGRAM Average
      IMPLICIT NONE
      CHARACTER*30 NAME
      INTEGER n, i
      REAL Current, Sum, Ave
5     FORMAT(' ',A,X,F6.2)
      write(*,*)'Enter the name of the student: '
      read(*,*) NAME
      write(*,*)'Enter number of grades to average: '
      read(*,*) n
      DO i=1,n
         write(*,*)'Enter grade: '
         read(*,*) Current
         Sum = Sum + Current
      END DO 
      Ave = Sum/n
      write(*,*) NAME,"'s total and Average"
      write(*,5) 'Average:',Ave,'Sum:',Sum
      END