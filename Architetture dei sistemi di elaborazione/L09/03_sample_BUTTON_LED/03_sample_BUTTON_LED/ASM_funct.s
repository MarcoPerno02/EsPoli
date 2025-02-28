				AREA asm_functions, CODE, READONLY				
					
				EXPORT next_state

next_state
    PUSH {R4-R7, LR} ;Push in the stack

    LDR R4, [R0]               ; Carica current_state (R0)
    LDR R5, [R1]               ; Carica taps (R1)

    AND R6, R4, #1             ; Calcola output_bit (R2 = bit meno significativo)
    STR R6, [R2]               ; Salva output_bit nella variabile

    ; XOR dei taps per calcolare il nuovo input_bit
    EOR R2, R4, R3, LSR #2
    EOR R2, R2, R3, LSR #3
    EOR R2, R2, R3, LSR #4
    AND R2, R2, #1             ; input_bit = XOR dei taps & 1

    ; Shift a destra del registro e inserimento del nuovo bit
    MOV R3, R3, LSR #1         ; Shift a destra di 1
    ORR R3, R3, R2, LSL #7     ; Inserisci il nuovo bit in posizione 7

    STR R3, [R0]               ; Salva il nuovo stato
	MOV R0, #0x55  ;
    POP {R4-R7, PC}    ; Pop from the stack
	END