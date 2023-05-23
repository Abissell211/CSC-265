C     ANDREW SPATE, ANDREW BISSELL
C     GROUP 2 
C     FORTRAN 306
C     SIMULTANEOUS EQUATIONS
!------------------------------------------------------------------------
!************************************************************************
      MODULE SIMULTANEOUS_EQ
 ! Data dictionary: declare constants
      REAL, PARAMETER :: EPSILON = 1.0E-6 ! A "small" number for comparison
 ! when determining singular eqns
 ! Data dictionary: declare local variable types & definitions
      REAL :: FACTOR ! Factor to multiply eqn irow by
 ! before adding to eqn jrow
      INTEGER :: IROW ! Number of the equation currently
 ! being processed
      INTEGER :: IPEAK ! Pointer to equation containing
 ! maximum pivot value
      INTEGER :: JROW ! Number of the equation compared
 ! to the current equation
      INTEGER :: KCOL ! Index over all columns of eqn
      REAL :: TEMP ! Scratch value     
      CONTAINS 
      
!------------------------------------------------------------------------ 
C SOLVER SUBROUTINE
C BY 
C GENERAL: 
C PRECONDITIONS: 
C POSTCONDITIONS: 
C WRITTEN 10/29
!------------------------------------------------------------------------       
      SUBROUTINE SOLVER(A, B, NDIM, N, ERROR)
      INTEGER, INTENT (IN) ::NDIM
      REAL, INTENT(OUT), DIMENSION (NDIM,NDIM)::A
      REAL, INTENT(OUT), DIMENSION(NDIM)::B
      INTEGER, INTENT(IN)::N
      INTEGER, INTENT(OUT)::ERROR
 ! Process n times to get all equations...
      CALL PRINTARRAY(A, NDIM, NDIM)
      WRITE(*,*)"INIT"
C     FIND PIVOT   

      DO IROW = 1, N
 ! Find peak pivot for column irow in rows irow to n
      IPEAK=IROW
      
      DO JROW=IROW+1,N
      IF (ABS(A(JROW,IROW)) > ABS(A(IPEAK,IROW))) THEN
      IPEAK=JROW
      END IF
      END DO !MAX PIVOT
      
      WRITE(*,*)"IPEAK",IPEAK
 ! Check for singular equations. 
      IF ( ABS(A(IPEAK,IROW))<EPSILON) THEN
      ERROR = 1
      RETURN
      END IF !singular
 ! Otherwise, if ipeak /= irow, swap equations irow & ipeak
      IF ( IPEAK .LE. IROW ) THEN
      WRITE(*,*)"IPEAK < IROW"
      DO KCOL=1,N
      TEMP= A(IPEAK,KCOL)
      A(IPEAK,KCOL) = A(IROW, KCOL)
      A(IROW,KCOL) = TEMP
      END DO
      TEMP = B(IPEAK)
      B(IPEAK)=B(IROW)
      B(IROW)=TEMP
      END IF 
      WRITE(*,*)"LINE60"
      CALL PRINTARRAY(A, NDIM,NDIM)      
 ! Multiply equation irow by -a(jrow,irow)/a(irow,irow), 
 ! and add it to Eqn jrow (for all eqns except irow itself).
      DO JROW=1,N
      IF (JROW .LE. IROW ) THEN
      FACTOR= -A(JROW, IROW)/A(IROW,IROW)
      WRITE(*,*)FACTOR
      WRITE(*,*)"LINE71"
      CALL PRINTARRAY(A, NDIM, NDIM)
      DO KCOL=1,N
      A(JROW,KCOL)=A(IROW,KCOL)*FACTOR + A(JROW,KCOL)  !1*-1 +1
      END DO
      B(JROW)= B(IROW)*FACTOR+B(JROW)
      END IF
      CALL PRINTARRAY(A, NDIM, NDIM)
      WRITE(*,*)"HI"
      END DO !eliminate
      CALL PRINTARRAY(A, NDIM, NDIM)
      WRITE(*,*)"LOOP"
      END DO !mainloop            
 ! End of main loop over all equations. All off-diagonal
 ! terms are now zero. To get the final answer, we must
 ! divide each equation by the coefficient of its on-diagonal
 ! term.
      DO IROW=1,N
      B(IROW)=B(IROW)/A(IROW,IROW)
      A(IROW,IROW)=1
      END DO !divide
 ! Set error flag to 0 and return.
      ERROR = 0
      END SUBROUTINE
!------------------------------------------------------------------------ 
C INPUT SUBROUTINE
C BY 
C GENERAL: 
C PRECONDITIONS: 
C POSTCONDITIONS: 
C WRITTEN 10/29
!------------------------------------------------------------------------                  
      SUBROUTINE INPUT (A, B, NDIM, N)
      
      REAL, INTENT(OUT),DIMENSION(10,10)::A
      REAL, INTENT(OUT),DIMENSION(10)::B
      INTEGER, INTENT(OUT) :: NDIM
      INTEGER, INTENT(OUT) :: N
      INTEGER :: I
      INTEGER :: J
      
15    FORMAT(' ',A12,I3)
      
      WRITE(*,*)"HOW MANY EQUATIONS AND COEFFICIENTS ARE WE SOLVING TODA
     +Y?(1-10)"
      READ(*,*)N
      NDIM = N + 1
      DO I=1, N
      WRITE(*,15)"EQUATION #",I
      DO J=1, NDIM
      IF(J .NE. NDIM)THEN
      WRITE(*,15)"COEFFICIENT ",J
      READ(*,*)A(I,J)
      ELSE
      WRITE(*,15)"SOLUTION TO",J
      READ(*,*)A(I,J)   
      END IF 
      END DO
      END DO
          
      END SUBROUTINE
     
      END MODULE
!************************************************************************     
 !------------------------------------------------------------------------ 
C PRINTARRAY SUBROUTINE
C BY ANDREW SPATE
C GENERAL: WRITE MATRIX TO SPECIFIED OUTPUT
C PRECONDITIONS: UNIT DESTINATION FOR WRITE STATEMENT, AND MATRIX TO WRITE, ROWS AND COLUMNS TO PRINT
C POSTCONDITIONS: NONE
C WRITTEN 9/27
C REVISED 9/27- PUT MATRIX INTO GENERIC FORM VS SPECIFIC
!------------------------------------------------------------------------      
      SUBROUTINE PRINTARRAY(GENERICassMATRIX, ROWS, COLUMNS)
      INTEGER, INTENT(IN)::ROWS, COLUMNS
      REAL,INTENT(IN),DIMENSION(10,10)::GENERICassMATRIX
      INTEGER I,J
70    FORMAT(' ',10(F6.2,2X))
      WRITE(*,*)"ROWS (EQUATIONS) =",ROWS
      WRITE(*,*)"COLUMNS (COEF + 1 SOL) =", COLUMNS   
      DO I=1,ROWS
      WRITE(*,70)(GENERICassMATRIX(I,J),J=1,COLUMNS)
      END DO
      END SUBROUTINE PRINTARRAY
!------------------------------------------------------------------------ 
C MAIN
C COMPLEX EQUATION SOLVER
C BY ANDREW SPATE, ANDREW BISSELL, KELLI HUFF
C GROUP #2
C GENERAL: HOUSES THE MAIN PROGRAM
C PRECONDITIONS: 
C    SUBROUTINES PRESENT IN SIMULTANEOUS EQUATIONS MODULE:
C		
C POSTCONDITIONS: 
C WRITTEN 10/28/2021 - 
!------------------------------------------------------------------------              
      PROGRAM G2P6
      USE SIMULTANEOUS_EQ
      IMPLICIT NONE
      
      REAL, DIMENSION(25,25)::A
      REAL, DIMENSION(25)::B
      INTEGER :: NDIM
      INTEGER :: N
      INTEGER :: ERROR
      INTEGER :: I
      
      ERROR=0
      
      CALL INPUT(A, B, NDIM, N)
      CALL PRINTARRAY(A, N, NDIM)
      
!      CALL SOLVER(A, B, NDIM, N, ERROR )
!      WRITE(*,*)(B(I),I=1,NDIM)
      
      END PROGRAM