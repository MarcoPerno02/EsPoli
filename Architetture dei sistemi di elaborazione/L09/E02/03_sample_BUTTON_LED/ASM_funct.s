				AREA asm_functions, CODE, READONLY				
					
				EXPORT next_state

next_state
    PUSH {R3-R8, LR} ;Push in the stack

    ; Carica gli argomenti
    MOV R3, R0               ; R3 = current_state
    MOV R4, R1               ; R4 = taps

    ; Calcola l'output_bit
    AND R5, R3, #1             ; R5 = current_state & 1
    STR R5, [R2]               ; Salva output_bit nell'indirizzo puntato da R2
	
	MOV R7, #0					; R7 conterrà i vari risultati delle EXOR e poi il nuovo bit.
	MOV R8, #1					; R8 a 1 Indica che non c'è ancora un risulatato quindi bisogna mettere al primo giro in R7 solo l'operando iniziale. R8 viene poi messo a zero
	MOV R6, R3					; R6 sarà usato come registro che shifto ad 1 ad 1 per la EXOR
	MOV R2, #8;					; R2 ora lo uso come contatore del LOOP

LOOP
	AND R5, R4, #1             ; R5 = taps & 1 -> se ho 1 vuol dire che ho un tap
	
	CMP R5, #1
	BEQ CALCOLA_EXOR
	B FATTO_POSSIBILE_EXOR
	
CALCOLA_EXOR
	CMP R8, #1
	BEQ IMPOSTA_OPERANDO			; Se R8 è a un ovuol dire che non abbiamo ancora risultati

	EOR R7, R6, R7				; faccio la EXOR tra current state shiftato e risultato precedente delle exor.
								; nell'ultimo bit di R7 ci sarà sempre il risultato della EXOR e io sono interessato solo a quello
	B FATTO_POSSIBILE_EXOR

IMPOSTA_OPERANDO
	AND R7, R6, #1				; Metto in R7 il primo operando della exor, cioè l'ultimo bit del current state shifatto
	MOV R8, #0					; Azzero R8
	B FATTO_POSSIBILE_EXOR

FATTO_POSSIBILE_EXOR
	LSR R4, R4, #1             ; R4 = R4 >> 1 (shift dei taps logico verso destra di 1 bit)
	LSR R6, R6, #1             ; R6 = R6 >> 1 (shift di current_state logico verso destra di 1 bit)

	SUB R2, R2, #1				; Decrementa di 1 il contatore
	CMP R2, #0 				    ; Se R2 è arrivato 0 esci
	BNE LOOP

EXIT
	AND R7, R7, #1				; ora avro in R7 o 0 o 1 è sara il nuovo bit da aggiungere
	
	LSL R7, R7, #7				; Ora porto il bit finale all'inizio
	LSR R3, R3, #1				; Sposto current state di 1 verso sinistra e ora ho come primo bit 0
	ORR R3, R3, R7				; Facccio la OR tra current state shifato di 1 e il nuvo bit da inserire all'inizio

	MOV R0, R3 					; Metto in R0 il nuovo current state

	
POP_BEFORE_EXIT
    POP {R3-R8, PC}    ; Pop from the stack
	END