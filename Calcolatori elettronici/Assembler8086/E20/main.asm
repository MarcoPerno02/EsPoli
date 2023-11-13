; Conta il numero di 1 nel vettore
dosseg
.model small
.stack 100H
.data
    vettore DB 0, 1, 1, 0, 0
    DIM DB 5
.code

FINE:   mov ah, 4ch
        int 21h



main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza
    

    
main endp
end main