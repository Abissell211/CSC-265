        TTL     "Lab 9: ASCII Converter"

********************************************************************
* 1) HEADER block - overall info about the program

* Project name:   Lab9
* Author(s):      Andrew Bissell
* Date:           04/05/2021
* Description:
*   This program takes a user inputed ASCII character that can be
*   displayed, shows the user the inputted character and then 
*   converts it to the proper ASCII character using
*   Character to ASCII Value Subroutine. The program will keep taking
*   user inputs till the ESC key is pressed. 
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
        BGE     Display ; go process the character.
        
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
************************** MSB Processing *************************
        TAB
        LSRA               ; Logical Shift Right ACC A 1st time 
        LSRA               ;                           2nd time
        LSRA               ;                           3rd time
        LSRA               ;                           4th time
        
        ORA     #$30
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA.

************************** LSB Processing **************************       
        TBA             ; Transfer original value of ACCA from ACCB back to ACCA.
        ANDA    #$0F
        
        CMPA    #$0A    ; If the value is equal to $A, go process the A.
        BGE     GrtA
        
        ORA     #$30
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA. 
        BRA     Fin     ; Skip to the end of Subroutine.
        
GrtA    ADDA    AtoF
        JSR     OUTA
        
Fin     RTS             ; Returns back to program 
;                         (MSB and LSB already displayed)
********************************************************************
* 4) DATA section - variables & other data used by program         *
********************************************************************

;    a) constant data definitions (FCB,FDB,FCC)...

GREET   FCB     "Welcome to the CHAR to ASCII Value Converter!",CR,EOT
PROMP   FCB     "Enter a Character (ESC to Exit): ",EOT
WARN    FCB     "ERROR!!! NON-PRINTABLE CHAR ENTERED!",CR,EOT
DSPLYC  FCB     "The character entered was: ",EOT
DSPLYH  FCB     "The character's ASCII value is: $",EOT
GDBY    FCB     "Program Terminated, Have a good Day!",CR,EOT

NEWLN   FCB     "",CR,EOT
AtoF    FCB     $37          ;
*********************************************************************
; End of assembly source code
        END