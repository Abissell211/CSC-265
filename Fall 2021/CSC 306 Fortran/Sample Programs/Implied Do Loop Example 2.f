c234567
c Add a FORMAT statement with a repeat for the integer and spacing.
c Since the print is inside a do loop, each value will appear one per line.
c The print is executed 20 times.
      PROGRAM Implied
      INTEGER i,j
      INTEGER, DIMENSION(20)::ARRAY = [((i*j,i=1,5),j=1,4)]
10    FORMAT(' ',20(I3,2X))
      do i = 1,20
         PRINT 10,ARRAY(i)
      end do
      end