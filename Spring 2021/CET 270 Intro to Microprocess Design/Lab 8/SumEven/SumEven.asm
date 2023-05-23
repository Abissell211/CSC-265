        TTL     "Lab 8 - SumEven Program"

******************************************************************
* 1) HEADER block - overall info about the program

* Project name:   SumEven - Lab08
* Author(s):      Andrew D. Bissell
* Date:           03/25/2021
* Description:
*   This program adds all of the Even numbers in an array and
*   stores the sum in variable SUM at location $0000.
*     
******************************************************************

******************************************************************
* 2) EQUATE section - define symbolic names for various values

;    a) constants...
CR      EQU     $0D     ;ASCII Carriage Return
EOT     EQU     $04     ;ASCII End Of Transmission char

* BUFFALO utility routine entry points
OUTA    EQU     $FFB8   ;BUFFALO rtn to output char in acc A
OUTSTRG EQU     $FFC7   ;string output routine

;    b) memory map equates

RWDATA  EQU     $0000   ;Where to place read/write(RAM) variables
CODE    EQU     $2000   ;Where to start placing program object code
                        ;32K RAM (U5) on CME11E9-EVBU board

******************************************************************

******************************************************************
* 3) CODE section - actual program code

        ORG     CODE       ; Tell assembler where to begin object code.
        
Main    EQU     *          ; Start of Main program

        LDAA    #ArrSiz    ; Store the number of array bytes in ARYCNT.
        STAA    ARYCNT  
        
        LDX     #Array     ; Point X to starting address of array.
        CLR     SUM        ; Initialze the SUM to zero.
        
ChkAdd  LDAA    0,X        ; get the number pointed to by X.
        ANDA    #%00000001 ; Keep ONLY the LSB.  
;       BNE     ChkDONE    ; if Odd (LSB = 0), ignore and go check 
;                            next number.
; OR ! ------------------------------------------------------------        
        LSRA               ; Shift LSB into the C-flag.
        BCS     ChkDONE    ; If Carry = 1 (ODD Number), 
;                            skip to check if done ->
; -----------------------------------------------------------------

        LDAA    SUM        ; Otherwise, the number is EVEN (LSB = 1),
        ADDA    0,X        ; So add it to what's already in SUM
        STAA    SUM        ; and SAVE the result BACK TO SUM.
        
ChkDONE INX                ; Move X to next number in array.
        DEC     ARYCNT     ; Dec # of numbers left to look at in array.
        BNE     ChkAdd     ; If not 0, continue to check next number.
        
        LDX     #OUTPUT    ; Point X to OUTPUT string.
        JSR     OUTSTRG    ; Call BUFFALO rtn to output it.
        
        LSRA               ; Logical Shift Right ACC A 1st time 
        LSRA               ;                           2nd time
        LSRA               ;                           3rd time
        LSRA               ;                           4th time
        ORAA    #$36       ; ORAA with $36 to load bit with ASCII CHAR
        JSR     OUTA       ; Call BuFFALO rtn to output ACC A.
        
        LDAA    SUM        ; Reload ACC A with the SUM
        ANDA    #$00       ; ANDA with $04 to clear left bit.
        ORAA    #$45       ; ORAA with $34 to load bit with ASCII CHAR
        JSR     OUTA       ; Call BuFFALO rtn to output ACC A.
        
        LDX     #NEWLINE   ; Creates a space for the OUTPUT Message
        JSR     OUTSTRG
        
        SWI                ; return to BUFFALO monitor on HC11EVB

        
******************************************************************

******************************************************************
* 4) DATA section - variables & other data used by program

; Array of numbers to sort.
Array   FCB     1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
                           ; Sum should equal $6E or 110. 
ArrSiz  EQU     *-Array    ; Set ArrSiz to the number of 
;                            bytes in the array.

        ORG     RWDATA     ; Set data starting from RWDATA which
;                            is located at memory location $0000.
        
SUM     RMB     1          ; Reserve for the sum.
ARYCNT  RMB     1          ; Reserve for the # of elements left
;                            in array

OUTPUT  FCB     "The sum of EVEN numbers in the array are: $",EOT
NEWLINE FCB     " ",CR,EOT
******************************************************************

; End of assembly source code
        END