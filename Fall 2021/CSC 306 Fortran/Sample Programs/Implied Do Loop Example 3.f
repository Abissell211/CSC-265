c234567
c Remove the do loop and use an implied do loop for the print with the format.
      PROGRAM Implied
      INTEGER i,j
      INTEGER, DIMENSION(20)::ARRAY = [((i*j,i=1,5),j=1,4)]
10    FORMAT(' ',20(I3,2X))
      PRINT 10,(ARRAY(i),i=1,20)
      end do
      end