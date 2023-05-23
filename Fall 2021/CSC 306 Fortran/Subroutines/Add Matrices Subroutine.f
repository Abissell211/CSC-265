c234567
      PROGRAM Array_Sum
      IMPLICIT NONE
      INTEGER r,c,i,j
      REAL, DIMENSION(3,4)::TEMPMATRIX(3,4)=RESHAPE([1.0,2.6,3.6,2.0,4.
     +6,4.8,3.5,2.5,2.5,4.0,9.5,5.6],[3,4])
      REAL, DIMENSION(3,4)::SUM(3,4)=RESHAPE([2.6,3.6,1.0,4.6,4.8,2.
     +0,2.5,2.5,3.5,9.5,5.6,4.0],[3,4])
10    FORMAT(' ',F7.2)
      r=3
      c=4
      CALL Matrix_Addition (TEMPMATRIX,SUM,r,c)
      WRITE(*,*)'ArraySum'
      DO i=1,r
         DO j=1,c
            WRITE(*,10)SUM(i,j)
         ENDDO
      ENDDO
      END
            
                              
      SUBROUTINE Matrix_Addition(TEMPMATRIX,SUM,r,c)
      INTEGER, INTENT(IN)::r,c
      REAL, INTENT(IN)::TEMPMATRIX(3,4)
      REAL, INTENT(OUT)::SUM(3,4)
      INTEGER i,j
      DO i=1,r
         DO j=1,c
            SUM(i,j)=SUM(i,j)+TEMPMATRIX(i,j)
         ENDDO
      ENDDO
      END SUBROUTINE Matrix_Addition
      