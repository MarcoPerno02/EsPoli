; Copia vettore in un altro vettore
dosseg
.model small
.stack 100H
.data
    vett1 0 DUP(5)
    vett2 1 DUP(5)
    DIM DB 5
.code

FINE:   mov ah, 4ch
        int 21h

CICLO:
    MOV AL,vett1[SI]
    MOV vett2[SI], AL
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