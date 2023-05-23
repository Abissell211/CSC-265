c234567
      PROGRAM information
      IMPLICIT NONE
      INTEGER selmain, selcolumn, seldata
      LOGICAL qmain, qcolumn, qdata
      qmain=.FALSE.
      PRINT*,'This program tells you about Fortran code and syntax.'
      PRINT*,'Please choose from the selection:'
      PRINT*,'Selection 1: Five column sections of Fortran.'
      PRINT*,'Selection 2: Data declaration.'
      READ(*,*)selmain
      DO WHILE(qmain .NEQV. .TRUE.)
      SELECT CASE(selmain)
         CASE(1)
            PRINT*,'Select a number 1-72, 81 to quit.'
            READ(*,*)selcolumn
            qcolumn=.FALSE.
            DO WHILE(qcolumn .NEQV. .TRUE.)
               SELECT CASE(selcolumn)
                  CASE(1)
                  	PRINT*,"Column 1: Comment section using a 'c'."
                  	selcolumn=0
              	 CASE(2:5)
                  	PRINT*,'Columns 2-5: Statement label field.'
                  	selcolumn=0
              	 CASE(6)
                	PRINT*,'Column 6: Continuation field.'
              	    selcolumn=0
               	 CASE(7:72)
              	    PRINT*,'Columns 7-72: Statement field.'
                  	selcolumn=0
               	 CASE(73:80)
                  	PRINT*,'Columns 73-80: Card number field.'
                  	selcolumn=0
               	 CASE(81)
                  	qcolumn=.TRUE.
               	 CASE DEFAULT
                  	PRINT*,'Select a number 1-72, 81 to quit.'
                  	READ(*,*)selcolumn
               ENDSELECT
            ENDDO
            selmain=0
         CASE(2)
            PRINT*,'Selection 1: Character.'
            PRINT*,'Selection 2: Integer.'
            PRINT*,'Selection 3: Logical.'
            PRINT*,'Selection 4: Real.'
            PRINT*,'Selection 5: Quit'
            READ(*,*)seldata
            qdata=.FALSE.
            DO WHILE(qdata .NEQV. .TRUE.)
               SELECT CASE(seldata)
                  CASE(1)
                     PRINT*,'Declaration 1: CHARACTER*(#) var_name'
                     PRINT*,'Declaration 2: CHARACTER var_name*(#)'
                     PRINT*,'Declaration 3: CHARACTER(len=#) var_name'
                     PRINT*,'Place Holder: rAw'
                     PRINT*,'r=repeat,A=place holder,w=width'
                     seldata=0
                  CASE(2)
                     PRINT*,'Declaration: INTEGER var_name'
                     PRINT*,'Place Holder: rIw'
                     PRINT*,'r=repeat,L=place holder,w=width'
                     seldata=0
                  CASE(3)
                     PRINT*,'Declaration: LOGICAL var_name'
                     PRINT*,'Place Holder: rLw'
                     PRINT*,'r=repeat,L=place holder,w=width.'
                     seldata=0
                  CASE(4)
                     PRINT*,'Declaration: REAL var_name'
                     PRINT*,'Place Holder: rEw.d,rFw.d'
                     PRINT*,'r=repeat,EorF=PH,w=width,d=decimal'
                     seldata=0
                  CASE(5)
                     qdata=.TRUE.
                  CASE DEFAULT
                     PRINT*,'Selection 1: Character.'
            		 PRINT*,'Selection 2: Integer.'
            		 PRINT*,'Selection 3: Logical.'
            		 PRINT*,'Selection 4: Real.'
            		 PRINT*,'Selection 5: Quit'
            		 READ(*,*)seldata
               ENDSELECT
            ENDDO
            selmain=0
         CASE DEFAULT
            PRINT*,'Please choose from the selection:'
            PRINT*,'Selection 1: Five column sections of Fortran.'
            PRINT*,'Selection 2: Data declaration.'
            READ(*,*)selmain         
         ENDSELECT
         ENDDO
         END 