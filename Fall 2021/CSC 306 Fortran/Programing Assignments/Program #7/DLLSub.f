!-------------------------REMOVE NODE FROM DLL-------------------------     
      SUBROUTINE KILL_PERSON(NODE)
      
!-----------------------------MAIN PROGRAM-----------------------------
      PROGRAM DLL
      IMPLICIT NONE
      
!------------------------NODE DERIVED DATA TYPE------------------------      
      TYPE :: NODE
      CHARACTER :: NAME*30
      INTEGER :: COUNT
      TYPE(NODE),POINTER :: NEXT,PREV
      END TYPE
      
      TYPE(NODE),POINTER :: HEAD, TAIL, P
      INTEGER I  
      