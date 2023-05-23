c234567
c Following program initalizes an array and prints the array.
c Since the print is list-directed, each value will apear one per line.
      PROGRAM Implied
      INTEGER i,j
      INTEGER, DIMENSION(20)::ARRAY = [((i*j,i=1,5),j=1,4)]
      do i = 1,20
         PRINT *,ARRAY(i)
      end do
      end