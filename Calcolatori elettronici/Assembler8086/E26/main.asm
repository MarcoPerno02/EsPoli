; Prodotto scalare
; 10 20 30
; 1 2 3
; 10*1 + 20*2 + 30*3

; Conta quanti numeri nel vettore sono maggiori di 0
; Dato un array di 5 elementi contenente valori interi, calcolare la 
; somma dei suoi elementi e memorizzare il risultato in una 
; variabile
; Copia vettore in un altro vettore
dosseg
.model small
.stack 100H
.data
    vett1 DB 10, 20, 30
    vett2 DB 1, 2, 3
    DIM DB 3
    SOMMA DB 0
.code

FINE:   mov ah, 4ch
        int 21h

CICLO:
    MOV AL,vett1[SI]
    MUL vett2[SI]
    ADD AL, SOMMA
    MOV SOMMA, AL
    INC SI
    LOOP CICLO
    JMP FINE




main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza

    MOV SI,0
    MOV CX,3
    JMP CICLO
    
main endp
end main 

