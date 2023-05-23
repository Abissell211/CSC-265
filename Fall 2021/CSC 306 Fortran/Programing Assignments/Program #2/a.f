c234567
      PROGRAM Average
      IMPLICIT NONE
      CHARACTER*30 NAME
      INTEGER n, i
      REAL Sum, Ave, c
      REAL, DIMENSION(10)::a
5     FORMAT(' ',A,X,F7.2)
10    FORMAT(' ',A,I2)
15    FORMAT(' ',F6.2)
2     FORMAT(' ',A13,I2,A1,X)
      n=1
      i=1
      write(*,*)'Enter the name of the student: '
      read(*,*) NAME
      DO WHILE (i .LE. 10)
         write(*,2)'Enter grade #',n,': '
         read(*,*) c
         IF ((c .GE. 0).AND.(c .LE. 100)) THEN
            a(n)=c
            i=i+1
            n=n+1
         ELSE
            i=11
         END IF
      END DO
      DO i=1,n-1
         Sum=Sum+a(i)
      END DO
      Ave=Sum/(n-1)
      write(*,*)TRIM(NAME),"'s total and Average"
      write(*,5) 'Average:',Ave,'Sum:',Sum
      write(*,10)'Number of grades entered:',n-1
      DO i=1,n-1
         write(*,15)a(i)
      END DO
      END