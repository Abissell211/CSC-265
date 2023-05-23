c234567
c Accessing Characters From a String
      String(start,end)
      PROGRAM ARRAY
      IMPLICIT NONE
      INTEGER, parameter::max_length=30
      CHARACTER(len_max_length)C
      INTEGER i,l
10    FORMAT(A)
      PRINT*,"Enter string:"
      READ(*,10)C
      l=len_trim(C)
      PRINT*,C
      DO i=1,l
         PRINT*,"Character ",i," is ",C(i:i)
      ENDDO
      END