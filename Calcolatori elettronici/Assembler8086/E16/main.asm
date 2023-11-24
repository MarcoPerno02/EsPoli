; Calcolo minimo divisore che dia resto 0 di NUM
dosseg
.model small
.stack 100H
.data
    NUM DB 21
    CONT DB 2
.code

FINE:   mov ah, 4ch
        int 21h

CICLO:
    MOV AL,NUM
    DIV CONT
    CMP AH,0
    JE FINE
    INC CONT    
    JMP CICLO

main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza
    
    JMP CICLO

    
main endp
end main