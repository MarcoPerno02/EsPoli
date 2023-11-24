; Somma due numeri senza stampa e no input
dosseg
.model small
.stack 100H
.data
    GIGI DB 3
    PINO DB 2
    SOMMA DB ?
.code

main proc
    MOV AL, GIGI
    ADD AL, PINO
    MOV SOMMA, AL
    MOV BL, SOMMA

    mov ah, 4ch
    int 21h
main endp
end main