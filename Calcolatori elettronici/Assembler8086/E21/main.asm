; Controllare se un numero è divisibile per 2 e 5
dosseg
.model small
.stack 100H
.data
    NUM DB 20
.code

FINE:   mov ah, 4ch
        int 21h

DIVISIBILE:
    ;stampo che è divisibile
    JMP FINE


DIVISIBILITà:
    MOV AL,NUM
    DIV 5
    CMP AH,0
    JE DIVISIBILE
    ;STampo se non è divisibile
    JMP FINE

main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza
    
    MOV AL,NUM
    DIV 2
    CMP AH,0
    JE DIVISIBILITà
    ;STampo se non è divisibile
    JMP FINE

    
main endp
end main