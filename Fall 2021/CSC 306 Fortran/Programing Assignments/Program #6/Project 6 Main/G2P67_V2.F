C     SIMULTANEOUS EQUATIONS
C     ANDREW SPATE, ANDREW BISSELL, KELLI HUFF
C     GROUP 2 
C     FORTRAN 306
!------------------------------------------------------------------------
!************************************************************************
      MODULE SIMULTANEOUS_EQ
      IMPLICIT NONE
 ! Data dictionary: declare constants
      REAL, PARAMETER :: EPSILON = 1.0E-6 ! A "small" number for comparison
 ! when determining singular eqns
 ! Data dictionary: declare local variable types & definitions
      COMPLEX :: FACTOR ! Factor to multiply eqn irow by
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
C BY ANDREW SPATE, ANDREW BISSELL, KELLI HUFF
C GENERAL: TAKES TWO ARRAYS ONE TWO DIMENSION AND ONE SINGLE DIMENSION ARRAY AND USES THE 
C           DATA IN EACH TO SOLVE MULTIPLE EQUATIONS USING THE GAUSS JORDAN ELIMINATION
C PRECONDITIONS: INPUT SUBROUTINE MUST BE RAN BEFORE OR NO DATA WILL BE LOADED
C POSTCONDITIONS: CALCULATIONS WILL BE DONE IN BOTH ARRAYS WHICH WILL ALTER THE DATA, AND
C                  THE SOLUTIONS TO THE EQUATIONS WILL BE IN ARRAY B
C WRITTEN 10/29/2021
C REVISED 11/01/2021
!------------------------------------------------------------------------       
      SUBROUTINE SOLVER(A, B, N, ERROR)
      INTEGER, INTENT (IN) ::N
      COMPLEX, INTENT(OUT), DIMENSION (10,10)::A
      COMPLEX, INTENT(OUT), DIMENSION(10)::B
      INTEGER, INTENT(OUT)::ERROR
!--------------------------Process n times to get all equations---------------------------
      DO IROW = 1, N
!---------------------------------------FIND PIVOT----------------------------------------
!--------------------Find peak pivot for column irow in rows irow to n--------------------
      IPEAK=IROW
      DO JROW=IROW+1,N
      IF (CABS(A(JROW,IROW)) > CABS(A(IPEAK,IROW))) THEN
      IPEAK=JROW
      END IF
      END DO !MAX PIVOT
      
!------------------------------Check for singular equations-------------------------------
      IF (CABS(A(IPEAK,IROW)) < EPSILON) THEN
      ERROR = 1
      RETURN
      END IF !singular
      
!----------Otherwise, if ipeak does not equal irow, swap equations irow & ipeak-----------
      IF ( IPEAK .NE. IROW ) THEN
      DO KCOL=1,N
      TEMP = A(IPEAK,KCOL)
      A(IPEAK,KCOL) = A(IROW, KCOL)
      A(IROW,KCOL) = TEMP
      END DO
      TEMP = B(IPEAK)
      B(IPEAK) = B(IROW)
      B(IROW) = TEMP
      END IF 
            
!----------------Multiply equation irow by -a(jrow,irow)/a(irow,irow),-------------------- 
!--------------and add it to Eqn jrow (for all eqns except irow itself).------------------
      DO JROW=1,N
      IF (JROW .NE. IROW ) THEN
      FACTOR= -A(JROW, IROW)/A(IROW,IROW)
      DO KCOL=1,N
      A(JROW,KCOL)=A(IROW,KCOL)*FACTOR + A(JROW,KCOL)  !1*-1 +1
      END DO
      B(JROW)= B(IROW)*FACTOR+B(JROW)
      END IF
      END DO !eliminate
      END DO !mainloop
           
!-----------------End of main loop over all equations. All off-diagonal-------------------
!-----------------terms are now zero. To get the final answer, we must--------------------
!------------divide each equation by the coefficient of its on-diagonal term--------------
      DO IROW=1,N
      B(IROW)=B(IROW)/A(IROW,IROW)
      A(IROW,IROW)=1
      END DO
      
!--------------------------Set error flag to 0 and return---------------------------------
      ERROR = 0
      END SUBROUTINE
      
!------------------------------------------------------------------------ 
C INPUT SUBROUTINE
C BY ANDREW SPATE, ANDREW BISSELL, KELLI HUFF
C GENERAL: TAKES USER INPUT FOR NUMBER OF EQUATIONS AND THE DATA FOR EACH EQUATION
C PRECONDITIONS: NONE
C POSTCONDITIONS: LOADS THE USER INPUTTED EQUATION DATA INTO ARRAY A, AND LOADS THE 
C                  USER INPUTTED SOULTIONS TO THE EQUATIONS INTO ARRAY B
C WRITTEN 10/29/2021
C REVISED 11/01/2021
!------------------------------------------------------------------------       
      SUBROUTINE INPUT (A, B, N)
      
      COMPLEX, INTENT(OUT),DIMENSION(10,10)::A
      COMPLEX, INTENT(OUT),DIMENSION(10)::B
      INTEGER, INTENT(OUT) :: N
      INTEGER :: I, J, ERROR
      LOGICAL :: OUTBOUNDS
      OUTBOUNDS = .TRUE.
!------------------------MAIN LOOP FOR USER DECISION---------------------   
      DO WHILE(OUTBOUNDS)
      WRITE(*,*)"HOW MANY EQUATIONS ARE WE SOLVING TODAY?(1-10)"
      READ(*,*)N
!-------------------------------CHECK FOR N------------------------------      
      IF((N .LE. 10) .AND. (N .GE. 0))THEN
      WRITE(*,*)"FOR ALL INPUTS, USE (XXXX,XXXX) NOTATION, MAX FOUR DIGI
     +T ONE DECIMAL AND TWO DECIMAL PLACES"
!---------------------LOOP FOR INPUTING COMPLEX NUMBER-------------------     
      DO I=1, N
15    FORMAT(' ',A12,I3)
      WRITE(*,15)"EQUATION #",I
      DO J=1, N
      WRITE(*,15)"COEFFICIENT ",J
      READ(*,*,IOSTAT=ERROR)A(I,J)
!---------------------CHECK FOR DATA ERROR COEFFICIENT-------------------      
      IF(ERROR .NE. 0)THEN
      WRITE(*,*)"ERROR: INCORRECT DATA ENTRY, VALUE DEFAULTED"
      A(I,J) = (0,0)
      ERROR = 0
      END IF      
      END DO  ! COEFFICIENT END
      WRITE(*,15)"SOLUTION TO EQ",I
      READ(*,*,IOSTAT=ERROR)B(I)
!-----------------------CHECK FOR DATA ERROR SOLUTION--------------------
      IF(ERROR .NE. 0)THEN
      WRITE(*,*)"ERROR: INCORRECT DATA ENTRY, VALUE DEFAULTED"
      B(I) = (0,0)
      ERROR = 0
      END IF
      END DO  !EQUATION END
!-------------------END LOOP FOR INPUTINT COMPLEX NUMBERS----------------
      OUTBOUNDS = .False.
      ELSE
      WRITE(*,*)"ERROR: OUT OF BOUNDS PLEASE ENTER EQUATIONS BETWEEN 1 -
     + 10"
      END IF
      END DO
!------------------------------END MAIN LOOP-----------------------------         
      END SUBROUTINE
           
      END MODULE
!************************************************************************     
!------------------------------------------------------------------------ 
C PRINTCOEF SUBROUTINE
C BY ANDREW SPATE, ANDREW BISSELL, KELLI HUFF
C GENERAL: WRITE MATRIX TO SPECIFIED OUTPUT
C PRECONDITIONS: UNIT DESTINATION FOR WRITE STATEMENT, AND MATRIX TO WRITE, ROWS AND COLUMNS TO PRINT
C POSTCONDITIONS: NONE
C WRITTEN 09/27/2021
C REVISED 11/05/2021
!------------------------------------------------------------------------      
      SUBROUTINE PRINTCOEF(GaM, GaM2, R)
      INTEGER, INTENT(IN)::R
      COMPLEX,INTENT(IN),DIMENSION(10,10)::GaM
      COMPLEX,INTENT(IN),DIMENSION(10)::GaM2
      INTEGER I,J,K

70    FORMAT(' ','(',F6.2,'+ i',F6.2,")X",I2,'+')
71    FORMAT(' ','(',F6.2,'+ i',F6.2,")X",I2)
75    FORMAT(' ',10(A,I2,A,F6.2,A,F6.2,A))
      
      DO I=1,R
      DO J = 1, R
      
	  IF (J .NE. R) THEN
      WRITE(*, 70, ADVANCE='NO') GaM(I, J), J
      ELSE
      
	  IF (J .EQ. 10) THEN
      WRITE(*, 70, ADVANCE='no') GaM(i, j), J
      PRINT '(/)'
      ELSE
      WRITE(*, 71, ADVANCE='NO') GaM(I, J), J
      PRINT '(/)'
      END IF
     
	  END IF
      
	  END DO
      END DO
     
      WRITE(*,*)" "
      
      DO I=1,R
      WRITE(*,75)"CONSTANT(",I,") = (",REAL(GaM2(I))," + i
     +", AIMAG(GaM2(I)),")"
      END DO

      WRITE(*,*)" "
      
      END SUBROUTINE PRINTCOEF
!------------------------------------------------------------------------ 
C PRINTSOLUT SUBROUTINE
C BY ANDREW BISSELL
C GENERAL: WRITE MATRIX TO SPECIFIED OUTPUT
C PRECONDITIONS: UNIT DESTINATION FOR WRITE STATEMENT, AND MATRIX TO WRITE, ROWS TO PRINT
C POSTCONDITIONS: NONE
C WRITTEN 11/05/2021
!------------------------------------------------------------------------      
      SUBROUTINE PRINTSOLUT(GaM, ROWS)
      INTEGER,INTENT(IN)::ROWS
      COMPLEX,INTENT(IN),DIMENSION(10)::GaM
      INTEGER I

80    FORMAT(' ',10(A,I2,A,F6.2,A,F6.2,A))

      DO I=1,ROWS
      WRITE(*,*)"THE SOLUTION IS:"
      WRITE(*,80)"X",I," = (",REAL(GaM(I))," + i", AIMAG(GaM(I)),")"
     
      END DO
      WRITE(*,*)" "
      END SUBROUTINE PRINTSOLUT
!------------------------------------------------------------------------ 
C MAIN
C COMPLEX EQUATION SOLVER
C BY ANDREW SPATE, ANDREW BISSELL, KELLI HUFF
C GROUP #2
C GENERAL: CREATES A USER DECISION DRIVEN SYSTEM TO TAKE USER INPUTS TO SOLVE
C           MULTIPLE EQUATIONS 
C PRECONDITIONS: MODULE NEEDS TO BE USED
C    SUBROUTINES PRESENT IN SIMULTANEOUS_EQ MODULE:
C		SOLVER, INPUT
C    SUBROUTINES PRESENT IN PROGRAM
C       PRINTSOLUT, PRINTCOEF
C POSTCONDITIONS: SHOWS USER INPUTTED DATA IN EQUATIONS AND SOLUTIONS FOR THOSE EQUATIONS
C                  ,USING THE DATA IT SOLVES FOR EACH VARIABLE(X1,X2,...,Xn) AND DISPLAYS
C                  THE SOLUTIONS TO THE USER. 
C WRITTEN 10/28/2021 - 11/05/2021
!------------------------------------------------------------------------       
      PROGRAM G2P6
      USE SIMULTANEOUS_EQ
      IMPLICIT NONE
      
      COMPLEX, DIMENSION(10,10)::A
      COMPLEX, DIMENSION(10)::B
      INTEGER :: N, ERROR, I
	  CHARACTER(LEN=5)::RESPOND
	  LOGICAL :: INPUTLOOP, PROLOOP
	  
	  INPUTLOOP = .TRUE.
	  PROLOOP = .TRUE.
!----------------------MAIN LOOP FOR USER DECISION-----------------------      
	  DO WHILE(PROLOOP)
      ERROR=0
      WRITE(*,*)"DO YOU WISH TO SOLVE COMPLEX EQUATIONS TODAY? (Y/ELSE)"
	  READ(*,*)RESPOND
	  IF (RESPOND .EQ. 'Y' .OR. RESPOND .EQ. 'y')THEN 
!----------------------------LOOP FOR SOLVER-----------------------------	  
	  DO WHILE(INPUTLOOP)     
      CALL INPUT(A, B, N)
      WRITE(*,*)"          EQUATIONS INPUTTED            "
      WRITE(*,*)"----------------------------------------"
      CALL PRINTCOEF(A, B, N)
!---------------------USER DECISION FOR CORRECT DATA---------------------      
      WRITE(*,*)"ARE THESE DATA POINTS CORRECT (Y/ELSE)"
      READ(*,*)RESPOND
      IF (RESPOND .EQ. 'Y' .OR. RESPOND .EQ. 'y')THEN 
!-----------------------START SOLVER FOR SOLUTION------------------------            
      CALL SOLVER(A, B, N, ERROR )
      WRITE(*,*)"               SOLUTION                 "
      WRITE(*,*)"----------------------------------------"
      CALL PRINTSOLUT(B, N)
      INPUTLOOP = .FALSE.
!--------------USER DIDN'T SAY YES FOR CORRECT DATA DECISION-------------      
      ELSE
      INPUTLOOP = .FALSE.
      END IF
      END DO     
      INPUTLOOP = .TRUE.
!----------------USER DIDN'T SAY YES FOR MAIN LOOP DECISION--------------     
	  ELSE
	  WRITE(*,*)"GOODBYE"
	  PROLOOP = .FALSE.
	  END IF
	  END DO
!-------------------------------END MAIN LOOP----------------------------      
      END PROGRAM