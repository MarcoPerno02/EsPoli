; 
dosseg
.model small
.stack 100H
.data
    vettore DB 1, 2, 3, 4, 5
    DIM DB 5
    SOMMA DB 0
.code

FINE:   mov ah, 4ch
        int 21h


STAMPAEL:
    ; Stampo elemento in posizione SI del vettore
    MOV AX, 0200H
    MOV DL, vettore[SI]
    ADD DL, 48
    INT 21H
    MOV AL, vettore[SI]
    ADD AL, SOMMA
    MOV SOMMA, AL

    INC SI
    LOOP STAMPAEL
    JMP FINE

main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza
    
    MOV CL, DIM
    MOV SI, 0
    JMP STAMPAEL

main endp
end main