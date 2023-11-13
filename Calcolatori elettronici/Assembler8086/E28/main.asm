; Conversione decimmale binario
; Dato num fare quest'ultimo diviso 2 fino a qundo non sarà 0.
; ogni volta salvare il resto nello stack e una volta finite le divisioni bisognera fare la pop di tutti i resti inseriti
; 10 0
; 5 1
; 2 0
; 1 1
; 0

; Ricerca elemento in un vettore

; Prodotto scalare
; 10 20 30
; 1 2 3
; 10*1 + 20*2 + 30*3

; Conta quanti numeri nel vettore sono maggiori di 0
; Dato un array di 5 elementi contenente valori interi, calcolare la 
; somma dei suoi elementi e memorizzare il risultato in una 
; variabile
; Copia vettore in un altro vettore
dosseg
.model small
.stack 100H
.data
    NUM DB 20
    CONTAPUSH DB 0
.code

FINE:   mov ah, 4ch
        int 21h
CICLOPOP:
    POP AL
    LOOP CICLOPOP
    JMP FINE

CICLO:
    MOV AL,NUM
    DIV 2
    PUSH AH  
    CMP AL, 0
    INC CONTAPUSH
    JG CICLO
    MOV CL, CICLOPOP
    JMP CICLOPOP


main proc
    MOV AX,  @DATA
    MOV DS, AX; passare @DATA per forza

    JMP CICLO
    

main endp
end main 

