c234567
c Movie Ticket Problem Program
c CASE logic solution
      PROGRAM TICKET
      IMPLICIT NONE
      INTEGER AGE
      REAL PRICE
5     FORMAT (' ','The ticket price is $',f5.2)
      PRINT *,'ENTER AGE OF INDIVIDUAL'
      READ(*,*)AGE
      SELECT CASE(AGE)
         CASE(:12)
            PRICE = 2.0
         CASE(13:59)
            PRICE = 10.0
         CASE(60:)
            PRICE = 5.0
         END SELECT
      PRINT 5,PRICE
      END       