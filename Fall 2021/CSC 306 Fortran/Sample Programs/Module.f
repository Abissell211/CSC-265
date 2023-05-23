c234567
      MODULE my_subs
      IMPLICIT NONE
c     (declare shared data here)
      CONTAINS
      SUBROUTINE sub1 (a,b,c,x,error)
      IMPLICIT NONE
      REAL,DIMENSION(3),INTENT(IN)::a
      REAL,INTENT(IN)::b,c
      REAL,INTENT(OUT)::x
      LOGICAL,INTENT(OUT)::error
c     ...
      END SUBROUTINE sub1
      END MODULE my_subs