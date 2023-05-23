c234567
      PROGRAM ArrayAllocate
      IMPLICIT NONE
      INTEGER CHOICE,i,slot,dat
      CHARACTER*3 clear
      LOGICAL quit
      INTEGER, DIMENSION(10)::A=[(i,i=1,10)]
      WRITE(*,*)'Selection 1: Read/Write'
      WRITE(*,*)'Selection 2: Print Array'
      WRITE(*,*)'Selection 3: Clear Array'
      WRITE(*,*)'Selection 4: Quit'
      READ(*,*)choice
      quit = .FALSE.
      DO WHILE(quit .NEQV. .TRUE.)
      SELECT CASE(choice)
         CASE(1)
            WRITE(*,*)'Please enter array slot location'
            READ(*,*)slot
            WRITE(*,*)'Please enter data for that slot'
            READ(*,*)dat
            A(slot)=dat
            choice=0
         CASE(2)
            DO i=1,10
            PRINT *,A(i)
            ENDDO
            choice=0
         CASE(3)
            WRITE(*,*)'Do you want to clear array?'
            READ(*,*)clear
            IF(clear .EQ. 'yes')THEN
               A=[(0,i=1,10)]
            ENDIF
            choice=0
         CASE(4)
            quit=.TRUE.
            WRITE(*,*)'PROGRAM QUIT: Have a nice day!'
         CASE DEFAULT
     		WRITE(*,*)'Selection 1: Read/Write'
     		WRITE(*,*)'Selection 2: Print Array'
      		WRITE(*,*)'Selection 3: Clear Array'
      		WRITE(*,*)'Selection 4: Quit'
      		READ(*,*)choice
      END SELECT
      ENDDO
      END