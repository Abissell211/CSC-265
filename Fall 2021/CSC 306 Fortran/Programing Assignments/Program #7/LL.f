      PROGRAM DOUBLY_LINKED_LIST
      IMPLICIT NONE
!------------------------NODE DERIVED DATA TYPE------------------------      
      TYPE :: NODE
      CHARACTER :: NAME*30
      INTEGER :: COUNT
      TYPE(NODE),POINTER :: NEXT,PREV
      END TYPE
!---------------------------DATA DECLARATIONS--------------------------      
      TYPE(NODE),POINTER :: HEAD, TAIL, P
      INTEGER I      
!-----------------------START DOUBLY LINKED LIST-----------------------      
      INTEGER ISTAT
      NULLIFY(HEAD,TAIL)
      ALLOCATE(P,STAT=ISTAT)
      IF(ISTAT .EQ. 0)THEN
      NULLIFY(P%NEXT)
      NULLIFY(P%PREV)
      END IF
      
!----------------------------ADDING FIRST NODE-------------------------      
      IF(ASSOCIATED(HEAD))THEN
      TAIL%NEXT => P
      P%PREV => TAIL
      TAIL => P
      ELSE
      HEAD => P
      TAIL => P
      END IF
      
!----------ADDING THE REST OF NODES FOR 25 SELECTIONS OF DATA----------       
      DO I = 1, 24
      IF(ASSOCIATED(HEAD))THEN
      HEAD%PREV => P
      P%NEXT => HEAD
      HEAD => P
      END IF
      END DO
      
!----------------------TRAVERSE FORWARD AND ADD DATA TO NODES------------------
      P => HEAD
      DO WHILE(ASSOCIATED(P))
                 !!!---OUR DATA FROM FILE WILL GO HERE---!!!
      P => P%NEXT
      END DO      
      
      END PROGRAM DOUBLY_LINKED_LIST
      
