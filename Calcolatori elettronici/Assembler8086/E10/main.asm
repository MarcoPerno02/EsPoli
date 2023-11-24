;   Date due variabili di tipo byte A e B contenenti interi senza 
;   segno, memorizzare in A il valore minore e in B il valore 
;   maggiore
.model small
.stack 100H
.data
    A DW 42 ;intero senza segno
    B DW 12
.code

FINE:   mov ah, 4ch
        int 21h
  
SCAMBIA:
    MOV AX,A
    MOV BX,B 
    MOV B, AX
    MOV A, BX
    JMP FINE

main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza

    MOV AX, A
    CMP AX, B
    JB FINE
    JMP SCAMBIA
    
main endp
end main