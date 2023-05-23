        TTL     "Exam 02 - Student Grade Program"

****************************************************************************
* 1) HEADER block - overall info about the program

* Project name: StudentGrade
* Author(s):    Andrew D. Bissell
* Date:         04/19/2021
* Description:
*   This program needs a username to access the data for student grades. If
*    the correct username is given, access to the average, minimum and maximum 
*    grades will be availible.
*
****************************************************************************
* 2) EQUATE section - define symbolic names for various values             *
****************************************************************************
;    a) constants...
CR       EQU     $0D       ;ASCII Carriage Return (To create a newline on output)
EOT      EQU     $04       ;ASCII for End Of Transmission (Use with OUTSTRG)
ESC      EQU     $1B       ;ASCII for Escape (For quitting the program)

;    b) "system" objects (I/O registers, monitor routines, etc.)
* BUFFALO utility routine entry points
OUTA     EQU     $FFB8    ;BUFFALO rtn to output char in acc A
OUTSTRG  EQU     $FFC7    ;BUFFALO rtn to output a string
INCHAR   EQU     $FFCD    ;BUFFALO rtn to take a user input CHAR

;    c) memory map equates
USERDATA EQU     $0000    ;Where to place read/write(RAM) variables
CODE     EQU     $2000    ;Where to start placing program object code
                          ;32K RAM (U5) on CME11E9-EVBU board
****************************************************************************
* 3) CODE section - actual program code                                    *
****************************************************************************
         ORG     CODE    ; Tell assembler where to begin object code.
        
Main     EQU     *       ; Define label for start of Main program.

         LDX     #Greet  
         JSR     OUTSTRG ; Displays the welcome message.
;                         "Welcome please enter you username to access grades: "
         BRA     Promp   ; Skip error messages and begin inputs.
         
***************************** ERROR MESSAGES! ******************************         
ErrMsg   LDX     #ErrNoMat
         JSR     OUTSTRG  ; Displays the error message for usernames not matching.
;                          "ERROR!!! Usernames do not match please try again!"
         CLRB             ; Clear ACCB used to check for errors.
         DEC     UNcount  ; Decrements the variable digtcount to keep the division count.
         BNE     Promp    ; Go to try username again. 
         
         LDX     #TMErr 
         JSR     OUTSTRG  ; Displays the error message for to many inputs.
;                          "Too many incorrect inputs!"           
         LDAA    #$03     ; Load ACCA with the reset for UNcount.
         STAA    UNcount  ; Reset the UNcount.
         BRA     Quit     ; Move to Quit message and SWI.
****************************** Username Input ******************************         
Promp    CLRB     
         LDX     #UsName  ; Loads the username memory locations in index x.
         JSR     INSERUNA ; Jumps to the insert username subroutine.
         
         CMPA    #ESC
         BEQ     Quit
         
         JSR     CHKUN    ; Jumps to the check Username subroutine.
         
         CMPB    #$FF     ; Checks if there was an error in the previous subroutine. 
         BEQ     ErrMsg   ; If there was an error display the usernames do not match error.

         LDAA    #$03     ; Load ACCA with the reset for UNcount.
         STAA    UNcount  ; Reset the UNcount.

InLoop   LDX     #Prompt
         JSR     OUTSTRG  ; Displays the prompt message.

         JSR     INCHAR   ; Get a input from the user to go to the various subroutines or quit.
         
         CMPA    #ESC     ; Checks if the input is a quit command.
         BEQ     Quit     ; If it is branch to quit message and SWI.
         
         CMPA    #'A'     ; Checks if the input is a Average command.
         BEQ     Average  ; If it is branch to the average subroutine.
         
         CMPA    #'N'     ; Checks if the input is a Minimum command.
         BEQ     Minimum  ; If it is branch to the minimum subroutine.
         
         CMPA    #'X'     ; Checks if the input is a Maximum command.
         BEQ     Maximum  ; If it is branch to the maximum subroutine.
         
         LDX     #ErrInp  ; If none of the above load error message.
         JSR     OUTSTRG  ; Output Error message for incorrect input.
;                          
         BRA     InLoop   ; Move back to get new input.
         
Average  JSR     GrdAve   ; Jump to subroutine to get grade average.
         BRA     InLoop   ; Once finished go back to get new input.
         
Minimum  JSR     GrdMin   ; Jump to subroutine to get minimum grade.
         BRA     InLoop   ; Once finished go back to get new input.
         
Maximum  JSR     GrdMax   ; Jump to subroutine to get maximum gr
         BRA     InLoop   ; Once finished go back to get new input.
               
Quit     LDX     #QuitMess 
         JSR     OUTSTRG  ; Displays the quit message.
;                          "Program Terminated! Have a great day!"

         SWI              ; Return to BUFFALO monitor on HC11EVB.
****************************************************************************
*  Insert Username Subroutine -INSERUNA-                                   *
****************************************************************************
* This Subroutine takes user inputted characters and creates a username in a
*  location of memory.
*
* Parameters: Index X must point to an array of bytes to store CHARS into.
*             ACCB is used for ERROR checks, and character count.
****************************************************************************
INSERUNA EQU     *        ; Start of subroutine.

Start1   JSR     INCHAR   ; Store the CHAR in ACCA

         CMPA    #ESC     ; Checks to see if the user pressed escape (quit program).
         BEQ     Escape   ; If the user pressed escape move to escape to quit program.

         CMPA    #CR      ; Checks to see if the user pressed enter (finish username).
         BEQ     InsrEOT  ; If the user pressed enter move to insert EOT.
                
         STAA    0,X      ; Store the CHAR in the username memory found with index x.
         INX              ; Increment to the next memory location.
         BRA     Start1   ; Restart for the next user input.
        
InsrEOT  LDAA    #EOT     ; Load the EOT CHAR in ACCA.
         STAA    0,X      ; Stores the EOT at the next data slot.        
         BRA     Fin      ; Move to RTS.          
         
Escape   LDAA    #EOT     ; Load ACCA with EOT to finish the username as is.
         STAA    0,X      ; Stores EOT in the next memory location.
         LDAA    #ESC     ; Load ACCA with the escape charater to quit once returned to main.
         
Fin      RTS              ; Return from subroutine. 
****************************************************************************
*  Check Username -CHKUN-                             *
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
CHKUN    EQU     *        ; Start of subroutine.

         LDX     #$00     ; Reset index x to zero.
         LDX     #UsName  ; Load the username using index x.
         BRA     Begin    ; Move to the start of the checks.
         
Next     INX              ; Increment to next username CHAR.
         CMPA    #EOT     ; Check if first username has hit EOT.
         BEQ     ChkStop  ; If it does move to the end of subroutine.
         
Begin    LDAA    0,X      ; Load ACCA with the character found at x index.
         CMPA    15,X     ; Check if the characters for the first and second 
         ;                 username match.
         BEQ     Next     ; If they do, go back to check the next character.
         
         LDAB    #$FF     ; If they don't, load ACCB with the error value(-1).     

ChkStop  RTS              ; Return from subroutine.
****************************************************************************
*  Get Average Grade Subroutine -GrdAve-                                   *
****************************************************************************
* This Subroutine takes an array of data (grades) and adds them together and
*  divides by the number of data variables to get the average.
*  
* Parameters: Uses the X Index for data count.
*             Uses the Y Index to add all the data together.
*             Does not change the values found in data array.
****************************************************************************
GrdAve   EQU     *        ; Start of subroutine.
         
         CLRA             ; Clear ACCA for processing.
         CLRB             ; Clear ACCB for processing.
         LDY     #$00     ; Clear Index Y for processing.
         LDX     #Grades  ; Load Index X with the grades start location.
         
AveStart CPX     #$10     ; Compare if it has looped through all the grades.
         BEQ     AveStop  ; Branch to final process and output message. 
         
         LDAB    0,X      ; Load the current grade pointed to by Index X into ACCB.
         ABY              ; Adds ACCB to index Y.
         INX              ; Step to the next grade.
         BRA     AveStart ; Branch back to start to process next grade.
                     
AveStop  XGDY             ; Trades the value stored in Index Y into ACCD.

         LSLD             ; Uses logical shift right to divide by 2.
         LSLD             ;                             divide by 4.
         LSLD             ;                             divide by 8.
         LSLD             ;                             divide by 16.
         
         STD     AVG      ; Store D into the variable Average.
         
         LDX     #StudAve 
         JSR     OUTSTRG  ; Display the student Average output message. 
;                          "Students Average = $"         
         LDAA    AVG      ; Load Average in ACCA to output.
         JSR     CHA2ASC  ; Jump to Character to ASCII to output the Average to user.
         
         RTS              ; Return from subroutine.
****************************************************************************
*  Get Average Grade Subroutine -GrdMin-                                   *
****************************************************************************
* This Subroutine takes a array of data and loops through to check and store
*  the minimum value.
*  
* Parameters: Use of an array of data to check
*             Uses the CHARASC Subroutine to output final calculation to user.
*             Does not change the values found in data array.
****************************************************************************
GrdMin   EQU     *        ; Start of subroutine.

         LDX     #Grades  ; Load X index with the grades start location.
         LDAA    0,X      ; Store the first grade in ACCA.
         STAA    MIN      ; Store the first grade as the initial Minimum.
         INX              ; Step to next grade.
         
MinStart CPX     #$10     ; Compare if it has looped through all the grades.
         BEQ     MinStop  ; Branch to the output messages if it has.
         
         LDAA    0,X      ; Load ACCA with the next grade.
         CMPA    MIN      ; Compare that with the current Minimum.
         BLS     StoreMin ; If the current grade is lower or the same as the 
;                            current Minimum go store it. 
         
         INX              ; If not move to next grade.
         BRA     MinStart ; Go back to the start to check next grade.
            
StoreMin STAA    MIN      ; Store the current grade as the new minimum.
         INX              ; Step to next grade.
         BRA     MinStart ; Go back to the start to check next grade.
         
MinStop  LDX     #StudMin 
         JSR     OUTSTRG  ; Display the Minimum output.
;                          "Minimum Student Grade = $"         
         
         LDAA    MIN      ; Load Minimum in ACCA to output.
         JSR     CHA2ASC  ; Jump to Character to ASCII to output the minimum to user.
         
         RTS              ; Return from subroutine.   
****************************************************************************
*  Get Average Grade Subroutine -GrdMax-                                   *
****************************************************************************
* This Subroutine takes an array of data and loops through to check and store
*  the maximum value.
*  
* Parameters: Use of an array of data to check.
*             Uses the CHARASC Subroutine to output final calculation to user.
*             Does not change the values found in data array.
****************************************************************************
GrdMax   EQU     *        ; Start of subroutine.

         LDX     #Grades  ; Load X index with the grades start location.
         LDAA    0,X      ; Store the first grade in ACCA.
         STAA    MAX      ; Store the first grade as the initial Maximum.
         INX              ; Step to next grade.
         
MaxStart CPX     #$10     ; Compare if it has looped through all the grades.
         BEQ     MaxStop  ; Branch to the output message if it has.
         
         LDAA    0,X      ; Load ACCA with the next grade.
         CMPA    MAX      ; Compare with the current Maximum.
         BHS     StoreMax ; If the current grade is higher or the same as the 
;                            current Maximum go store it.
         
         INX              ; If not move to next grade.
         BRA     MaxStart ; Go back to the start to check next grade.
         
StoreMax STAA    MAX      ; Store the current grade as the new Maximum.
         INX              ; Step to next grade.
         BRA     MaxStart ; Go back to the start to check next grade.
         
MaxStop  LDX     #StudMax 
         JSR     OUTSTRG  ; Display the Maximum output.
;                          "Maximum Student Grade = $"
         
         LDAA    MAX      ; Load Maximum in ACCA to output.
         JSR     CHA2ASC  ; Jump to Character to ASCII to output the Maximum to user.

         RTS              ; Return from subroutine.   
****************************************************************************
*  Character to ASCII Value Subroutine -CHA2ASC-                           *
****************************************************************************
* This Subroutine takes a user inputed CHAR and converts it into
*  it's proper ASCII Hex Value.
* Parameters: The Input CHAR in ACCA
*             Computes MSB hex value for ASCII CHAR and prints MSB,
*              then LSB and prints LSB.
*             CCR will be changed in here
****************************************************************************
CHA2ASC EQU     *       ; Start of subroutine.
************************** MSB Processing **********************************
        TAB
        LSRA               ; Logical Shift Right ACC A 1st time 
        LSRA               ;                           2nd time
        LSRA               ;                           3rd time
        LSRA               ;                           4th time
        
        ORA     #$30
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA.
************************** LSB Processing **********************************     
        TBA 
        ANDA    #$0F
        
        CMPA    #$0A    ; If the value is equal to $A, go process the A.
        BGE     GrtA
        
        ORA     #$30
        JSR     OUTA    ; Call BuFFALO rtn to output ACCA. 
        BRA     FinASC  ; Skip to the end of Subroutine.
        
GrtA    ADDA    AtoF
        JSR     OUTA
        
FinASC  RTS             ; Returns back to program 
;                         (MSB and LSB already displayed)         
****************************************************************************
* 4) DATA section - variables & other data used by program                 *
****************************************************************************
;    a) constant data definitions (FCB,FDB,FCC)...

Greet    FCB      "Welcome please enter you username to access grades: ",EOT
Prompt   FCB      "Press 'A' for Average, 'N' for Minimum or 'X' for Maximum Grade: ",EOT
ErrNoMat FCB      "ERROR!!! Usernames do not match please try again!",CR,CR,EOT
TMErr    FCB      "Too many incorrect inputs!",EOT
ErrInp   FCB      "Not the correct input (A,N,X,ESC)",CR,CR,EOT
StudAve  FCB      "Students Average = $",EOT
StudMin  FCB      "Minimum Student Grade = $",EOT
StudMax  FCB      "Maximum Student Grade = $",EOT
QuitMess FCB      CR,"Program Terminated! Have a great day!",EOT
;    b) variable data allocations (RMB)...

         ORG     USERDATA
;       Array of Grades
Grades   FCB     $23, $19, $5F, $21, $07, $62, $1A, $3C, $15, $4C, $31, $52, $51, $3F, $28, $33 ; AVG = $34
UsName   RMB     15      ; Variable for the user input Username.
;       Array to check if the inputted username matches against this data.
Username FCB     'G','r','a','d','e','r','0','1',EOT
AVG      RMB     1       ; Variable to store the average of the grades.
MIN      RMB     1       ; Variable to store the Minimum of the grades.
MAX      RMB     1       ; Variable to store the Maximum of the grades.
UNcount  DB      3       ; To keep track of the number of user failed inputs.
AtoF     FCB     $37     ; To convert HEX A throu F to user.         
****************************************************************************
         END