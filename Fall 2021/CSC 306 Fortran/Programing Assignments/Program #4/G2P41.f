!------------------------------------------------------------------------
!------------------------------------------------------------------------
      MODULE MATRIX_CALC
      IMPLICIT NONE
      CONTAINS
!------------------------------------------------------------------------ 
C ADDITION SUBROUTINE
C BY ANDREW SPATE & ANDREW BISSELL
C GENERAL: WILL PROMPT FOR 2 MATRIXES, CHECK DIMENSIONS, AND THEN ADD THEM TOGETHER AND WRITE TO SCREEN
C PRECONDITIONS: N/A
C POSTCONDITIONS: WILL WRITE SUM TO SCREEN
C WRITTEN 10/02/2021
!------------------------------------------------------------------------
      SUBROUTINE ADDITION()
      REAL, DIMENSION(10,10) :: MATRIX1
      REAL, DIMENSION(10,10) :: MATRIX2
      INTEGER :: ROWS1, ROWS2, COLUMNS1, COLUMNS2, I, J
      LOGICAL :: FLAG2
      CALL GETMATRIX(MATRIX1, ROWS1, COLUMNS1)
      CALL GETMATRIX(MATRIX2, ROWS2, COLUMNS2)
      CALL CHECKMATRIX_AS(ROWS1, ROWS2, COLUMNS1, COLUMNS2, FLAG2)
C-----------------END DATA DECLARATIONS AND MATRIX CALLS-----------------
      IF (FLAG2 .EQV. .TRUE.) THEN
      CALL PRINTARRAY(MATRIX1, ROWS1, COLUMNS1) 
      WRITE(*,*)"+"
      CALL PRINTARRAY(MATRIX2, ROWS2, COLUMNS2)
      WRITE(*,*)"="
      DO I=1,ROWS1
         DO J=1,COLUMNS2
            MATRIX1(I,J)=MATRIX1(I,J)+MATRIX2(I,J)
         END DO
      END DO
C---------------------------END CALCULATIONS-----------------------------
      WRITE(*,*)"********SUM MATRIX********"
      CALL PRINTARRAY(MATRIX1, ROWS1, COLUMNS1)
      ELSE
      WRITE(*,*)"ERROR INCORRECT DATA CHECK REQUIREMENTS"
      END IF
      END SUBROUTINE ADDITION
      
!------------------------------------------------------------------------ 
C SUBTRACT SUBROUTINE
C BY ANDREW SPATE & ANDREW BISSELL
C GENERAL: WILL PROMPT FOR 2 MATRIXES, CHECK DEMENSIONS, AND THEN SUBTRACT THEM AND WRITE TO SCREEN
C PRECONDITIONS: N/A
C POSTCONDITIONS: WILL WRITE DIFFERENCE TO SCREEN
C WRITTEN 10/02/2021
!------------------------------------------------------------------------      
      SUBROUTINE SUBTRACTION ()
      REAL, DIMENSION(10,10) :: MATRIX1
      REAL, DIMENSION(10,10) :: MATRIX2
      INTEGER :: ROWS1, ROWS2, COLUMNS1, COLUMNS2, I, J
      LOGICAL :: FLAG2
      CALL GETMATRIX(MATRIX1, ROWS1, COLUMNS1)
      CALL GETMATRIX(MATRIX2, ROWS2, COLUMNS2)
      CALL CHECKMATRIX_AS(ROWS1, ROWS2, COLUMNS1, COLUMNS2, FLAG2)
C-----------------END DATA DECLARATIONS AND MATRIX CALLS-----------------
      IF (FLAG2 .EQV. .TRUE.) THEN
      CALL PRINTARRAY(MATRIX1, ROWS1, COLUMNS1)
      WRITE(*,*)"-"
      CALL PRINTARRAY(MATRIX2, ROWS2, COLUMNS2)
      WRITE(*,*)"="
      DO I=1,ROWS1
         DO J=1,COLUMNS2
            MATRIX1(I,J)=MATRIX1(I,J)-MATRIX2(I,J)
         END DO
      END DO
C---------------------------END CALCULATIONS-----------------------------
      WRITE(*,*)"********DIFFERENCE MATRIX********"
      CALL PRINTARRAY(MATRIX1, ROWS1, COLUMNS1)
      ELSE
      WRITE(*,*)"ERROR INCORRECT DATA CHECK REQUIREMENTS"
      END IF
      END SUBROUTINE SUBTRACTION
        
!------------------------------------------------------------------------ 
C TRANSPOSE SUBROUTINE
C BY JUSTIN GUNDERSON
C GENERAL: WILL TANSPOSE A GIVEN MATRIX
C PRECONDITIONS: N/A
C POSTCONDITIONS: WILL WRITE TRANSPOSED VERSION
C WRITTEN 10/08/2021
!------------------------------------------------------------------------      
      SUBROUTINE TRANSPOSE()
      INTEGER::ROWS1
      INTEGER:: COLUMNS1, I, J
      REAL,DIMENSION(10,10)::MATRIX1
      REAL, DIMENSION(10,10)::TEMP
      CALL GETMATRIX(TEMP, ROWS1, COLUMNS1)
      I=1
      J=1
C-----------------END DATA DECLARATIONS AND MATRIX CALLS-----------------
      CALL PRINTARRAY(TEMP, ROWS1, COLUMNS1)
      DO WHILE (I .LE. ROWS1)
      
      DO WHILE (J .LE. COLUMNS1)
      
      MATRIX1(J,I) = TEMP(I,J)
      J=J+1
      END DO
      IF (J .GE. COLUMNS1)THEN
      J=1 
      END IF
      I=I+1
      END DO 
C---------------------------END CALCULATIONS-----------------------------
      WRITE(*,*)"TRANSPOSED"
      CALL PRINTARRAY(MATRIX1, COLUMNS1, ROWS1)
      END SUBROUTINE TRANSPOSE
      
!------------------------------------------------------------------------ 
C GETMATRIX SUBROUTINE
C BY ANDREW SPATE & ANDREW BISSELL
C GENERAL: TAKES A INPUT FROM THE USER TO CREATE AN ARRAY WITH MAX SIZE OF 10 ROWS AND 10 COLUMNS
C PRECONDITIONS: N/A
C POSTCONDITIONS: RETRURNS A CREATED MATRIX TO THE SUBROUTINE CALL
C WRITTEN 10/02/2021
!------------------------------------------------------------------------      
      SUBROUTINE GETMATRIX(TEMPMATRIX, ROWS, COLUMNS)
      INTEGER, INTENT (OUT) :: ROWS, COLUMNS
      INTEGER :: TOTAL, USRTERMS
      REAL, INTENT(OUT),DIMENSION(10,10) :: TEMPMATRIX
      INTEGER :: I,J
C-------------------------END DATA DECLARATIONS--------------------------      
10    FORMAT(' ', A,X,I3)
      WRITE(*,*)"ENTER NUMBER OF ROWS YOU WOULD LIKE TO ENTER"
      READ(*,*)ROWS
      DO WHILE((ROWS .GT. 10) .OR. (ROWS .LT. 1))
      WRITE(*,*)'OUT OF BOUNDS DATA PLEASE ENTER A NUMBER 1 - 10'
      READ(*,*)ROWS
      END DO
      WRITE(*,*)"ENTER NUMBER OF COLUMNS YOU WOULD LIKE TO ENTER"
      READ(*,*)COLUMNS
      DO WHILE((COLUMNS .GT. 10) .OR. (COLUMNS .LT. 1))
      WRITE(*,*)'OUT OF BOUNDS DATA PLEASE ENTER A NUMBER 1 - 10'
      READ(*,*)COLUMNS
      END DO
      TOTAL=COLUMNS*ROWS
      WRITE(*,*)"TO FILL MATRIX, ENTER 1 NUMBER PER LINE"
      DO I=1,ROWS
      WRITE(*,10)"ROW " ,I
      DO J=1,COLUMNS
      WRITE(*,10)"COLUMN " ,J
      READ(*,*)TEMPMATRIX(I,J)
      END DO                                                                   !END COLUMNS LOOP
      END DO                                                                   !END ROWS LOOP
      WRITE(*,*)"MATRIX LOADED"
      
      END SUBROUTINE GETMATRIX

!------------------------------------------------------------------------ 
C HELP SUBROUTINE
C BY ANDREW SPATE & ANDREW BISSELL
C GENERAL: CREATES A USER "HELP" DISPLAY FOR WHAT TO INPUT TO FOR CASE STATEMENT
C PRECONDITIONS: N/A
C POSTCONDITIONS: WRITES THE CASE SELECTION
C WRITTEN 10/05/2021
!------------------------------------------------------------------------
      SUBROUTINE HELP()
      WRITE(*,*)"TYPE IN THE NUMBER FOR THE OPERATION YOU WISH TO DO"
      WRITE(*,*)"1 FOR MATRIX ADDITION"
      WRITE(*,*)"2 FOR MATRIX SUBTRACTION"
      WRITE(*,*)"3 FOR DOT MULTIPLICATION"
      WRITE(*,*)"4 FOR TRANSPOSE"
      WRITE(*,*)"QUIT TO EXIT THE CALCULATOR"
      END SUBROUTINE HELP
      
      
!------------------------------------------------------------------------ 
C PRINTARRAY SUBROUTINE
C BY ANDREW SPATE
C GENERAL: WRITE MATRIX TO SPECIFIED OUTPUT
C PRECONDITIONS: UNIT DESTINATION FOR WRITE STATEMENT, AND MATRIX TO WRITE, ROWS AND COLUMNS TO PRINT
C POSTCONDITIONS: NONE
C WRITTEN 09/27/2021
C REVISED 09/27/2021- PUT MATRIX INTO GENERIC FORM VS SPECIFIC
!------------------------------------------------------------------------
      SUBROUTINE PRINTARRAY(GENERICassMATRIX, ROWS, COLUMNS)
      INTEGER, INTENT(IN)::ROWS, COLUMNS
      REAL,INTENT(IN),DIMENSION(10,10)::GENERICassMATRIX
      INTEGER I,J
C-------------------------END DATA DECLARATIONS-------------------------- 
70    FORMAT(' ',10(F6.2,2X))   
      DO I=1,ROWS
      WRITE(*,70)(GENERICassMATRIX(I,J),J=1,COLUMNS)
      END DO
      END SUBROUTINE PRINTARRAY
      
!------------------------------------------------------------------------ 
C CHECKMATRIX_AS SUBROUTINE
C BY ANDREW SPATE
C GENERAL: USED TO CHECK IF ROWS AND COLUMNS OF TWO MATRIX ARE EQUAL FOR ADDITION AND SUBTRACTION
C PRECONDITIONS: NEED TO PASS ROWS AND COLUMNS OF TWO CREATED ARRAYS
C POSTCONDITIONS: RETURNS FLAG FOR GOOD OR BAD DATA
C WRITTEN 09/27/2021
C REVISED 09/27/2021- PUT MATRIX INTO GENERIC FORM VS SPECIFIC
!------------------------------------------------------------------------      
      SUBROUTINE CHECKMATRIX_AS(ROWS1, ROWS2, COLUMNS1, COLUMNS2, FLAG2)
      INTEGER, INTENT(IN)::ROWS1,ROWS2, COLUMNS1, COLUMNS2
      LOGICAL, INTENT(OUT)::FLAG2
C-------------------------END DATA DECLARATIONS-------------------------- 
      IF ((ROWS1 .EQ. ROWS2) .AND. (COLUMNS1 .EQ. COLUMNS2)) THEN
      FLAG2= .TRUE.
      ELSE
      FLAG2= .FALSE.
      END IF
      END SUBROUTINE CHECKMATRIX_AS
      
!------------------------------------------------------------------------ 
C CHECKMATRIX_DOT SUBROUTINE
C BY ANDREW BISSELL
C GENERAL: USED TO CHECK FIRST MATRIX COLUMNS AND SECOND MATRIX ROWS ARE EQUAL
C PRECONDITIONS: NEED TO PASS FIRST MATRIX COLUMNS AND SECOND MATRIX ROWS OF TWO CREATED ARRAYS
C POSTCONDITIONS: RETURNS FLAG FOR GOOD OR BAD DATA
C WRITTEN 10/12/2021
!------------------------------------------------------------------------ 
      SUBROUTINE CHECKMATRIX_DOT(ROWS2, COLUMNS1, FLAG2)
      INTEGER, INTENT(IN)::ROWS2, COLUMNS1
      LOGICAL, INTENT(OUT)::FLAG2
C-------------------------END DATA DECLARATIONS-------------------------- 
      IF (ROWS2 .EQ. COLUMNS1) THEN
      FLAG2= .TRUE.
      ELSE
      FLAG2= .FALSE.
      END IF
      END SUBROUTINE CHECKMATRIX_DOT      
      
      END MODULE    
!------------------------------------------------------------------------
!------------------------------------------------------------------------     

      
!------------------------------------------------------------------------ 
C DOTPRODUCT FUNCTION
C BY ANDREW BISSELL, JUSTIN GUNDERSON
C GENERAL: TAKES A ROW FROM MATRIX AND A COLUMN FROM ANOTHER AND RETURNS THE DOT PRODUCT
C PRECONDITIONS: NEED TWO MATRIXIES WITH THE FIRST ONE PASSING ITS ROWS AND THE SECOND PASSING ITS COLUMNS
C POSTCONDITIONS: RETURNS THE DOT PRODUCT
C WRITTEN 10/13/2021
!------------------------------------------------------------------------ 
      REAL FUNCTION DOT(A,B,ROWS2)
      IMPLICIT NONE
      INTEGER ROWS2,I
      REAL A(10),B(10)
      DO I=1, ROWS2
      DOT=DOT + A(I)*B(I)
      END DO
      RETURN
      END FUNCTION
      
!------------------------------------------------------------------------ 
C MAIN
C THE MATRIX CALCULATOR PROGRAM
C BY ANDREW SPATE, ANDREW BISSELL, JUSTIN GUNDERSON
C GROUP #2
C GENERAL: HOUSES THE MAIN PROGRAM
C PRECONDITIONS: MODULE MATRIX_CALC REQUIRED
C    SUBROUTINES PRESENT IN MODULE:
C		PRINTARRAY, CHECKMATRIX_AS/DOT, HELP, GETMATRIX, TRANSPOSE, DOTMULT, ADDITION, SUBTRACTION
C POSTCONDITIONS: CREATES A USER MENU FOR CALCUATOR OPERATIONS
C WRITTEN 09/29/2021 - 10/13/2021
!------------------------------------------------------------------------       
      PROGRAM MATRIX_CALCULATOR
      USE MATRIX_CALC
      IMPLICIT NONE
      REAL DOT
      REAL, DIMENSION(10,10)::MATRIX1
      REAL, DIMENSION(10,10)::MATRIX2
      INTEGER ::ROWS1,ROWS2,COLUMNS1,COLUMNS2,I,J,N,TEMP
      REAL, DIMENSION(10,10)::MATRIXOUT
      LOGICAL:: FLAG1
      LOGICAL :: FLAG2 
      CHARACTER(LEN=20):: LINE
C-------------------------END DATA DECLARATIONS--------------------------
      FLAG1=.TRUE.
      CALL HELP()
      DO WHILE(FLAG1)                                                          !MAIN LOOP
      WRITE(*,*)"ENTER A NUMBER TO SELECT AN OPTION OR TYPE QUIT TO EXIT
     + OR HELP FOR HELP"
      READ(*,*)LINE
      SELECT CASE (TRIM(LINE))
C--------------------------------CASE 1---------------------------------- 
      CASE("1")
      WRITE(*,*)"ADDITION"
      CALL ADDITION
C--------------------------------CASE 2---------------------------------- 
      CASE("2")
      WRITE(*,*)"SUBTRACTION"
      CALL SUBTRACTION
C--------------------------------CASE 3---------------------------------- 
      CASE("3")     
      WRITE(*,*)"DOT MULTIPLICATION"
      MATRIXOUT=0    
      CALL GETMATRIX(MATRIX1, ROWS1, COLUMNS1)
      CALL GETMATRIX(MATRIX2, ROWS2, COLUMNS2)
      CALL CHECKMATRIX_DOT(ROWS2, COLUMNS1, FLAG2)
      I=1
      J=1
C-----------------END DATA DECLARATIONS AND MATRIX CALLS-----------------
      IF (FLAG2 .EQV. .TRUE.) THEN
      CALL PRINTARRAY(MATRIX1, ROWS1, COLUMNS1)
      WRITE(*,*)"*"
      CALL PRINTARRAY(MATRIX2, ROWS2, COLUMNS2)
      WRITE(*,*)"="
      DO I=1, ROWS1
      DO J=1, COLUMNS2
      MATRIXOUT(I,J)=DOT(MATRIX1(I,:),MATRIX2(:,J),ROWS2)
      END DO
      END DO
C---------------------------END CALCULATIONS-----------------------------
      CALL PRINTARRAY(MATRIXOUT, ROWS1,COLUMNS2)
      ELSE
      WRITE(*,*)"ERROR INCORRECT DATA CHECK REQUIREMENTS"
      END IF
C--------------------------------CASE 4----------------------------------       
      CASE("4")
      WRITE(*,*)"TRANSPOSE"
      CALL TRANSPOSE
C-------------------------------CASE QUIT--------------------------------
      CASE("QUIT")
      FLAG1=.FALSE.
C-------------------------------CASE quit--------------------------------
      CASE("quit")
      FLAG1=.FALSE.
C-------------------------------CASE HELP--------------------------------
      CASE("HELP")
      CALL HELP()
C-------------------------------CASE help--------------------------------
      CASE("help")
      CALL HELP()
C------------------------------CASE DEFAULT------------------------------
      CASE DEFAULT
      WRITE(*,*)"INVALID MENU ENTRY, TYPE HELP FOR HELP"
      END SELECT
      END DO                                                                   !END MAIN LOOP DO LOOP
      END
      