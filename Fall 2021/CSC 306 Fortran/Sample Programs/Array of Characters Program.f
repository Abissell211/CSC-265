c234567
c Array of Characters Program
      PROGRAM ARRAY
      IMPLICIT NONE
      INTEGER, parameter::max_siz=30
      INTEGER, parameter::max_length=20
      CHARACTER, DIMENSION(max_size)::C
      CHARACTER(len=max_length)S
      INTEGER i,l
10    FORMAT(A)
      PRINT*,"Enter string:"
      READ(*,10)S
      l=len_trim(S)
      DO i=1,l
         C(i)=S(i:i)
      ENDDO
      PRINT*,C
      DO i=1,l
         PRINT*,"Character ",i," is ",C(i)
      ENDDO
      END