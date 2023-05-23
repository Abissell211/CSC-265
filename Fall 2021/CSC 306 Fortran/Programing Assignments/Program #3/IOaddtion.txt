      PROGRAM G2P3
      IMPLICIT NONE
      
      INTEGER::STATUS
      INTEGER::GARBAGE, ROWS, COLUMNS
      LOGICAL:: EXISTS
      LOGICAL:: FILES_OPEN=.FALSE.
      LOGICAL:: FLAG1=.FALSE.
      LOGICAL:: FLAG2=.FALSE.
      LOGICAL:: FLAG3=.TRUE.                                                   !ASSUMPTION OF GOOD DATA UNLESS OTHERWISE GIVEN
      
      CHARACTER(LEN=20) :: INFILE_NAME
      CHARACTER(LEN=20) :: OUTFILE_NAME
      CHARACTER(LEN=80) :: LINE
      
      REAL :: NUM
      REAL, DIMENSION(10,10)::SUM
      REAL, DIMENSION(10,10)::TEMPMATRIX
      
      
      INTEGER :: LOOPCOUNT
      INTEGER :: I
      INTEGER :: J
      INTEGER :: W
      LOOPCOUNT=1
      I=0
      J=0
      W=1
      TEMPMATRIX=0.0
      SUM=0.0
10    FORMAT(I3)
C     Prompt for, test existence of INPUT FILE NAME
      CALL INPUTFILE(INFILE_NAME, EXISTS, FLAG1)
!------------------------------------------------------------------------------
C     If the file exists, prompt the user to enter a new file name, overwrite the existing file, or 'QUIT',otherwise open the new file.
      IF(FLAG1 .EQV. .TRUE.) THEN
      CALL OUTPUTFILE(OUTFILE_NAME, EXISTS, FLAG2)
      END IF
!-------------------------------------------------------------------------      
C	  OPEN BOTH FILES WITH FLAG
      IF ((FLAG1 .EQV. .TRUE.) .AND. (FLAG2 .EQV. .TRUE.)) THEN
      OPEN(UNIT=1, FILE=INFILE_NAME, STATUS='OLD',IOSTAT=STATUS)
      IF (STATUS .EQ.0) THEN
      OPEN(UNIT=2, FILE=OUTFILE_NAME, STATUS='REPLACE', IOSTAT=STATUS)
      IF (STATUS .EQ. 0) THEN
      FILES_OPEN=.TRUE.
      END IF
      END IF
      END IF
!--------------------------------------------------------------------------     
C     READ FILE PROCESS.  WILL READ FIRST LINE, STORE AS GARBAGE, READ NEXT LINE AND STORE AS ROWS AND COLUMNS, THEN LOOP THROUGH THE MATRICES
      IF (FILES_OPEN .EQV. .TRUE.) THEN
      DO WHILE (STATUS .EQ. 0 .AND. FLAG3)
      IF (LOOPCOUNT .EQ. 1) THEN
      READ(1,10,IOSTAT=STATUS)GARBAGE
73    FORMAT(' ', A20,X, I2)
      WRITE(2,73)'NUMBER OF MATRICES= ',GARBAGE                                    !NEATLY FORMATTED DATA FOR THE NUMBER OF MATRICES
      IF((GARBAGE .LE. 0) .OR. (GARBAGE .GT. 10)) THEN                             ! IF NUMBER OF MATRICES IS BAD DATA, THROWS FLAG TO EXIT PROGRAM
      FLAG3=.FALSE.
      END IF
      ELSE
       IF (LOOPCOUNT .EQ. 2) THEN
       READ(1,*, IOSTAT=STATUS)ROWS,COLUMNS
       WRITE(2,73)"ROWS= ", ROWS                                                   !NEATLY FORMATED DATA FOR ROWS AND COLUMNS
       WRITE(2,73)"COLUMNS= ", COLUMNS
       IF((ROWS .LE.0) .OR. (ROWS .GT.10) .OR. (COLUMNS .LE. 0)                    !CHECKS INPUT FOR BAD DATA, THROWS FLAG TO EXIT PROGRAM
     + .OR. (COLUMNS .GT. 10)) THEN
      FLAG3=.FALSE.
      ENDIF
       ELSE
       WRITE(2,*)"****************************************************"
69    FORMAT(10(F6.2))
70    FORMAT(' ',10(F6.2,2X))
      I=1	
C     READ DATA INTO MATRIX
      DO WHILE (I .LE. ROWS .AND. FLAG3)  
		READ(1,*, IOSTAT=STATUS)(TEMPMATRIX(I,J),J=1, COLUMNS)                       !READING INTO MATRIX
		IF(STATUS .NE. 0 .AND. (COLUMNS .NE. J .OR. ROWS .NE. I))THEN				 !CHECK FOR INCOMPLETE DATA
		WRITE(2,*)'INCOMPLETE DATA: Matrix dimensions do not match data!'
		FLAG3=.FALSE.
		ELSEIF (STATUS .NE. 0) THEN                                                  !CHECK IF LINE IS END OF FILE
		FLAG3=.FALSE.								                                 !THROWS FLAG IF END OF FILE
		ELSE
		LOOPCOUNT=LOOPCOUNT+1                                                        !UPDATE LOOP COUNTER
		I=I+1                                                                        !UPDATE ROW
		END IF
       END DO
C     MATRIX FINALIZED
       IF (FLAG3) THEN                                                               !IF FLAG3 IS TRUE THEN PROCESS ADDITION, IF NOT BYPASS
9      FORMAT(' ',A7,X,I2)
       WRITE(2,9)"MATRIX", W                                                         !NICELY FORMATED OUTPUT HEADING
       CALL PRINTARRAY(TEMPMATRIX,ROWS,COLUMNS)
       W=W+1						                                                 !INCREMENT NUMBER OF MATRIXES
       CALL Matrix_Addition (TEMPMATRIX,SUM,ROWS,COLUMNS)                            !CALL ADDITION SUBROUTING
       IF (W .GT. GARBAGE) THEN
       FLAG3= .FALSE.
       END IF 
       END IF
       END IF
      END IF
      LOOPCOUNT=LOOPCOUNT+1                                                          !UPDATE LOOP COUNTER FOR CORRECT LINE MENAING
      END DO
      WRITE(2,*)"****************************************************"
66    FORMAT(' ',A,I2,A)
      WRITE(2,66)"SUM OF ALL ",W-1," MATRICES"                                       !NICELY FORMATTED HEADING FOR OUTPUT FILE
      CALL PRINTARRAY(SUM, ROWS, COLUMNS)                                            !WRITING SUM ARRAY TO THE OUTPUT FILE
      CLOSE(1)                                                                       !CLOSE INPUT FILE 
      CLOSE(2)                                                                       !CLOSE OUTPUT FILE 
      END IF

      END PROGRAM
!------------------------------------------------------------------------- 
C MATRIX_ADDITION SUBROUTINE
C BY ANDREW BISSELL
C GENERAL: ADD 2 MATRIXES TOGETHER, RETURN SUM MATRIX
C PRECONDITIONS: REQUIRES 2 MATRIXES, AND THE NUMBER OF ROWS AND COLUMNS FOR PROCESSING
C POSTCONDITIONS: RETURNS AN UPDATED SUM MATRIX
C WRITTEN 9/26
C REVISION 9/27- ELIMINATED SECOND ARRAY INPUT, IN LIEU TO ADD TEMP TO SUM        
!-------------------------------------------------------------------------
      SUBROUTINE Matrix_Addition(TEMPMATRIX,SUM,ROWS,COLUMNS)
      INTEGER, INTENT(IN)::ROWS,COLUMNS
      REAL, INTENT(IN),DIMENSION(10,10)::TEMPMATRIX
      REAL, INTENT(OUT),DIMENSION(10,10)::SUM
      INTEGER i,j
      DO i=1,ROWS
         DO j=1,COLUMNS
            SUM(i,j)=SUM(i,j)+TEMPMATRIX(i,j)
         END DO
      END DO
      END SUBROUTINE Matrix_Addition
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
      DO I=1,ROWS
      WRITE(2,70)(GENERICassMATRIX(I,J),J=1,COLUMNS)
      END DO
      END SUBROUTINE PRINTARRAY
      
!-------------------------------------------------------------------------
C OUTPUTFILE SUBROUTINE
C BY ANDREW SPATE, JUSTIN GUNDERSON, ANDREW BISSELL AND DR PYZDROWSKI
C GENERAL: PROMPTS FOR OUTPUT FILE FROM USER
C PRECONDITIONS: NONE
C POSTCONDITIONS: RETURNS FILE NAME, AND EXISTING STATUS AS FLAG
C WRITTEN: 9/23
!-------------------------------------------------------------------------
      SUBROUTINE OUTPUTFILE(OUTFILE_NAME, EXISTS, FLAG2)
      CHARACTER(LEN=20), INTENT(OUT) :: OUTFILE_NAME
      CHARACTER(LEN=20)::TEMP_NAME
      LOGICAL, INTENT(OUT):: EXISTS, FLAG2
      WRITE(*,*)'ENTER OUTPUT FILE NAME (INCLUDING FILE EXTENSION)'
      READ(*,'(A)')OUTFILE_NAME
      INQUIRE(FILE=OUTFILE_NAME,EXIST=EXISTS)
      IF (EXISTS) THEN
      FLAG2=.FALSE.
      ELSE
      FLAG2=.TRUE.
      END IF
      TEMP_NAME=OUTFILE_NAME
      DO WHILE (FLAG2 .EQV. .FALSE. .OR.(TRIM(OUTFILE_NAME) 
     +.EQ. "QUIT"))
      WRITE(*,*)"YOU ENTERED A USED FILE NAME, ENTER A NEW FILENAME OR
     +OVERWRITE (TO OVERWRITE THE FILE) OR QUIT"
      READ(*,'(A)')OUTFILE_NAME
C     SELECT CASE TO DETERMINE WHAT USER WANTS TO DO NEXT IF BAD OUTPUT FILE GIVEN
      SELECT CASE (TRIM(OUTFILE_NAME))
      CASE("QUIT")
      FLAG2=.FALSE.
      CASE("OVERWRITE")
      OUTFILE_NAME=TEMP_NAME
      FLAG2=.TRUE.
      CASE DEFAULT 
      INQUIRE(FILE=OUTFILE_NAME, EXIST=EXISTS)
      IF (EXISTS) THEN
      FLAG2=.TRUE.
      END IF 
      END SELECT 
C     END DO FROM RE-ENTER OUTPUTFILE NAME TRUE
      END DO
      END SUBROUTINE OUTPUTFILE
      
      
!-----------------------------------------------------------------------------
C INPUTFILE SUBROUTINE
C BY ANDREW SPATE, JUSTIN GUNDERSON, ANDREW BISSELL AND DR PYZDROWSKI
C GENERAL: PROMPTS FOR INPPUT FILE FROM USER
C PRECONDITIONS: NONE
C POSTCONDITIONS: RETURNS FILE NAME, AND EXISTING STATUS AS FLAG
C WRITTEN: 9/23
!-----------------------------------------------------------------------------
      SUBROUTINE INPUTFILE(INFILE_NAME, EXISTS, FLAG1)
      CHARACTER(LEN=20), INTENT(OUT) :: INFILE_NAME
      LOGICAL, INTENT(OUT):: EXISTS, FLAG1
      WRITE(*,*)'ENTER INPUT FILE NAME (INCLUDING FILE EXTENSION)'
      READ(*,'(A)')INFILE_NAME 
      INQUIRE(FILE=INFILE_NAME,EXIST=EXISTS)
      IF (EXISTS)THEN
      FLAG1=.TRUE.
      END IF
C     IF FILE IS FALSE, THEN LOOP FOR CONTINUE
      DO WHILE ((FLAG1 .EQV. .FALSE.) .AND. (TRIM(INFILE_NAME) 
     +.NE. "QUIT"))
      WRITE(*,*)'ENTER INPUT FILE NAME OR QUIT TO QUIT'
      READ(*,'(A)')INFILE_NAME 
      INQUIRE(FILE=INFILE_NAME,EXIST=EXISTS)
      END DO
      IF (EXISTS) THEN
      FLAG1=.TRUE.
      END IF   
      END SUBROUTINE INPUTFILE  