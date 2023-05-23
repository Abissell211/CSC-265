        TTL     "Lab 9"

********************************************************************
* 1) HEADER block - overall info about the program

* Project name:   Lab9
* Author(s):      Andrew Bissell
* Date:           04/01/2021
* Description:
*   This program 
*
********************************************************************
* 2) EQUATE section - define symbolic names for various values     *
********************************************************************

;    a) constants...
CR      EQU     $0D     ;ASCII Carriage Return (To create a newline on output)
EOT     EQU     $04     ;ASCII for End Of Transmission (Use with OUTSTRG)
ESC     EQU     $1B     ;ASCII for Escape (For quitting the program)
BELL    EQU     $07     ;ASCII code to ring ouput Bell. (For ERRORS in input)

* BUFFALO utility routine entry points
OUTA    EQU     $FFB8   ;BUFFALO rtn to output char in acc A
OUTSTRG EQU     $FFC7   ;BUFFALO OUTSTRING Subroutine (Makes use of EOT constant)
INCHAR  EQU     $FFCD   ;BUFFALO INCHAR Subroutine

;    c) memory map equates

RWDATA  EQU     $0000   ;Where to place read/write(RAM) variables
CODE    EQU     $2000   ;Where to start placing program object code
                        ;32K RAM (U5) on CME11E9-EVBU board

********************************************************************
* 3) CODE section - Main program code                              *
********************************************************************

        ORG     CODE    ; tell assembler where to begin object code
        
Main    EQU     *       ;Define label for start of Main program.

        LDX     #GREET  
        JSR     OUTSTRG ; Displays the welcome message.
;                         "Welcome to the CHAR to ASCII Value Converter!"
        
Prompt  LDX     #PROMP
        JSR     OUTSTRG ; Displays the prompt message.
;                         "Enter a Character (ESC to Exit): "
        
        JSR     INCHAR  ; Gets the users inputted CHAR.
        CMPA    #ESC    ; Checks if the user input was an ESC.
        BEQ     Exit    ; If the input is ESC Exit the program.
        
******** Program checks to detect non-printing input char. ********
        CMPA    #'!     ; If CHAR is exclamation or greater,
        BGE     Display ; go process the character
        
        LDAA    #BELL   ; If CHAR is not warn user with bell tone.
        JSR     OUTA
        LDX     #WARN  
        JSR     OUTSTRG ; Displays the warning message.
;                         "ERROR!!! NON-PRINTABLE CHAR ENTERED!"
         
        BRA     Prompt  ; Return to prompt to get a new user input.
*******************************************************************   
        
Display TAB             ; Transfers contents of ACCA to ACCB
        
        LDX     #DSPLYC
        JSR     OUTSTRG ; Displays the user character message.
;                         "The character entered was: "
        TBA             ; Puts B into A
        JSR     OUTA    ; Displays the inputted CHAR to user.
        
        LDX     #DSPLYH
        JSR     OUTSTRG ; Displays the user character ASCII value message.
;                         "The character's ASCII value is: "        
        
        JSR     CHA2ASC ; Jump to Character to ASCII Value Subroutine 
;                         (Will display the ASCII value to user in subroutine)
        
        LDX     #NEWLN
        JSR     OUTSTRG ; Creates a newline to clean up display for user.
        BRA     Prompt  ; Returns back to the prompt to get new user input.
      
Exit    LDX     #NEWLN
        JSR     OUTSTRG ; Creates a newline to clean up display for user.
        LDX     #GDBY
        JSR     OUTSTRG ; Displays the Goodbye message.
;                         "Program Terminated Have a good Day!"         
      
        SWI             ; return to BUFFALO monitor on HC11EVB
        
*******************************************************************
*  Character to ASCII Value Subroutine -CHA2ASC-                  *
*******************************************************************
* This Subroutine takes a user inputed CHAR and converts it into
*  it's proper ASCII Hex Value.
* Parameters: The Input CHAR in ACCA
*             Computes MSB hex value for ASCII CHAR and prints MSB,
*              then LSB and prints LSB.
*             CCR will be changed in here

CHA2ASC EQU     *       ; Start of subroutine.

************************** MSB Processing **************************
        TBA
        JSR     LSRBYTE ; Jump to Logical Shift Right One Byte.
        
        STAA    HEXVAL  ; Store the new ACCA value to variable to use BSET ($0X)
        BSET    HEXVAL $30 ; Sets the MSB to a three.                         ($3X)
        LDAA    HEXVAL  ; Stores the final MSB value to ACCA.
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA.

************************** LSB Processing **************************        
        TBA             ; Transfer original value of ACCA from ACCB back to ACCA.
        STAA    HEXVAL  ; Store the value of ACCA to the variable to use BSET/BCLR.
        BCLR    HEXVAL $F0 ; Clears the MSB.                                  ($0X)
        LDAA    HEXVAL  ; Loads ACCA with the new value. 
        
        CMPA    #$0A    ; If the value is equal to $A, go process the A.
        BEQ     LetA
        
        CMPA    #$0B    ; If the value is equal to $B, go process the B.
        BEQ     LetB

        CMPA    #$0C    ; If the value is equal to $C, go process the C.
        BEQ     LetC
        
        CMPA    #$0D    ; If the value is equal to $D, go process the D.
        BEQ     LetD
        
        CMPA    #$0E    ; If the value is equal to $E, go process the E.
        BEQ     LetE
        
        CMPA    #$0F    ; If the value is equal to $F, go process the F.
        BEQ     LetF        
        
        BSET    HEXVAL $30 ; else continue process since: X != A <-> F.
        LDAA    HEXVAL  ; Reload ACCA with the final LSB value.
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA. 
        BRA     Fin     ; Skip to the end of Subroutine.
        
LetA    LDAA    #$41    ; Directly load an A into the LSB.
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA.
        BRA     Fin     ; Skip to the end of Subroutine.

LetB    LDAA    #$42    ; Directly load an B into the LSB.
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA.
        BRA     Fin     ; Skip to the end of Subroutine.
        
LetC    LDAA    #$43    ; Directly load an C into the LSB.
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA.
        BRA     Fin     ; Skip to the end of Subroutine.
        
LetD    LDAA    #$44    ; Directly load an D into the LSB.
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA.
        BRA     Fin     ; Skip to the end of Subroutine.
        
LetE    LDAA    #$45    ; Directly load an E into the LSB.
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA.
        BRA     Fin     ; Skip to the end of Subroutine.
     
LetF    LDAA    #$46    ; Directly load an F into the LSB.
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA.
        
Fin     RTS             ; Returns back to program 
;                         (MSB and LSB already displayed)

*******************************************************************
*  Logical Shift Right One Byte -LSRBYTE-                         *
*******************************************************************
* This Subroutine shifts the entire MSB (of a two Byte value) to 
*  the LSB with the new MSB equal to zero.
* Parameters: The Input CHAR in ACCA
*             Moves MSB to the LSB, MSB now equal zero
*             CCR will be changed in here

LSRBYTE EQU     *

        LSRA               ; Logical Shift Right ACC A 1st time 
        LSRA               ;                           2nd time
        LSRA               ;                           3rd time
        LSRA               ;                           4th time
        
        RTS                ; Return
        
********************************************************************
* 4) DATA section - variables & other data used by program         *
********************************************************************

;    a) constant data definitions (FCB,FDB,FCC)...

GREET   FCB     "Welcome to the CHAR to ASCII Value Converter!",CR,EOT
PROMP   FCB     "Enter a Character (ESC to Exit): ",EOT
WARN    FCB     "ERROR!!! NON-PRINTABLE CHAR ENTERED!",CR,EOT
DSPLYC  FCB     "The character entered was: ",EOT
DSPLYH  FCB     "The character's ASCII value is: $",EOT
GDBY    FCB     "Program Terminated Have a good Day!",CR,EOT

NEWLN   FCB     "",CR,EOT

;    b) variable data allocations (RMB)...

        ORG     RWDATA
       
HEXVAL  RMB     1          ; Variable used in conjunction with ACCA to 
;                            display the proper ASCII Value, also to use
;                            BSET and BCLR.

*********************************************************************

; End of assembly source code
        END