c234567
c Function Example
      REAL FUNCTION addthem(a,b)
      IMPLICIT NONE
      REAL,INTENT(IN)::a,b
      addthem=a+b
      RETURN
      END FUNCTION
      
      PROGRAM addit
      IMPLICIT NONE
      REAL addthem
      print'(f10.2)',addthem(5.2,9.2)
      END PROGRAM