; Controllo se byte è pari o dispari
; Cercare il numero massimo nel vettore
dosseg
.model small
.stack 100H
.data
    NUM DB 25
.code

FINE:   mov ah, 4ch
        int 21h

DISPARI:
;stampo dispari
    JMP FINE

main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza
    
    MOV AL,NUM
    MOV BL,2
    DIV BL
    CMP AH,1
    JE DISPARI
    ;stampo che è pari
main endp
end main