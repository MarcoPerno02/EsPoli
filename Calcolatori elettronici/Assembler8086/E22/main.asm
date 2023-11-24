; Indovina numero
dosseg
.model small
.stack 100H
.data
    NUM DB 10
.code

FINE:   mov ah, 4ch
        int 21h

YES:
    ;stampo se lo trovato
    JMP FINE

CICLO:
    MOV AL,NUM
    CMP AL,SI
    JE YES
    INC SI
    JMP CICLO
    ; stampo se è no
    JMP FINE

main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza
    
   MOV SI,0
     

    
main endp
end main 