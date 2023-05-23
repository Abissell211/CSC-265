c234567
      PROGRAM read_write_file
      IMPLICIT NONE
      INTEGER::status
      LOGICAL::exists
c	  	initalize logical varable to false value
      LOGICAL::files_open=.FALSE.
      CHARACTER(len=20)::file_name
      CHARACTER(len=80)::line
      WRITE(*,*)'Enter input file name'
c     	including format into the read clause list
      READ(*,'(A)')file_name
c     	check(inquire) if the file exists
      INQUIRE(File=file_name,EXIST=exists)
      IF(exists)THEN
c       open unit one, with the file name, status old since it already exists and IOSTAT with have status.
         OPEN(UNIT=1,FILE=file_name,STATUS='OLD',IOSTAT=status)
c     	check if there was any error when file was opened, if it is equal to zero we proceed.
         IF(status .EQ. 0)THEN
            WRITE(*,*)'Enter output file name:'
            READ(*,'(A)')file_name
            INQUIRE(FILE=file_name,EXIST=exists)
            IF(.NOT. exists)THEN
               OPEN(UNIT=2,FILE=file_name,STATUS='NEW',IOSTAT=status)
               IF(status .EQ. 0)THEN
c      	this means the Input and output files have opened.
                  files_open=.TRUE.
               ELSE
c       had an error opening the output file.
			      WRITE(*,*)'Error opening output file',file_name,'.'
			   ENDIF
			ELSE
c       the output file existed and we don't want to overide it.
			   WRITE(*,*)'Output file',file_name,'exists.'
			ENDIF
         ELSE
c       we had an error opening the input file
            WRITE(*,*)'Error opening input file ',file_name,'.'
         ENDIF
c       if the output file was not opened (possible due to error) close the input file.
         IF(.NOT. files_open)THEN
            CLOSE(1)
         ENDIF
      ELSE
c       the input file did not exist.
         WRITE(*,*)'Input file ',file_name,'does not exist.'
      ENDIF
c       if both input and output open successfully
      IF(files_open)THEN
c       perliminary read for the DO WHILE loop
         READ(1,'(A)',iostat=status)line
c       as long as we read something and its a zero we did not get an error.
         DO WHILE(status .EQ. 0)
            WRITE(2,'(A)')line
            READ(1,'(A)',iostat=status)line
         END DO
c       close input file (1) and close output file (2)
         CLOSE(1)
         CLOSE(2)
      ENDIF
      END PROGRAM read_write_file