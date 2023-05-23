!     ANDREW SPATE, ANDREW BISSELL, KELLI HUFF
!     GROUP 2 
!     FORTRAN 306
!     LINKED LIST PROGRAM
!     PROGRAM 7
!------------------------------------------------------------------------
!************************************************************************
!------------------------------------------------------------------------ 
! I0_FILE MODULE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL
! GENERAL: MODULE FOR THE I/O FILE SETUP AND CREATION
! SUBROUTINES:
!	OPEN_MASTER, INPUTFILE, OUTPUTFILE, READ_THE_FILE
! WRITTEN: 10/02/2021
! REVISED: 11/10/2021
!------------------------------------------------------------------------
!************************************************************************
!------------------------------------------------------------------------
      MODULE IO_FILE
      IMPLICIT NONE
      
      INTEGER :: STATUS
      INTEGER :: LOOPCOUNT
      INTEGER :: I
      INTEGER :: J
      INTEGER :: X=1
      INTEGER :: Y=2
           
      LOGICAL :: EXISTS
      LOGICAL :: FILES_OPEN
      LOGICAL :: FLAG1
      LOGICAL :: FLAG2
      LOGICAL :: FLAG3
      
      CHARACTER(LEN=20) :: INFILE_NAME
      CHARACTER(LEN=20) :: OUTFILE_NAME
      CHARACTER(LEN=20) :: TEMP_NAME
      CHARACTER(LEN=80) :: LINE
      
      CONTAINS
!------------------------------------------------------------------------ 
! OPEN_MASTER SUBROUTINE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL
! GENERAL: MASTER SUBROUTINE FOR OPENING INPUT FILE AND CREATING AN OUTPUT FILE
! PRECONDITIONS: A CORRECT INPUT FILE 
! POSTCONDITIONS: CHECKS INPUT FILE AND CREATES OR OVERRIDES AN OUTPUT FILE
! WRITTEN: 10/02/2021
! REVISED: 11/10/2021
!------------------------------------------------------------------------
      SUBROUTINE OPEN_MASTER(COUNTSFROMFILE, NAMESFROMFILE, BADDATA)
      INTEGER, DIMENSION(30),INTENT(OUT)::COUNTSFROMFILE
      CHARACTER(LEN=50), DIMENSION(30), INTENT(OUT)::NAMESFROMFILE
      LOGICAL, INTENT(OUT) :: BADDATA
      
!     Prompt for, test existence of INPUT FILE NAME
      CALL INPUTFILE()
!     If the file exists, prompt the user to enter a new file name, overwrite the existing file, or 'QUIT',otherwise open the new file.
      IF(FLAG1 .EQV. .TRUE.) THEN
      CALL OUTPUTFILE()
      END IF      
!     OPEN BOTH FILES WITH FLAG
      IF ((FLAG1 .EQV. .TRUE.) .AND. (FLAG2 .EQV. .TRUE.)) THEN
      OPEN(UNIT=1, FILE=INFILE_NAME, STATUS='OLD',IOSTAT=STATUS)
      IF (STATUS .EQ.0) THEN
      OPEN(UNIT=2, FILE=OUTFILE_NAME, STATUS='REPLACE', IOSTAT=STATUS)
      IF (STATUS .EQ. 0) THEN
      FILES_OPEN=.TRUE.
      END IF
      END IF
      END IF
      IF (FILES_OPEN)THEN
      CALL READ_THE_FILE(COUNTSFROMFILE, NAMESFROMFILE)
      ELSE
      BADDATA=.TRUE.
      END IF
      END SUBROUTINE     
!-----------------------------------------------------------------------------
! INPUTFILE SUBROUTINE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL AND DR PYZDROWSKI
! GENERAL: PROMPTS FOR INPPUT FILE FROM USER
! PRECONDITIONS: NONE
! POSTCONDITIONS: RETURNS FILE NAME, AND EXISTING STATUS AS FLAG
! WRITTEN: 09/23/2021
! REVISED: 11/10/2021
!-----------------------------------------------------------------------------
      SUBROUTINE INPUTFILE()
!      CHARACTER(LEN=20) :: INFILE_NAME
!      LOGICAL, INTENT(OUT):: EXISTS, FLAG1
      WRITE(*,*)'ENTER INPUT FILE NAME (INCLUDING FILE EXTENSION)'
      READ(*,'(A)')INFILE_NAME 
      INQUIRE(FILE=INFILE_NAME,EXIST=EXISTS)
      
      IF (EXISTS)THEN
      FLAG1=.TRUE.
      END IF
!     IF FILE IS FALSE, THEN LOOP FOR CONTINUE
      DO WHILE ((FLAG1 .EQV. .FALSE.) .AND. (TRIM(INFILE_NAME) .NE. "QUIT"))
      WRITE(*,*)'ENTER INPUT FILE NAME OR QUIT TO QUIT'
      READ(*,'(A)')INFILE_NAME 
      INQUIRE(FILE=INFILE_NAME,EXIST=EXISTS)
      IF (EXISTS) THEN
      FLAG1=.TRUE.
      END IF
      END DO
      IF (EXISTS) THEN
      FLAG1=.TRUE.
      END IF   
      END SUBROUTINE INPUTFILE   
!-------------------------------------------------------------------------
! OUTPUTFILE SUBROUTINE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL AND DR PYZDROWSKI
! GENERAL: PROMPTS FOR OUTPUT FILE FROM USER
! PRECONDITIONS: NONE
! POSTCONDITIONS: RETURNS FILE NAME, AND EXISTING STATUS AS FLAG
! WRITTEN: 09/23/2021
! REVISED: 11/10/2021
!-------------------------------------------------------------------------
      SUBROUTINE OUTPUTFILE()
      WRITE(*,*)'ENTER OUTPUT FILE NAME (INCLUDING FILE EXTENSION)'
      READ(*,'(A)')OUTFILE_NAME
      INQUIRE(FILE=OUTFILE_NAME,EXIST=EXISTS)
      IF (EXISTS) THEN
      FLAG2=.FALSE.
      ELSE
      FLAG2=.TRUE.
      END IF
      TEMP_NAME=OUTFILE_NAME
      DO WHILE (FLAG2 .EQV. .FALSE. .AND.(TRIM(OUTFILE_NAME) .EQ. "QUIT"))
      WRITE(*,*)"YOU ENTERED A USED FILE NAME, ENTER A NEW FILENAME OR OVERWRITE (TO OVERWRITE THE FILE) OR QUIT"
      READ(*,'(A)')OUTFILE_NAME
!     SELECT CASE TO DETERMINE WHAT USER WANTS TO DO NEXT IF BAD OUTPUT FILE GIVEN
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
!     END DO FROM RE-ENTER OUTPUTFILE NAME TRUE
      END DO
      
      END SUBROUTINE OUTPUTFILE     
!------------------------------------------------------------------------ 
! READ_THE_FILE SUBROUTINE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL
! GENERAL: READS CONTENTS OF THE INPUT FILE INTO AN ARRAY
! PRECONDITIONS: NEED A CORRECTLY OPENED INPUT FILE
! POSTCONDITIONS: FILLS THE POINTS ARRAY WITH THE INPUT FILE DATA
! WRITTEN: 10/02/2021
! REVISED: 11/10/2021
!------------------------------------------------------------------------
      SUBROUTINE READ_THE_FILE(COUNTSFROMFILE, NAMESFROMFILE)
!      LOGICAL, INTENT(OUT) :: BADDATA
      CHARACTER(LEN=50), DIMENSION(30), INTENT(OUT):: NAMESFROMFILE
      INTEGER, DIMENSION(30),INTENT(OUT) :: COUNTSFROMFILE     
      INTEGER :: I=1
      INTEGER :: BLANK
            
      IF (FILES_OPEN .EQV. .TRUE.) THEN
      STATUS=0
      DO WHILE(I .LE. 25 )
      
      READ(1, *, IOSTAT=STATUS)NAMESFROMFILE(I)
      READ(1, *, IOSTAT=STATUS)COUNTSFROMFILE(I)
      I=I+1
      END DO 
      READ(1, *, IOSTAT=STATUS)BLANK
      IF (STATUS .NE. 5001) THEN
      WRITE(*,*)"ADDITIONAL DATA IS DETECTED, RECORDS >25 WILL BE IGNORED"
      END IF
      END IF
      END SUBROUTINE
!------------------------------------------------------------------------
      END MODULE
!------------------------------------------------------------------------
!************************************************************************
!------------------------------------------------------------------------ 
! LINKED_LIST MODULE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL
! GENERAL: MODULE RUNNING DOUBLY LINKED LIST OPERATIONS
! SUBROUTINES:
!	LINKED_MASTER, TRAVERSEMASTER, ADDNODE, DELETENODE, TRAVERSE
! WRITTEN: 10/02/2021
! REVISED: 11/10/2021
!------------------------------------------------------------------------
!************************************************************************
!------------------------------------------------------------------------
      MODULE LINKED_LIST
      IMPLICIT NONE
      
      TYPE :: DEATHPOOL
      CHARACTER(LEN=20) :: NAME
      INTEGER ::COUNTNUM
      TYPE(DEATHPOOL),POINTER:: NEXT
      TYPE(DEATHPOOL),POINTER:: PREVIOUS
      END TYPE 
      
      TARGET :: DEATHPOOL
      TYPE(DEATHPOOL),POINTER :: HEAD
      TYPE(DEATHPOOL),POINTER :: TAIL
      TYPE(DEATHPOOL),POINTER :: INTERNAL
      TYPE(DEATHPOOL),POINTER :: BULLSEYE     
      INTEGER :: ISTAT
      
      CHARACTER*30, DIMENSION(25)::DEATHARRAY
         
      CONTAINS
!------------------------------------------------------------------------ 
! LINKED_MASTER SUBROUTINE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL
! GENERAL: USED TO PROCESS THE GAME FOR THE DOUBLY LINKED LIST
! PRECONDITIONS: REQUIRES THE ADDNODE AND TRAVERSEMASTER SUBROUTINES AND TYPE
!  DEATHPOOL CREATED. 
! POSTCONDITIONS: TAKES THE USER INPUT DATA AND CREATES A DOUBLY LINKED LIST
!  THAT WILL COUNT THROUGH AND DELETE NODES BASED OF THE NODES COUNT.
! WRITTEN: 10/10/2021 - 10/16/2021
!------------------------------------------------------------------------
      SUBROUTINE LINKED_MASTER(NAMESFROMFILE, COUNTSFROMFILE)
      INTEGER, DIMENSION(30),INTENT(IN) ::COUNTSFROMFILE
      CHARACTER(LEN=50),DIMENSION(30),INTENT(IN)::NAMESFROMFILE
      INTEGER :: I=1
      INTEGER :: BLAH
      
      !ADD NAMES AND COUNT TO LINKED LIST
      DO WHILE (NAMESFROMFILE(I) .NE. ' ')
      IF (COUNTSFROMFILE(I) .NE. 0) THEN
      CALL ADDNODE(NAMESFROMFILE(I), COUNTSFROMFILE(I))
      ELSE
      WRITE(2,*)TRIM(NAMESFROMFILE(I)), " WAS DEAD ON ARRIAL TO DEATH ISLAND"
      WRITE(*,*)TRIM(NAMESFROMFILE(I)), " WAS DEAD ON ARRIAL TO DEATH ISLAND"
      END IF
      I=I+1
      END DO
      !LINKED LIST COMPLETE
      WRITE(*,*)"-----LET THE GAMES BEGIN-----"
      WRITE(2,*)"-----LET THE GAMES BEGIN-----"
      !START OF DEATHPOOL
      INTERNAL=>HEAD
      
      DO WHILE ((ASSOCIATED(HEAD%NEXT)) .AND. (ASSOCIATED(TAIL%PREVIOUS)))
      CALL TRAVERSEMASTER()
      
      BULLSEYE=>INTERNAL
            
      END DO
      WRITE(*,*)"========================================"
      WRITE(*,*)"\    /\    / * |\  | |\  | |--- |  )"
      WRITE(*,*)" \  /  \  /  | | \ | | \ | |--- | \"
      WRITE(*,*)"  \/    \/   | |  \| |  \| |--- |  \"
      WRITE(*,*)TRIM(INTERNAL%NAME)," HAS SURVIVED"
      WRITE(2,*)"========================================"
      WRITE(2,*)"\    /\    / * |\  | |\  | |--- |  )"
      WRITE(2,*)" \  /  \  /  | | \ | | \ | |--- | \"
      WRITE(2,*)"  \/    \/   | |  \| |  \| |--- |  \"
      WRITE(2,*)TRIM(INTERNAL%NAME)," HAS SURVIVED"
           
      END SUBROUTINE
!------------------------------------------------------------------------ 
! TRAVERSEMASTER SUBROUTINE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL
! GENERAL: CONTROL SUBROUTINE FOR THE TRAVERSE SUBROUTINE
! PRECONDITIONS: REQUIRES THE TRAVERSE SUBROUTINE AND TYPE DEATHPOOL MUST 
!  BE CREATED.
! POSTCONDITIONS: TAKES A COUNT CHECKS IF IT A POSITIVE OR NEGATIVE COUNT
!  THEN CALLS THE TRAVERSE SUBROUTINE TO FINISH THE TRAVERSAL
! WRITTEN: 10/10/2021 - 10/16/2021
!------------------------------------------------------------------------
      SUBROUTINE TRAVERSEMASTER()
      
      IF (INTERNAL%COUNTNUM .GT. 0) THEN
      CALL TRAVERSE(INTERNAL%COUNTNUM, 1)
      ELSE
      CALL TRAVERSE(ABS(INTERNAL%COUNTNUM), -1)
      END IF
      
      END SUBROUTINE

!------------------------------------------------------------------------ 
! ADDNODE SUBROUTINE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL
! GENERAL: INITIALIZES THE DOUBLY LINKED LIST AND CREATES NEW NODES 
! PRECONDITIONS: REQUIRES TYPE DEATHPOOL CREATED
! POSTCONDITIONS: CREATES A DOUBLY LINKED LIST BASED OFF THE RECORD INPUTS.
! WRITTEN: 10/10/2021 - 10/16/2021
!------------------------------------------------------------------------
      SUBROUTINE ADDNODE(NAMEFROMFILE, COUNTFROMFILE)
      CHARACTER(LEN=50), INTENT (IN):: NAMEFROMFILE
      INTEGER, INTENT (IN):: COUNTFROMFILE
      INTEGER :: ISTAT
      
      ALLOCATE(INTERNAL, STAT=ISTAT)
      IF(ISTAT .EQ. 0) THEN
      NULLIFY(INTERNAL%NEXT)
      NULLIFY(INTERNAL%PREVIOUS)
      INTERNAL%NAME=NAMEFROMFILE
      INTERNAL%COUNTNUM=COUNTFROMFILE
      IF (ASSOCIATED(HEAD))THEN
      TAIL%NEXT=>INTERNAL
      INTERNAL%PREVIOUS=>TAIL
      TAIL=>INTERNAL
      ELSE
      HEAD=>INTERNAL
      TAIL=>INTERNAL
      END IF 
      END IF
      END SUBROUTINE
!------------------------------------------------------------------------ 
! DELETENODE SUBROUTINE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL
! GENERAL: DELETES THE NODE CURRENTLY POINTED AT EVEN IF THE POINTER IS AT
!  THE CENTER, HEAD, OR TAIL.
! PRECONDITIONS: REQUIRES TYPE DEATHPOOL CREATED
! POSTCONDITIONS: NODE IS DELETED
! WRITTEN: 10/10/2021 - 10/16/2021
!------------------------------------------------------------------------
      SUBROUTINE DELETENODE()
      LOGICAL :: DISPLAY
      REAL :: U,J
      INTEGER :: I,N
      integer, allocatable :: seed(:)
      DISPLAY = .TRUE.
      
      IF (ASSOCIATED(BULLSEYE))THEN
      IF(ASSOCIATED(BULLSEYE%PREVIOUS)) THEN
      BULLSEYE%PREVIOUS%NEXT=>BULLSEYE%NEXT
      ELSE
      HEAD=>BULLSEYE%NEXT
      END IF
      IF (ASSOCIATED(BULLSEYE%NEXT)) THEN
      BULLSEYE%NEXT%PREVIOUS=>BULLSEYE%PREVIOUS
      ELSE
      TAIL=>BULLSEYE%PREVIOUS
      END IF

      IF(DISPLAY .EQV. .TRUE.)THEN
      I = BULLSEYE%COUNTNUM
      I = ABS(I)
      IF(I .GT. 25)THEN
      I = 22
      END IF
      END IF      
      
5     FORMAT(" ", 2A)
      WRITE(*,5,ADVANCE="NO")TRIM(BULLSEYE%NAME)," WAS"
	  CALL WAYSTODIE(DEATHARRAY,DISPLAY,I)
	  DISPLAY = .FALSE.
      WRITE(2,5,ADVANCE="NO")TRIM(BULLSEYE%NAME)," WAS"
      CALL WAYSTODIE(DEATHARRAY,DISPLAY,I)
      DISPLAY = .TRUE.
      DEALLOCATE(BULLSEYE)
      END IF
      
      END SUBROUTINE
!------------------------------------------------------------------------ 
! TRAVERSE SUBROUTINE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL
! GENERAL: TRAVERSES FORWARD AND BACKWARDS BASED OFF THE DIRECTION INT FLAG
!  AND DELETENODE SUBROUTINE IS CREATED
! PRECONDITIONS: DIRECTION MUST BE SET AND NUMBER OF TRAVERSALS
! POSTCONDITIONS: TRAVERSES THE LIST BUT DELETES THE NODE AFTER THE FIRST
!  TRAVERSAL THEN CONTINUES TO ITS FINAL COUNT. 
! WRITTEN: 10/10/2021 - 10/16/2021
!------------------------------------------------------------------------
      SUBROUTINE TRAVERSE(NUM, DIRECTION)
      INTEGER, INTENT(IN) :: NUM
      INTEGER, INTENT(IN) :: DIRECTION
      INTEGER :: I
      
      IF (DIRECTION .GT. 0) THEN
      DO I=1, NUM
      IF (.NOT. ASSOCIATED(INTERNAL%NEXT)) THEN
      INTERNAL =>HEAD
      ELSE
      INTERNAL=>INTERNAL%NEXT
      END IF
      IF (I .EQ. 1) THEN
      CALL DELETENODE()
      END IF
      END DO
      ELSE
      DO I=1, NUM
      IF (.NOT. ASSOCIATED(INTERNAL%PREVIOUS)) THEN
      INTERNAL =>TAIL
      ELSE
      INTERNAL=>INTERNAL%PREVIOUS
      END IF
      IF (I .EQ. 1) THEN
      CALL DELETENODE()
      END IF
      END DO
      END IF
      
      END SUBROUTINE
!------------------------------------------------------------------------ 
! WAYSTODIE SUBROUTINE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL
! GENERAL: HOLDS AN ARRAY WITH PRESET DEATHS FOR THE CONTESTANTS AND DISPLAYS THEM
! PRECONDITIONS: DEATHARRY NEEDS TO BE INITALIZED, A FLAG FOR DISPLAYING, AND THE
!  COUNT FROM THE NODES TO RECIEVE THE DEATH
! POSTCONDITIONS: OUTPUTS THE DEATH BASED ON THE COUNT
! WRITTEN: 10/14/2021 - 10/18/2021
!------------------------------------------------------------------------      
      SUBROUTINE WAYSTODIE(DEATHARRAY,DISPLAY,I)
      CHARACTER*30, DIMENSION(25), INTENT(OUT)::DEATHARRAY
      LOGICAL, INTENT(IN) :: DISPLAY
      INTEGER, INTENT(IN) :: I

      DEATHARRAY(1) = "STABBED"
      DEATHARRAY(2) = "BLUDGEONED"
      DEATHARRAY(3) = "DROWNED IN MOLASSES"
      DEATHARRAY(4) = "CRUSHED BY ROCKS"
      DEATHARRAY(5) = "PUSHED OFF TALL OBJECT"
      DEATHARRAY(6) = "STRANGLED"
      DEATHARRAY(7) = "DROWNED"
      DEATHARRAY(8) = "EXSANGUINATED"
      DEATHARRAY(9) = "SENT TO FIRING SQUAD"
      DEATHARRAY(10)= "TRAMPLED"
      DEATHARRAY(11)= "RAVAGED BY DOGS"
      DEATHARRAY(12)= "HIT WITH BASEBALL BAT"
      DEATHARRAY(13)= "DECAPITATED"
      DEATHARRAY(14)= "DRAWN AND QUARTERED"
      DEATHARRAY(15)= "DISMEMBERED"
      DEATHARRAY(16)= "BURIED ALIVE"
      DEATHARRAY(17)= "GARROTED"
      DEATHARRAY(18)= "POENA CULLEI"
      DEATHARRAY(19)= "IMPALED"
      DEATHARRAY(20)= "BEATEN TO DEATH BY MIDGETS"
      DEATHARRAY(21)= "FROZEN TO DEATH"
      DEATHARRAY(22)= "LEFT ON THE SIDE OFF THE ROAD"
      DEATHARRAY(23)= "BURNED AT THE STAKE FOR WITCHCRAFT"
      DEATHARRAY(24)= "STONED TO DEATH"
      DEATHARRAY(25)= "EDUCATED TO DEATH"
      
      IF(DISPLAY .EQV. .TRUE.)THEN
      WRITE(*,*)DEATHARRAY(I)
      ELSE
      WRITE(2,*)DEATHARRAY(I)
      END IF
      
      END SUBROUTINE
!------------------------------------------------------------------------ 
! WAYSTODIE SUBROUTINE
! BY ANDREW SPATE, KELLI HUFF, ANDREW BISSELL
! GENERAL: 
! PRECONDITIONS: 
! POSTCONDITIONS:  
! WRITTEN: 10/10/2021 - 10/16/2021
!------------------------------------------------------------------------ 
      SUBROUTINE INIT_RANDOM_SEED()
      INTEGER :: I,N,CLK
      INTEGER, DIMENSION(:),ALLOCATABLE :: SEED
      
      CALL RANDOM_SEED(SIZE = N)
      ALLOCATE(SEED(N))
      
      SEED = CLK +37 * (/(I-1,I=1,N)/)
      CALL RANDOM_SEED(PUT = SEED)

      DEALLOCATE(SEED)
      END SUBROUTINE
!------------------------------------------------------------------------
      END MODULE
!------------------------------------------------------------------------
!************************************************************************
!------------------------------------------------------------------------
! MAIN
! THE LINKED LIST PROGRAM
! BY ANDREW SPATE, ANDREW BISSELL, KELLI HUFF
! GROUP #2
! GENERAL: HOUSES THE MAIN PROGRAM
! PRECONDITIONS: MODULE IO_FILE AND MODULE LINKED_LIST REQUIRED
! POSTCONDITIONS: TAKES AN INPUT FILE OF DATA AND CREATES A DOUBLY LINKED LIST
!  WITH THE DATA AND THEN STARTS TO TRAVERSE THE LIST KILLING THE PEOPLE BASED
!  OFF THE PERSONS COUNT.
! WRITTEN: 10/10/2021 - 10/16/2021
!------------------------------------------------------------------------
!************************************************************************
!------------------------------------------------------------------------  
      PROGRAM G2P7
      USE IO_FILE
      USE LINKED_LIST
      
      IMPLICIT NONE

      LOGICAL :: BADDATA
      INTEGER, DIMENSION(30) :: COUNTSFROMFILE
      CHARACTER(LEN=50), DIMENSION(30):: NAMESFROMFILE
           
      NAMESFROMFILE=' '
      COUNTSFROMFILE=0
      BADDATA= .FALSE.
      CALL OPEN_MASTER(COUNTSFROMFILE, NAMESFROMFILE, BADDATA)
      IF (BADDATA .EQV. .FALSE.) THEN
      CALL LINKED_MASTER(NAMESFROMFILE, COUNTSFROMFILE)
      END IF

      CLOSE(1)
      CLOSE(2)
      END PROGRAM
