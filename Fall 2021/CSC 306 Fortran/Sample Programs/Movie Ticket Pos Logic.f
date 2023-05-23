c234567
c Movie Ticket Problem Program
c Positive logic solution
      PROGRAM TICKET
      IMPLICIT NONE
      INTEGER AGE
      REAL PRICE
5     FORMAT (' ','The ticket price is $',f5.2)
      PRINT *,'ENTER AGE OF INDIVIDUAL'
      READ(*,*)AGE
      IF(AGE.GE.60)THEN
         PRICE = 5.0
      ELSE
         IF(AGE.GT.12)THEN
            PRICE = 10.0
         ELSE
            PRICE = 20
         END IF
      END IF
      PRINT 5, PRICE
      END