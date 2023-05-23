        TTL     "Lab 06 Done in a Different Way!"

******************************************************************
* 1) HEADER block - overall info about the program

* Project name: Lab 06
* Author(s): Andrew D. Bissell
* Date: 03/24/2021
* Description:
*   This program will take a CHAR input from the user and display
*   it back with the previous and the next CHAR in the following
*   format <CHAR>-1=<previous CHAR>, <CHAR>+1=<next CHAR>
*   Example: (user input)B B-1=A, B+1=C
*   To exit hit the ESC key
*
******************************************************************

******************************************************************
* 2) EQUATE section - define symbolic names for various values

;    a) constants...
CR      EQU     $0D     ;ASCII Carriage Return
EOT     EQU     $04     ;ASCII for End Of Transmission
ESC     EQU     $1B     ;ASCII for Escape

* BUFFALO utility routine entry points ;Subroutines
OUTA    EQU     $FFB8   ;BUFFALO rtn to output char in acc A
OUTSTRG EQU     $FFC7   ;BUFFALO OUTSTRING Subroutine
INCHAR  EQU     $FFCD   ;BUFFALO INCHAR Subroutine

;    c) memory map equates (memory locations to run the program)

RWDATA  EQU     $0000   ;Where to place read/write(RAM) variables
CODE    EQU     $2000   ;Where to start placing program object code
                        ;32K RAM (U5) on CME11E9-EVBU board

******************************************************************

******************************************************************
* 3) CODE section - actual program code

        ORG     CODE    ; tell assembler where to begin object code
        
; main program body follows
Main    EQU     *       ;Define label for start of Main program.
        LDAA    #':'    ;Load ACCA with the ASCII code for :
        JSR     OUTA    ;Displays the contents of ACCA (:)
        JSR     INCHAR  ;Wait for user inputed CHAR
        CMPA    #ESC    ;Check for ESC press
        BEQ     Stop    ;Branches to the SWI
;       JSR     OUTA    ;Display the CHAR back
        LDX     #Msg1   ;Loads the location of Msg1 in X
        STAA    0,X     ;Store the user input as the first CHAR
        STAA    7,X     ;Store the user input as the seventh CHAR
        
Prev    DECA            ;To find the previous CHAR
        STAA    4,X     ;Store the previous as the fourth CHAR
        
Next    INCA            ;INCA to the original CHAR
        INCA            ;INCA to the next CHAR
        STAA    11,X    ;Store the next CHAR as the eleventh CHAR
        
        JSR     OUTSTRG
        BRA     Main    ;Branches to start of Program
        
Stop    SWI             ;return to BUFFALO monitor on HC11EVB
        
******************************************************************

******************************************************************
* 4) DATA section - variables & other data used by program

;    a) constant data definitions (FCB,FDB,FCC)...

Msg1    FCC     "I-1=P, I+1=N"
        FCB     CR,EOT

;    b) variable data allocations (RMB)...

* Uncomment the following ORG statement to cause the assembler to
* position the variable data somewhere specific in RAM, otherwise
* the data storage will follow the constant data above.
;       ORG     RWDATA

ByteVar RMB     1       ;a 1-byte variable
WordVar RMB     2       ;a 2-byte (1 word) variable

******************************************************************

; End of assembly source code
        END