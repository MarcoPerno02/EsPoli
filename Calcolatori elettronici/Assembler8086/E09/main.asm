; Somma primi 5 numeri interi con un ciclo
.model small
.stack 100H
.data
    RIS DB 0
    CONT DB 0
.code

FINE:   mov ah, 4ch
        int 21h

CICLO: 
    MOV AL,CONT 
    ADD AL,RIS
    INC CONT
    LOOP CICLO
    JMP FINE


main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza

    MOV CONT,0
    MOV CX,5
    JMP CICLO
    
main endp
end main