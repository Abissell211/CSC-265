        TTL     "Lab 8 - Demo Program"

******************************************************************
* 1) HEADER block - overall info about the program

* Project name: Lab8Mod.asm
* Author(s):    Andrew D. Bissell 
* Date:         2021-03-25
*
* Description:
*   The program displays a greeting message, then repeatedly loops,  
*   inputting a character typed by the user, then outputing the 
*   ASCII characters before and after the input character.
* 
*   Entering the Escape character terminates the program back to
*   the BUFFALO monitor prompt.
*
*   If "C" is the input character, the output is in the format below:
*
*       : C-1=B, C+1=D
*       : <ESC>
*       >
*
*   NOTE:  Assemble using  CAS11 -cls lab8demo.asm
*
******************************************************************

******************************************************************
* 2) EQUATE section - define symbolic names for various values

;    a) constants...

* Define ASCII character constants
COLON    EQU   ':'      ; ASCII Colon (for prompt)
COMMA    EQU   $2C      ; ASCII Comma character
SPACE    EQU   $20      ; ASCII Space character
CR       EQU   $0D      ; ASCII Carriage Return
ESC      EQU   $1B      ; ASCII ESCape character
EOT      EQU   $04      ; ASCII End Of Transmission char
BELL     EQU   $07      ; ASCII code to ring ouput Bell.

;    b) "system" objects (I/O registers, monitor routines, etc.)

* BUFFALO utility routine entry points
OUTSTRG  EQU   $FFC7    ; string output routine
INCHAR   EQU   $FFCD    ; character input routine
OUTA     EQU   $FFB8    ; character output routine

;    c) memory map equates

CODE     EQU   $2000    ; 32K RAM (U5) on CME11E9-EVBU board

******************************************************************

******************************************************************
* 3) CODE section - actual program code

         ORG   CODE     ; tell assembler where to begin object code
        
; main program body.
Main     EQU   *
         LDX   #GREET   ; point X to greeting string
         JSR   OUTSTRG  ; call BUFFALO rtn to output it
        
PROMPT   LDAA  #COLON   ; Output colon prompt character
         JSR   OUTA
        
INPUT    JSR   INCHAR   ; get user input char     
         CMPA  #ESC     ; is it ESCape char?
         BEQ   EXIT     ; exit program if so
         
* Program changes to detect non-printing input char.
         CMPA  #'!      ; If char is exclamation or greater,
         BGE   DISPLAY  ; go process the character
         
         LDAA  #BELL    ; otherwise ring the BELL.
         JSR   OUTA
         
         BRA   INPUT    ; then just go get another input char. 
        
DISPLAY  TAB            ; save a copy in B
        
        ; NOTE: Input character is last character showing on screen.
        
         LDAA  #'-      ; output "-1=" 
         BSR   OneEQ    
        
         TBA            ; recall input char to A
         DECA           ; Get previous ASCII char
         JSR   OUTA     ; and output it.
        
         ldaa  #COMMA   ; Output Comma 
         JSR   OUTA        
         LDAA  #SPACE   ; Output space 
         JSR   OUTA
        
         TBA            ; recall input char to A again
         JSR   OUTA     ; and output it
        
         LDAA  #'+      ; output "+1=" 
         BSR   OneEQ   
        
         TBA            ; recall input char to A
         INCA           ; Get char following input char
         JSR   OUTA     ; and output that
        
         LDAA  #CR      ; output ASCII CR to advance to next line
         JSR   OUTA    
        
         BRA   PROMPT   ; loop back to prompt for next char
        
EXIT     SWI            ; End prog & return to BUFFALO monitor

         PAGE
; place various subroutines next

* This subroutine outputs the char in A followed by "1=".
* It is used to output "+1=" and "-1=" strings needed to
* format the output to the user.
*
*   Register A - on input, contains an ASCII character which
*               is output before the "1=" string.

OneEQ    EQU   *
         JSR   OUTA     ; output existing char in A
        
         LDAA  #'1      ; output '1'
         JSR   OUTA
         LDAA  #'=      ; output '='
         JSR   OUTA
        
         RTS            ; and return to caller after BSR
        
******************************************************************

******************************************************************
* 4) DATA section - variables & other data used by program

;    a) Constant data definitions (FCB,FDB,FCC)...
;       (Constants may be defined following program code area.)

* define program greeting message

GREET    FCB   "Welcome from Andrew Bissell to the Lab8Mod",CR
         FCB   "If an input is less than the '!' ASCII CHAR a warning bell will chime!.",CR
         FCB   "Press ESCape to exit, any other char to [display].",CR
         FCB   EOT        

******************************************************************

; end of assembly source code
         END
