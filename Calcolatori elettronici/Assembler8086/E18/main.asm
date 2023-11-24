; Cerca num in vettore
dosseg
.model small
.stack 100H
.data
    NUM DB 21
    vettore DB 5, 48, 21, 83, 4
    DIM DB 5
.code

FINE:   mov ah, 4ch
        int 21h
CICLO:
    MOV AL, vettore [SI]
    CMP AL,NUM
    JE FINE
    INC SI
    LOOP CICLO
    ; stampo non trovato
    JMP FINE


main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza
    
    MOV SI,0
    MOV CX,5
    JMP CICLO
    
main endp
end main