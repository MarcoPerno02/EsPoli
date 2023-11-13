; Dati A e B, controllare che 5A+1 < B
dosseg
.model small
.stack 100H
.data
    A DB 10
    B DB 80
    TMP DB ?
.code

FINE:   mov ah, 4ch
        int 21h

VERo:
   JMP FINE
FALSO:
    JMP FINE 

main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza

    MOV AL,5
    MUL A
    MOV TMP,AL
    ADD TMP,1
    MOV AL,TMP
    CMP AL,B 
    JB VERO
    JMP FALSO

    
main endp
end main