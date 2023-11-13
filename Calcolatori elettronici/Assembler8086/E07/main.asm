dosseg
.model small
.stack 100H
.data
            FUNZSTR DB 'Sono una funzione','$'
            MAINSTR DB 'Sono il main','$'
            MACROSTR DB 'Sono una macro','$'
            ACAPO DB 13,10,'$'
.code

FINE:       mov ah, 4ch
            int 21h

funzioneACaso proc
            MOV AH, 09H
            MOV DX, OFFSET FUNZSTR
            INT 21H; stampo stringa
            MOV DX, OFFSET ACAPO
            INT 21H; stampo stringa
            RET
funzioneACaso endp

macroACaso  MACRO p1, p2, p3
            MOV AH, 09H
            MOV DX, OFFSET MACROSTR
            INT 21H; stampo stringa
            MOV DX, OFFSET ACAPO
            INT 21H; stampo stringa
endm

main proc   
            MOV AX, @DATA
            MOV DS, AX
            MOV AH, 09H
            MOV DX, OFFSET MAINSTR
            INT 21H; stampo stringa
            MOV DX, OFFSET ACAPO
            INT 21H; stampo stringa

            CALL funzioneACaso 

            MOV AH, 09H
            MOV DX, OFFSET MAINSTR
            INT 21H; stampo stringa
            MOV DX, OFFSET ACAPO
            INT 21H; stampo stringa

            macroACaso

            MOV AH, 09H
            MOV DX, OFFSET MAINSTR
            INT 21H; stampo stringa
            MOV DX, OFFSET ACAPO
            INT 21H; stampo stringa
            JMP FINE
main endp
end main
