c     Andrew Spate, Andrew Bissell, Justin Gunderson
c     Fortran 306
c     Average Program
      program Average
      implicit none
      character name
      real sum, score
      integer i, counter
c     input Test score format
10    FORMAT(' ',A,X, F6.2)
c     input user name format

c init for incrimenter and accumulator
	  
      sum=0.0
      counter=0
      write(*,*)"Enter the student's name:  "
      read(*,*) name
      write(*,*)"How many scores will we be averaging?  "
      read(*,*)counter
c Loop Begin
      DO 69 i=1, counter
c Print statement to prompt for input 
      score=-1
      write(*,*)'Enter the test score: '
		DO WHILE ((score .LT. 0) .OR. (score .GT. 100))
c Read input from Keyboard
      		read(*,*)score
c Test inputted Data for validity
      		IF ((score .LT. 0.0) .OR. (score .GT. 100)) THEN
c Reprompt if bad data, then loops back for new data
			   write(*,*)'Enter a valid score between 0 and 100 (inclusive)'
			END IF
		END DO
c increment sum and counter
      	sum=sum+score
69    CONTINUE     
c output statements
      write(*,*)name,"'s total and average" 
      write(*,10)'Sum=   ',sum      
c average math
      sum=sum/counter
c write numbers to the screen
      write(*,10)'Average= ',sum
      end