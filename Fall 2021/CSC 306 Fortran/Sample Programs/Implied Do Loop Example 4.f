c234567
c Use a do loop for j and use an implied do for i
      PROGRAM Implied
      INTEGER i,j
      INTEGER, DIMENSION(20)::ARRAY = [((i*j,i=1,5),j=1,4)]
10    FORMAT(' ',20(I3,2X))
	  do j=1,4
      PRINT 10,(ARRAY((j-1)*5+i),i=1,5)
      end do
      end