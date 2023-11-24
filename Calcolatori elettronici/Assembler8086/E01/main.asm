; Prova assembley
dosseg
.model small
.stack 100H
.data
    GIGI DB 5
    PINO DB 10
    SOMMA DB ?
.code

main proc
MOV dl, '5'
mov ah, 2
int 21h

mov ah, 4ch
int 21h
main endp
end main