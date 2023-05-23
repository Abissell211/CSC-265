        TTL     "HW03 - Username Creator"

****************************************************************************
* 1) HEADER block - overall info about the program                         *
****************************************************************************
* Project name:   UsernameCreator
* Author(s):      Andrew D. Bissell
* Date:           04/07/2021
* Description:
*   This program allows a user to create a password that is 6 - 20 characters
*   long with letters a - z lower case and capital, and with periods only. 
*   The user will have to input the username twice to check if it matches if
*   it does not follow criteria or the first username does not match the 
*   second the user will have to restart from the beginning. If the usernames
*   match the user will get a congratulations message and the username displayed.
****************************************************************************
* 2) EQUATE section - define symbolic names for various values             *
****************************************************************************
;    a) constants...
CR      EQU     $0D       ;ASCII Carriage Return (To create a newline on output)
EOT     EQU     $04       ;ASCII for End Of Transmission (Use with OUTSTRG)
ESC     EQU     $1B       ;ASCII for Escape (For quitting the program)

;    b) "system" objects (I/O registers, monitor routines, etc.)
* BUFFALO utility routine entry points
OUTA     EQU     $FFB8    ;BUFFALO rtn to output char in acc A
OUTSTRG  EQU     $FFC7    ;BUFFALO rtn to output a string
INCHAR   EQU     $FFCD    ;BUFFALO rtn to take a user input CHAR

;    c) memory map equates

USERDATA EQU     $0100    ;Where to place read/write(RAM) variables
CODE     EQU     $2000    ;Where to start placing program object code
                          ;32K RAM (U5) on CME11E9-EVBU board
****************************************************************************
* 3) CODE section - actual program code                                    *
****************************************************************************
         ORG     CODE     ; Tell assembler where to begin object code.
        
Main     EQU     *        ; Define label for start of Main program.

         LDX     #Greet  
         JSR     OUTSTRG  ; Displays the welcome message.
;                          "Welcome to the username creator!"
         BRA     Prompt   ; Skip error messages and begin inputs.
         
***************************** ERROR MESSAGES! ******************************         
ErrMsg1  LDX     #Err2L2S
         JSR     OUTSTRG  ; Displays the error message for too long or too short username.
;                          "ERROR!!! Username is too long or too short! 
;                           Must be between 0-26 characters!"
         CLRB             ; Clear ACCB used to check for errors.
         BRA     Prompt   ; Return to start of program inputs.
         
ErrMsg2  LDX     #ErrIncIn
         JSR     OUTSTRG  ; Displays the error message for username criteria not met.
;                          "ERROR!!! Username does not match criteria please try again!"
         CLRB             ; Clear ACCB used to check for errors.
         BRA     Prompt   ; Return to start of program inputs.
         
ErrMsg3  LDX     #ErrNoMat
         JSR     OUTSTRG  ; Displays the error message for usernames not matching.
;                          "ERROR!!! Usernames do not match please try again!"
         CLRB             ; Clear ACCB used to check for errors.
***************************** Username Input 1 *****************************
Prompt   LDX     #Prompt1
         JSR     OUTSTRG  ; Displays the prompt message to input the username.
;                          "Please enter a username 6-20 characters long lowercase 
;                           and capital letters accatable,"
         CLRB
              
         LDX     #UsName1 ; Loads the first username memory locations in index x.
         JSR     INSERUNA ; Jumps to the insert username subroutine.
         
         CMPA    #ESC     ; Checks if the user wants to quit program.
         BEQ     Quit     ; If the user pressed escape quit program.
         
         CMPB    #$FF     ; Checks if there was an error in the previous subroutine.
         BEQ     ErrMsg1  ; If there was an error display the too long or too short error.

         LDX     #$00     ; Reset index x back at zero.
         LDX     #UsName1 ; Re-load the first username with index x.        
         JSR     CHKUNC   ; Jump to the check username subroutine.
         
         CMPB    #$FF     ; Checks if there was an error in the previous subroutine.
         BEQ     ErrMsg2  ; If there was an error display the username doesn't meet 
;                           criteria error message.
***************************** Username Input 2 *****************************         
         LDX     #Prompt2 
         JSR     OUTSTRG  ; Displays the prompt message for username re-entry.
;                          "Please re-enter the username (press enter to finish username or 
;                           escape to quit program): "  
         CLRB             ; Clear ACCB used to check for errors.  
         LDX     #UsName2 ; Loads the second username memory locations in index x. 
         JSR     INSERUNA ; Jumps to the insert username subroutine.
         
         CMPA    #ESC     ; Checks if the user wants to quit program.
         BEQ     Quit     ; If the user pressed escape quit program.
         
         CMPB    #$FF     ; Checks if there was an error in the previous subroutine.
         BEQ     ErrMsg1  ; If there was an error display the too long or too short error.
 
         LDX     #$00     ; Reset index x back at zero.
         LDX     #UsName2 ; Re-load the second username with index x.         
         JSR     CHKUNC   ; Jump to the check username subroutine.
         
         CMPB    #$FF     ; Checks if there was an error in the previous subroutine.
         BEQ     ErrMsg2  ; If there was an error display the username doesn't meet 
;                            criteria error message.
***************************** Check Usernames ******************************                  
         JSR     CHKUN1A2 ; Jump to the check username one and two 
         
         CMPB    #$FF     ; Checks if there was an error in the previous subroutine. 
         BEQ     ErrMsg3  ; If there was an error display the usernames do not match error.
         
         LDX     #DisplyUN 
         JSR     OUTSTRG  ; Display the compeleted username message and username.
        ;                  "Congratulations! The validated username entered was: " 
         LDX     #UsName1 ; Load index x with the username that was validated.
         JSR     OUTSTRG  ; Display the user created username.
       
Quit     LDX     #QuitMess  
         JSR     OUTSTRG  ; Displays the quit message.
;                          "Program Terminated! Have a great day!"
        
         SWI              ; Return to BUFFALO monitor on HC11EVB.
****************************************************************************
*  Username Creator Subroutine -INSERUNA-                                  *
****************************************************************************
* This Subroutine takes user inputted characters and creates a username in a
*  location of memory.
*
* Parameters: Index X must point to an array of bytes to store CHARS into.
*             ACCB is used for ERROR checks.
****************************************************************************
INSERUNA EQU     *        ; Start of subroutine.

Start1   JSR     INCHAR   ; Store the CHAR in ACCA

         CMPA    #CR      ; Checks to see if the user pressed enter (finish username).
         BEQ     InsrEOT  ; If the user pressed enter move to insert EOT.
         
         CMPA    #ESC     ; Checks to see if the user pressed escape (quit program).
         BEQ     Escape   ; If the user pressed escape move to escape to quit program.
                
         STAA    0,X      ; Store the CHAR in the username memory found with index x.
         INX              ; Increment to the next memory location.
         INCB             ; Increment the count using ACCB to find if the username is too
;                           small or too large.
         BRA     Start1   ; Restart for the next user input.
        
InsrEOT  LDAA    #EOT     ; Load the EOT CHAR in ACCA.
         STAA    0,X      ; Stores the EOT at the next data slot.

         CMPB    #$05     ; Checks using increments of B if the input username is too small.
         BLS     ErrMsg   ; Will give an error message if B <= 5.
         
         CMPB    #$1B     ; Checks using increments of B if the input username is too large.
         BHS     ErrMsg   ; Will give an error message if B >= 27.
         
         BRA     Fin      ; Move to RTS. 
         
ErrMsg   LDAB    #$FF     ; Load ACCB with $FF(-1) to signal error.
         BRA     Fin      ; Move to RTS.
         
Escape   LDAA    #EOT     ; Load ACCA with EOT to finish the username as is.
         STAA    0,X      ; Stores EOT in the next memory location.
         LDAA    #ESC     ; Load ACCA with the escape charater to quit once returned to main.
         
Fin      RTS              ; Return from subroutine.
****************************************************************************
*  Check Username Criteria Subroutine -CHKUNC-                             *
****************************************************************************
* This Subroutine checks the inputed string for bad data the good data is:
* 6-20 characters, lowercase/capital letters, and periods
*  
* Parameters: Index x must point to a filled array to check each character.
*             ACCB is used for ERROR checks.
****************************************************************************
CHKUNC   EQU     *        ; Start of subroutine.
         
Start2   LDAA    0,X      ; Load ACCA with the memory location of the username
;                          using index x.

         CMPA    #EOT     ; Checks if the memory location hits the end of the username.
         BEQ     Stop     ; If it does, stop checking and move to the end of subroutine.
         
         CMPA    #$2D     ; Checks if the character is a '-' or lower.
         BLS     BAD      ; If it is, its bad data move to send error message.
         
         CMPA    #$2E     ; Checks if the character is a '.'.
         BEQ     GOOD     ; If it is, its good data move to next memory location.  

         CMPA    #$2F     ; Checks if the character is a '/'.
         BEQ     BAD      ; If it is, its bad data move to send error message.

         CMPA    #$39     ; Checks if the character is a '9' or lower.
         BLS     GOOD     ; If it is, its good data move to next memory location. 

         CMPA    #$40     ; Checks if the character is a '@' or lower.
         BLS     BAD      ; If it is, its bad data move to send error message.

         CMPA    #$5A     ; Checks if the character is a ' ' or lower.
         BLS     GOOD     ; If it is, its good data move to next memory location. 
 
         CMPA    #$60     ; Checks if the character is a ' ' or lower.
         BLS     BAD      ; If it is, its bad data move to send error message.

         CMPA    #$7A     ; Checks if the character is a ' ' or lower.
         BLS     GOOD     ; If it is, its good data move to next memory location. 

BAD      LDAB    #$FF     ; Since it is bad data, load ACCB with the error value (-1).
         BRA     Stop     ; Move to RTS.
         
GOOD     INX              ; Increment X to get the next character.
         BRA     Start2   ; Restart at the beginning to check next character.

Stop     RTS              ; Return from subroutine.         
****************************************************************************
*  Check Username 1st and 2nd Input -CHKUN1A2-                             *
****************************************************************************
* This Subroutine uses the x and y index registers to check the first and second
*     usernames character by character to see if they match.
*  
* Parameters: Index x points to the first username array and Index y points 
*              to the second username array to compare against each other.
*              ACCA is used with Index x and ACCB is used with Index y.
*              ACCB is still used for ERROR checks (if error is found ACCB is forced
*                                                    with $FF)
****************************************************************************
CHKUN1A2 EQU     *        ; Start of subroutine.

         LDX     #$00     ; Reset index x to zero.
         LDX     #UsName1 ; Load the first username using index x.
         
         LDY     #UsName2 ; Load the second username using index y.
         LDAB    #$0      ; Reset ACCB to zero
         BRA     Begin    ; Move to the start of the checks.
         
Next     INX              ; Step the first username to the next character.
         INY              ; Step the second username to the next character.
         CMPA    #EOT     ; Check if first username has hit EOT.
         BEQ     EndCheck ; If it does move to the last check.
         
Begin    LDAA    0,X      ; Load ACCA with the character found at x index.
         LDAB    0,Y      ; Load ACCB with the character found at y index.
         CBA              ; Check if the characters for the first and second 
         ;                 username match.
         BEQ     Next     ; If they do, go back to check the next character.
         
ChkErr   LDAB    #$FF     ; If they don't, load ACCB with the error value(-1). 
         BRA     FinChk   ; Move to RTS.

EndCheck CMPB    #EOT     ; Check if second username has hit EOT.
         BNE     ChkErr   ; If it hasn't, go to the error set.

FinChk   RTS              ; Return from subroutine.   
****************************************************************************
* 4) DATA section - variables & other data used by program                 *
****************************************************************************
;    a) constant data definitions (FCB,FDB,FCC)...
Greet    FCB      "Welcome to the username creator!",CR,EOT
Prompt1  FCB      "Please enter a username 6-20 characters long lowercase and capital letters accatable,",CR,"no special characters allowed except periods",CR,"(press enter to finish username or escape to quit program): ",EOT
Prompt2  FCB      "Please re-enter the username (press enter to finish username or escape to quit program): ",EOT
Err2L2S  FCB      "ERROR!!! Username is too long or too short! Must be between 0-26 characters!",CR,CR,EOT
ErrIncIn FCB      "ERROR!!! Username does not match criteria please try again!",CR,CR,EOT
ErrNoMat FCB      "ERROR!!! Usernames do not match please try again!",CR,CR,EOT
DisplyUN FCB      "Congratulations! The validated username entered was: ",EOT
QuitMess FCB      CR,"Program Terminated! Have a great day!",EOT

;    b) variable data allocations (RMB)...
* Input Buffer
         ORG      USERDATA ; To save the user input at a location
;                            starting at $0100
UsName1  RMB     30;
UsName2  RMB     30;
****************************************************************************
; End of assembly source code
        END