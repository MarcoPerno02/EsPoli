; Dire se il primo numero di 3 letti da input è il maggiore

dosseg
.model small
.stack 100H
.data
    NUM1 DB ?
    NUM2 DB ?
    NUM3 DB ?
    DOM1 DB 'Inserire primo numero: ',13,10,'$'
    DOM2 DB 'Inserire secondo numero: ',13,10,'$'
    DOM3 DB 'Inserire terzo numero: ',13,10,'$'
    RIS1 DB 'Il primo numero essere il maggiore',13,10,'$'
    RIS2 DB 'Il primo numero non essere il maggiore',13,10,'$'
.code

FINE:   mov ah, 4ch
        int 21h

VERO1:  MOV AL, NUM1
        CMP AL, NUM3

        JL FALSO; NUM1 < NUM3

        MOV AH, 09H
        MOV DX, OFFSET RIS1
        INT 21H; stampo stringa
        JMP FINE


FALSO:  MOV AH, 09H
        MOV DX, OFFSET RIS2
        INT 21H; stampo stringa
        JMP FINE
        

SE1:    CMP AL, NUM2
        JG  VERO1; NUM1 > NUM2
        JMP FALSO

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

    MOV AH, 09H
    MOV DX, OFFSET DOM3; offset di dom3 da @data
    INT 21H; stampo stringa

    MOV AH, 01H
    INT 21H; Chideo in input carattere che andrà in AL
    MOV NUM3, AL

    MOV AL, NUM1

    JMP SE1

    
main endp
end main




