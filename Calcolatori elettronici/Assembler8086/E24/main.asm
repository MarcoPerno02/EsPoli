; Dato un array di 5 elementi contenente valori interi, calcolare la 
; somma dei suoi elementi e memorizzare il risultato in una 
; variabile
; Copia vettore in un altro vettore
dosseg
.model small
.stack 100H
.data
    vett DB 1, 2, 3, 4, 5
    DIM DB 5
    SOMMA DB 0
.code

FINE:   mov ah, 4ch
        int 21h

CICLO:
    MOV AL,vett[SI]
    ADD SOMMA
    MOV AL,SOMMA
    INC SI
    LOOP CICLO
    JMP FINE



main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza

    MOV SI,0
    MOV CX,5
    JMP CICLO
     

    
main endp
end main 