c234567
c Use an implied do loop for both i and j
      PROGRAM Implied
      INTEGER i,j
      INTEGER, DIMENSION(20)::ARRAY = [((i*j,i=1,5),j=1,4)]
10    FORMAT(' ',20(I3,2X))
      PRINT 10,((ARRAY((j-1)*5+i),i=1,5),j=1,4)
      end