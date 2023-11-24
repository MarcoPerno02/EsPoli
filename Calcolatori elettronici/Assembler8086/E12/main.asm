; Dati 3 numeri dire se il primo, il secondo o il terzo è il più grande
dosseg
.model small
.stack 100H
.data
    A DB 10
    B DB 80
    C DB 25
.code

FINE:   mov ah, 4ch
        int 21h

CmaggBmaggA:
    ; Stampo C maggiore di tutti
    JMP FINE
BmaggA:
    MOV AL,B
    CMP AL,C
    JB CmaggBmaggA
    ; Stampo B maggiore di tutti
    JMP FINE

AmaggB:
    


main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza
    MOV AL,A
    CMP AL,B
    JB BmaggA
    JMP AmaggB

main endp
end main