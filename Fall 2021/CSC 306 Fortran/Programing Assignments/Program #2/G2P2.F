c     Andrew Spate, Andrew Bissell, Justin Gunderson
c     Group 2
c     Fortran 306
c     Average PART 2 Program
      program G2P2
      implicit none
      character*25 STNAME
      real TEMP, AVG
      REAL SCORE(10)
C      SCORE=-1
      INTEGER I, COUNTER
      I=1
      TEMP=0.0
      COUNTER=0
c     input Test score format
10    FORMAT(' ',A18,X, F6.2)
11    FORMAT(' ',A17,X, I7)
27    FORMAT(' ',(10(F6.2,2X)))
28    FORMAT(' ',(A7,I2))
c     IMPUT FOR NAME  
      write(*,*)"Enter the student's name:  "
      read(*,*) STNAME
c     LOOP #1 
C     DATA INPUT LOOP TO LOAD ARRAY
      DO WHILE ((TEMP .GE. 0) .AND. (TEMP .LE. 100) .AND. 
     +(COUNTER .LT. 10))
        WRITE(*,28)'SCORE #',COUNTER+1
      	WRITE(*,*)'ENTER A TEST SCORE (<0 OR > TO END; 10 SCORES MAX)'
      	READ(*,*)TEMP
C     Test inputted Data for validity
      	IF ((TEMP .GE. 0.0) .AND. (TEMP .LE. 100)) THEN
c     TEMP IS PLACED INTO THE ARRAY
            COUNTER=COUNTER+1
			SCORE(COUNTER)=REAL(TEMP)
		ELSE
			TEMP=-1.0
		END IF
      END DO
      IF (COUNTER .GT. 1) THEN
       WRITE(*,*)TRIM(STNAME),"'s GRADEBOOK:"
C      PRINT AND SUM SCORES
       TEMP=0.0
c     Loop #2       
       DO i=1,COUNTER
        TEMP=TEMP+SCORE(i)
       END DO
C     Loop#3       
       PRINT 27,(SCORE(I),I=1,COUNTER)
C     Nicely formatted output       
       WRITE(*,*)TRIM(STNAME),"'s CALCULATIONS:"
       WRITE(*,10)'Sum= ',TEMP
       WRITE(*,11)' Count= ',COUNTER
c     average math
       AVG=TEMP/COUNTER
c     write numbers to the screen
       WRITE(*,10)'Average= ',AVG      
      ELSE
       WRITE(*,*)"NO SCORES ENTERED"
      END IF
      END