; Conta il numero di 1 nel vettore
dosseg
.model small
.stack 100H
.data
    vettore DB 0, 1, 1, 0, 0
    DIM DB 5
    CONT DB 0
.code

FINE:   mov ah, 4ch
        int 21h
CICLO:
    MOV AL,vettore[SI]
    CMP AL,1
    JE CONTATORE
    INC SI
    LOOP CICLO
    JMP FINE

CONTATORE:
    INC CONT
    INC SI
    LOOP CICLO
    JMP FINE


main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza
    
    MOV SI 0
    MOV CX 5
    JMP CICLO
    
main endp
end main