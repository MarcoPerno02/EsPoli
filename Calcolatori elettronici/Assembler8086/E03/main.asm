; Somma di due numeri con stampa

dosseg
.model small
.stack 100H
.data
    NUM1 DB ?
    NUM2 DB ?
    DOM1 DB 'Inserire primo numero: ',13,10,'$'
    DOM2 DB 'Inserire secondo numero: ',13,10,'$'
    RIS1 DB 'La somma essere: ',13,10,'$'
    SOMMA DB ?
.code

main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza

    MOV AH, 09H
    MOV DX, OFFSET DOM1; offset di dom1 da @data
    INT 21H; stampo stringa

    MOV AH, 01H
    INT 21H; Chideo in input carattere che andrà in AL
    MOV NUM1, AL

    MOV AH, 09H
    MOV DX, OFFSET DOM2; offset di dom2 da @data
    INT 21H; stampo stringa

    MOV AH, 01H
    INT 21H; Chideo in input carattere che andrà in AL
    MOV NUM2, AL

    MOV AL, NUM1
    ADD Al, NUM2
    MOV SOMMA, AL

    MOV AH, 09H
    MOV DX, OFFSET RIS1; offset di RIS1 da @data
    INT 21H; stampo stringa

    SUB SOMMA, 30H; Tolgo 30 per vedere il numero corretto e non carattere

    MOV AH, 02H
    MOV DL, SOMMA
    INT 21H

    mov ah, 4ch
    int 21h
main endp
end main