; Conta caratteri maiusc e min dati in input. 
; I 4 caratterri vanno salvati in un vettore anche

dosseg
.model small
.stack 100H
.data
        VETT DB 4 DUP(0)
        DOM1 DB 'Inserire carattere: ','$'
        ACAPO DB 13,10,'$'
        NMAIUSC DB 0
        NMINUSC DB 0
        CODASCIIMINUSC DB 96
        RIS1 DB 'Hai inserito il seguente numero di caratteri maiuscoli: ','$'
        RIS2 DB 'Hai inserito il seguente numero di caratteri minuscoli: ','$'
.code

FINE:       mov ah, 4ch
            int 21h

STAMPA:     MOV AH, 09H
            MOV DX, OFFSET RIS1
            INT 21H; stampo stringa
            MOV DX, OFFSET ACAPO
            INT 21H; stampo stringa

            ADD NMAIUSC, 48
            MOV AH, 02H
            MOV DL, NMAIUSC
            INT 21H
            MOV AH, 09H
            MOV DX, OFFSET ACAPO
            INT 21H; stampo stringa

            MOV AH, 09H
            MOV DX, OFFSET RIS2
            INT 21H; stampo stringa
            MOV DX, OFFSET ACAPO
            INT 21H; stampo stringa

            ADD NMINUSC, 48
            MOV AH, 02H
            MOV DL, NMINUSC
            INT 21H

            JMP FINE

MAIUSC:     INC NMAIUSC
            LOOP CICLO
            JMP STAMPA

MINUSC:     INC NMINUSC
            LOOP CICLO
            JMP STAMPA

main proc   
            MOV AX, @DATA
            MOV DS, AX
            MOV CX, 4
            MOV SI, 0
            JMP CICLO
            
CICLO:      MOV AH, 09H
            MOV DX, OFFSET DOM1
            INT 21H; stampo stringa
            MOV DX, OFFSET ACAPO
            INT 21H; stampo stringa

            MOV AH, 01H
            INT 21H; Leggo input carattere
            MOV VETT[SI], AL
            MOV DX, OFFSET ACAPO
            INT 21H; stampo stringa

            MOV AL, VETT[SI]
            CMP AL, CODASCIIMINUSC
            JG MINUSC
            JMP MAIUSC
main endp
end main