; Esercizio espressione "x^2+5x+3"
.model small
.stack 100H
.data
    Y DB 10
    RIS DW ?
    TMP DW ?
.code

FINE:   mov ah, 4ch
        int 21h
  

main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza

    MOV AL, Y
    MUL Y
    MOV RIS, AX

    MOV AL, 5
    MUL Y
    MOV TMP, AX

    MOV AX, RIS
    ADD AX, TMP
    MOV RIS, AX

    MOV AX, RIS
    ADD AX, 3 
    MOV RIS, AX

    JMP FINE
    
main endp
end main