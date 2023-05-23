c234567
c String Array Program
      PROGRAM ARRAY
      IMPLICIT NONE
      INTEGER, parameter::max_size=5
      INTEGER, parameter::max_length=30
      CHARACTER(len=max_length)SArray(max_size),C
      INTEGER i,n
10    FORMAT(A)
      i=1
      PRINT *,"Enter string:"
      READ(*,10)C
      DOWHILE(len_trim(C) .GT. 0 .AND. i .LE. max_size)
         SArray(i)=C
         i=i+1
         IF(i .LE. max_size)THEN
            PRINT*,"Enter string:"
            READ(*,10)C
         ENDIF
      ENDDO
      n=i-1
      DO i=1,n
         PRINT*,"String ",i," is ",SArray(i)
      ENDDO
      END