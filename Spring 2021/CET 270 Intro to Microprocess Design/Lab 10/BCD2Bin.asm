        TTL     "Lab 10: BCD to Binary Conversion"
****************************************************************************
* 1) HEADER block - overall info about the program

* Project name:   BCD2Bin
* Author(s):      Andrew Bissell
* Date:           04/26/2021
* Description:
*   This program takes a user input of five decimal numbers and converts them
*    to an equivalent binary number. The program will output the numbers in HEX
*    and binary back to the user in this format: 
*                       "Decimal" = "$HEX" = "%Binary"
****************************************************************************
* 2) EQUATE section - define symbolic names for various values             *
****************************************************************************
;    a) constants...
CR       EQU     $0D     ;ASCII Carriage Return
EOT      EQU     $04     ;ASCII for End Of Transmission
ESC      EQU     $1B     ;ASCII for Escap
BACKSPA  EQU     $08     ;ASCII for Delete
BELL     EQU     $07     ;ASCII code to ring ouput Bell. (For ERRORS in input)

* BUFFALO utility routine entry points
OUTA     EQU     $FFB8   ;BUFFALO rtn to output char in acc A
OUTSTRG  EQU     $FFC7   ;BUFFALO OUTSTRING Subroutine
INCHAR   EQU     $FFCD   ;BUFFALO INCHAR Subroutine

;    b) memory map equates
RWDATA   EQU     $0000   ;Where to place read/write(RAM) variables
CODE     EQU     $2000   ;Where to start placing program object code
                        ;32K RAM (U5) on CME11E9-EVBU board
****************************************************************************
* 3) CODE section - actual program code                                    *
****************************************************************************
         ORG     CODE     ; Tell assembler where to begin object code.

Main     EQU     *        ; Define label for start of Main program.

         LDX     #Greet  
         JSR     OUTSTRG  ; Displays the welcome message.
        
InputSt  LDX     #Prompt
         JSR     OUTSTRG  ; Displays the prompt message.
        
         LDX     #DecVal  ; Loads the first location of the user input decimal data.
         JSR     INSERDEC ; Jumps to the insert decimal subroutine.
        
         CMPA    #ESC     ; Checks if the user wants to quit program.
         BEQ     MainESC  ; If the usede pressed escape quit program.
         
         LDX     #DecVal  ; Loads the first location of the user input decimal data.
         JSR     ChkDec   ; Jumps to the check decimal number subroutine.
         
         CMPB    #$FF     ; Check if error code from check decimal subroutine is found.
         BEQ     ErrOv    ; If it is move to error message.
        
         LDX     #DecVal  ; Loads the first location of the user input decimal data.
         JSR     BCD2Hex  ; Jumps to the BCD to Binary converter. 

         JSR     Output   ; Else, jump to the output subroutine.
         
         BRA     InputSt
         
MainESC  LDX     #QuitMess
         JSR     OUTSTRG  ; Display the Quit message.
         BRA     Quit     ; Move to quit program.
         
ErrOv    LDX     #ErrMsg  
         JSR     OUTSTRG  ; Display Error message.
         BRA     InputSt  ; Move back to input statement.
        
Quit     SWI              ; Return to BUFFALO monitor on HC11EVB.        
****************************************************************************
*  Insert Decimal Subroutine -INSERDEC-                                  *
****************************************************************************
* This Subroutine will take up to five user inputed numbers and save them to five
*  memory locations in the order they are inputted.
* Parameters: A memory loaction of 5 has to be set before hand.
*             Index X and ACCA used in subroutine.
*             No Error code is sent back to main if error occurs
****************************************************************************
INSERDEC EQU     *        ; Start of subroutine.

Start    CPX     #5       ; Check if the user input is equal to 5 or memory is full.
         BEQ     Fin      ; If it is end subroutine.

         JSR     INCHAR   ; Store the CHAR in ACCA
         
         CMPA    #ESC     ; Checks to see if the user pressed escape (quit program).
         BEQ     Fin      ; If the user pressed escape move to escape to quit program.
         
         CMPA    #BACKSPA ; Check if user deleted a number.
         BEQ     Delete   ; If the user deleted move to delete.
         
         CMPA    #$2F     ; Check if the user input is not a number.
         BLS     ErrorInp ; If it is, move to error input. 
         
         CMPA    #$39     ; Check if the user input is a number.
         BLS     GdInp    ; If it is, move to good input.

ErrorInp LDAA    #BELL    ; Ring the bell.
         JSR     OUTA    
         BRA     Start    ; Return to start of subroutine.
                
GdInp    ANDA    #$0F     ; Remove the first byte.
         STAA    0,X      ; Store the CHAR in the username memory found with index x.
         INX              ; Increment to the next memory location.
         BRA     Start    ; Restart for the next user input.

Delete   CPX     #0       ; Make sure X isn't pointing at the first memory location.
         BEQ     Start    ; If X is at the first location just restart the subroutine.
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
         LDAA    #BELL    ; Else, ring the bell.
         JSR     OUTA    
         DEX              ; Decrement X to delete that memory location.
         BRA     Start    ; Return to start of subroutine.
         
Fin      RTS              ; Return from subroutine.
****************************************************************************
*  Check Decimal Input for Overflow -ChkDec-                               *
****************************************************************************
* This Subroutine will check the inputted 5 decimal number by the user and check
*  to see if it overflows the two byte HEX number.
* Parameters: Must have a 5 input data variable (DecVal).
*             Uses Index X, ACCA and ACCB.
*             ACCB will output an error code ($FF) if overflow is found.
****************************************************************************
ChkDec   EQU     *       
         
         CLRB             ; Reset ACCB
         
         LDAA    0,X      ; Load ACCA with first memory location.
         CMPA    #$06     ; Check to see if first digit is greater than a 6.
         BGT     BadInp   ; If it is, move to bad input.
         
         CMPA    #$06     ; Else, check to see if the input is a 6.
         BNE     QuitChk  ; If it isn't, done checking number.
         INX              ; Step to next digit.
                
         LDAA    0,X      ; Load ACCA with second memory location.
         CMPA    #$05     ; Check to see if second digit is greater than a 5.
         BGT     BadInp   ; If it is, move to bad input.
         
         CMPA    #$05     ; Else, check to see if the input is a 5.
         BNE     QuitChk  ; If it isn't, done checking number.
         INX              ; Step to next digit.
         
         LDAA    0,X      ; Load ACCA with third memory location.
         CMPA    #$05     ; Check to see if third digit is greater than a 5.
         BGT     BadInp   ; If it is, move to bad input.
         
         CMPA    #$05     ; Else, check to see if the input is a 5.
         BNE     QuitChk  ; If it isn't, done checking.
         INX              ; Step to next digit.
         
         LDAA    0,X      ; Load ACCA with first memory location.
         CMPA    #$03     ; Check to see if fourth digit is greater than a 3.
         BGT     BadInp   ; If it is, move to bad input.
         
         CMPA    #$03     ; Else, check to see if the input is a 3.
         BNE     QuitChk  ; If it isn't, done checking number.
         INX              ; Step to next digit.
         
         LDAA    0,X      ; Load ACCA with fifth memory location.
         CMPA    #$05     ; Check to see if fifth digit is less than or equal to 5.
         BLS     QuitChk  ; If it is, done checking number.
                  
BadInp   LDAB    #$FF     ; Load ACCB with the error code.
         
QuitChk  RTS              ; Return back from subroutine.
****************************************************************************
*  BCD to Binary Subroutine -BCD2Hex-                                      *
****************************************************************************
* This Subroutine will take a user data input of 5 and convert it to a Hex number
*  that will be found in ACCD and then transfered to the variable DVal.
* Parameters: A memory loaction of 5 has to be set before hand.
*             The variable DVal must be set.
*             Uses ACCA, ACCB, Index X, and Index Y in processing.
*             Index X will return error code to not give false errors if the user input
*              equals the error code.
****************************************************************************
BCD2Hex  EQU     *       

         CLRA             ; Clear ACCA
         CLRB             ; Clear ACCB, ACCD is now clear

ConLoop  CPX     #5       ; Check if the loop has processed five times.
         BEQ     ConFin   ; If it has move to store ACCD in DVal and quit.
         
         STD     DVal     ; Store ACCD to DVal to add later.
         LSLD             ; Multiply by 2.
         LSLD             ;             4.
         ADDD    DVal     ; Add the DVal to ACCD to make the multiplication by 5.
         LSLD             ; Multiply by 10.
         
         XGDY             ; Exchange ACCD and Index Y.
         
         LDAB    0,X      ; Load ACCB with the current data location.
         ABY              ; Add that data to Index Y.
         
         XGDY             ; Else, Exchange ACCD and Index Y.
         INX              ; Step Index X to next memory location.
        
         BRA     ConLoop  ; Branch back to Index X check for continued processing.        
         
ConFin   STD     DVal     ; Store ACCD in the DVal for later processing.
         RTS              ; Return back from subroutine.
****************************************************************************
*  Output Decimal, Hex and Binary -Output-                                 *
****************************************************************************
* This Subroutine will output the DVal variable HEX to user and the binary equivalent
*  of DVal in this format:   "Decimal" = "$HEX" = "%Binary"
* Parameters: ACCA, ACCB and Index X are used in processing.
*             No error code is sent back to Main, all error checks should occur before
*              calling this subroutine!
****************************************************************************
Output   EQU     *       

         LDAA    #' '     ; Load ACCA with a space and output.
         JSR     OUTA
         
         LDAA    #'='     ; Load ACCA with a equal and output.
         JSR     OUTA         
         
         LDAA    #' '     ; Load ACCA with a space and output.
         JSR     OUTA

         LDAA    #'$'     ; Load ACCA with a dollar sign and output.
         JSR     OUTA
         
         LDAA    DVal     ; Load ACCA with the DVal first byte.
         JSR     CHA2ASC  ; Output the DVal first byte in HEX to user.
         
         LDAA    DVal+1   ; Load ACCA with the DVal second byte.
         JSR     CHA2ASC  ; Output the DVal second byte in HEX to user.

         LDAA    #' '     ; Load ACCA with a space and output.
         JSR     OUTA
         
         LDAA    #'='     ; Load ACCA with a equal and output.
         JSR     OUTA         
         
         LDAA    #' '     ; Load ACCA with a space and output.
         JSR     OUTA

         LDAA    #'%'     ; Load ACCA with a percent sign and output.
         JSR     OUTA
         
         LDD     DVal     ; Load DVal into ACCD.
         LDX     #$00     ; Clear Index X.
         
OptBin   LSLD             ; Shift ACCD once to the left.
         
         PSHA             ; Push A to the stack.
         BCC     OptZero  ; Branch if carry is clear to output a zero.
         
         LDAA    #'1'     ; Else, load ACCA with a one and output. 
         JSR     OUTA
         BRA     OptChk   ; Move to check if the loop has processed 16 times.
         
OptZero  LDAA    #'0'     ; If carry is clear, load ACCA with a zero and output.
         JSR     OUTA
         
OptChk   INX              ; Increment X to keep count.
         CPX     #16      ; Check if the loop has processed all 16 bits.
         PULA             ; Pull A off the stack.
         BEQ     OptQuit  ; If Index X is 16 quit subroutine.
         
         BRA     OptBin   ; Else, return to start of loop.
                  
OptQuit  RTS              ; Return from subroutine.
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
CHA2ASC  EQU     *        ; Start of subroutine.
************************** MSB Processing **********************************
         TAB
         LSRA               ; Logical Shift Right ACC A 1st time 
         LSRA               ;                           2nd time
         LSRA               ;                           3rd time
         LSRA               ;                           4th time
        
         CMPA    #$0A     ; If the value is equal to $A, go process the A.
         BGE     GrtA
        
         ORA     #$30
         JSR     OUTA     ; Call BuFFALO rtn to output ACCA. 
         BRA     NextDig  ; Skip to the end of Subroutine.
        
GrtA     ADDA    AtoF
         JSR     OUTA
************************** LSB Processing **********************************     
NextDig  TBA 
         ANDA    #$0F
        
         CMPA    #$0A     ; If the value is equal to $A, go process the A.
         BGE     GrtA2
        
         ORA     #$30
         JSR     OUTA     ; Call BuFFALO rtn to output ACCA. 
         BRA     FinASC   ; Skip to the end of Subroutine.
        
GrtA2    ADDA    AtoF
         JSR     OUTA
        
FinASC   RTS              ; Returns back to program 
;                           (MSB and LSB already displayed)
****************************************************************************
* 4) DATA section - variables & other data used by program                 *
****************************************************************************
;    a) constant data definitions (FCB,FDB,FCC)...
Greet    FCB      "Welcome to the BCD to Binary Converter (16-Bit)!",CR,EOT
Prompt   FCB      "16-Bit Decimal Calculator by: Andrew Bissell",CR,":    ",EOT
ErrMsg   FCB      "Conversion OVERFLOW! Insert number from 0 - 65535.",CR,EOT   
QuitMess FCB      CR,"Program Terminated! Have a great day!",EOT

;    b) variable data allocations (RMB)...
         ORG     RWDATA

DecVal   RMB     5
DVal     RMB     2
AtoF     FCB     $37
****************************************************************************
         END