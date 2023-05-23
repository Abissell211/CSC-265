c234567
c String Compare Program
      PROGRAM Array
      IMPLICIT NONE
      INTEGER, parameter::max_size=20
      CHARACTER(len=max_size)A,B
      PRINT *,"Enter string 1"
      READ(*,*)A
      PRINT *,"Enter string 2"
      READ(*,*)B
      IF(A .EQ. B)THEN
         PRINT *,A," = ",B
      ENDIF
      IF(A .LT. B)THEN
         PRINT *,A," < ",B
      ENDIF
      IF(A .GT. B)THEN
         PRINT *,A," > ",B
      ENDIF
      END