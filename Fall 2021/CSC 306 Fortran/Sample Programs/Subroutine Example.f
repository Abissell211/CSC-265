c234567
c Write a program to read up to 10 integers between -100 and 100
c  inclusive from the keyboard and store them into an array.
c Print the array.
c Sort the array in ascending order.
c Print the sorted array.
c Write subroutines for the read, print, and sort modules.

      PROGRAM sortdata
      IMPLICIT NONE
      INTEGER, PARAMETER::size=10
      INTEGER X(size),N
      CALL readit(X,N,size)
      CALL printit(X,N,size)
      CALL sortit (X,N,size)
      print *,'Sorted data:'
      CALL printit (X,N,size)
      END PROGRAM sortdata
      
      SUBROUTINE readit(X,N,size)
      IMPLICIT NONE
      INTEGER,INTENT(IN)::size
      INTEGER,INTENT(out)::X(size)
      INTEGER,INTENT(out)::N
      INTEGER I,D
      i=1
      print *,'Enter a value betweeen -100 and 100'
      read(*,*)d
      DO WHILE(d .GE. -100 .AND. d .LE. 100 .AND. i .LE. size)
         X(i)=d
         i=i+1
         IF(i .LE. size)THEN
            print *,'Enter a value between -100 and 100'
            read(*,*)d
         ENDIF
      ENDDO
      n=i-1
      END SUBROUTINE readit
      
      SUBROUTINE printit(X,N,size)
      IMPLICIT NONE
      INTEGER,INTENT(IN)::size
      INTEGER,INTENT(out)::X(size)
      INTEGER,INTENT(in)::N
      INTEGER I
      DO i=1,n
         print*,X(i)
      ENDDO
      END SUBROUTINE printit
      
      SUBROUTINE sortit(X,N,size)
      IMPLICIT NONE
      INTEGER,INTENT(IN)::size
      INTEGER,INTENT(out)::X(size)
      INTEGER,INTENT(in)::N
      INTEGER I,E,T
      LOGICAL more
      more=.TRUE.
      E=n-1
      DO WHILE(more)
         more=.FALSE.
         DO i=1,E
            IF(X(i) .GT. X(i+1)) THEN
               more=.TRUE.
               T=X(i)
               X(i)=X(i+1)
               X(i+1)=T
            ENDIF
         ENDDO
         e=e-1
      ENDDO
      END SUBROUTINE sortit