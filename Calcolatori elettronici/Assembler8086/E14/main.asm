; Cercare il numero massimo nel vettore
dosseg
.model small
.stack 100H
.data
    vettore DB 1, 2, 3, 4, 5
    DIM DB 5
    MAX DB -88
.code

FINE:   mov ah, 4ch
        int 21h

AGGMAX:
    MOV AL, vettore[si]
    MOV MAX, AL

    INC SI
    LOOP CICLO
    JMP FINE


CICLO:
    MOV AL,vettore[SI]
    CMP AL,MAX
    JG AGGMAX


    INC SI
    LOOP CICLO
    JMP FINE

main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza
    
    MOV CL, DIM
    MOV SI, 0
    JMP CICLO

main endp
end main