;/**************************************************************************//**
; * @file     startup_LPC17xx.s
; * @brief    CMSIS Cortex-M3 Core Device Startup File for
; *           NXP LPC17xx Device Series
; * @version  V1.10
; * @date     06. April 2011
; *
; * @note
; * Copyright (C) 2009-2011 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/

; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3	; 2*3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WDT_IRQHandler            ; 16: Watchdog Timer
                DCD     TIMER0_IRQHandler         ; 17: Timer0
                DCD     TIMER1_IRQHandler         ; 18: Timer1
                DCD     TIMER2_IRQHandler         ; 19: Timer2
                DCD     TIMER3_IRQHandler         ; 20: Timer3
                DCD     UART0_IRQHandler          ; 21: UART0
                DCD     UART1_IRQHandler          ; 22: UART1
                DCD     UART2_IRQHandler          ; 23: UART2
                DCD     UART3_IRQHandler          ; 24: UART3
                DCD     PWM1_IRQHandler           ; 25: PWM1
                DCD     I2C0_IRQHandler           ; 26: I2C0
                DCD     I2C1_IRQHandler           ; 27: I2C1
                DCD     I2C2_IRQHandler           ; 28: I2C2
                DCD     SPI_IRQHandler            ; 29: SPI
                DCD     SSP0_IRQHandler           ; 30: SSP0
                DCD     SSP1_IRQHandler           ; 31: SSP1
                DCD     PLL0_IRQHandler           ; 32: PLL0 Lock (Main PLL)
                DCD     RTC_IRQHandler            ; 33: Real Time Clock
                DCD     EINT0_IRQHandler          ; 34: External Interrupt 0
                DCD     EINT1_IRQHandler          ; 35: External Interrupt 1
                DCD     EINT2_IRQHandler          ; 36: External Interrupt 2
                DCD     EINT3_IRQHandler          ; 37: External Interrupt 3
                DCD     ADC_IRQHandler            ; 38: A/D Converter
                DCD     BOD_IRQHandler            ; 39: Brown-Out Detect
                DCD     USB_IRQHandler            ; 40: USB
                DCD     CAN_IRQHandler            ; 41: CAN
                DCD     DMA_IRQHandler            ; 42: General Purpose DMA
                DCD     I2S_IRQHandler            ; 43: I2S
                DCD     ENET_IRQHandler           ; 44: Ethernet
                DCD     RIT_IRQHandler            ; 45: Repetitive Interrupt Timer
                DCD     MCPWM_IRQHandler          ; 46: Motor Control PWM
                DCD     QEI_IRQHandler            ; 47: Quadrature Encoder Interface
                DCD     PLL1_IRQHandler           ; 48: PLL1 Lock (USB PLL)
                DCD     USBActivity_IRQHandler    ; 49: USB Activity interrupt to wakeup
                DCD     CANActivity_IRQHandler    ; 50: CAN Activity interrupt to wakeup


                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF


var				RN 		2

                AREA    |.text|, CODE, READONLY



; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]                                            
                
				; Inizializzazione del registro per il conteggio dei giorni
        LDR R3, =Num_days         ; Carica l'indirizzo di Num_days
        LDRB R3, [R3]             ; Carica il numero di giorni in R3

        ; Copia Best_times in un buffer temporaneo per ordinamento
        LDR R0, =Best_times       ; Indirizzo di Best_times
        LDR R1, =Failed_runs      ; Indirizzo di Failed_runs
        LDR R2, =Best_times_ordered ; Destinazione per ID ordinati di Best_times
        LDR R4, =Failed_runs_ordered ; Destinazione per ID ordinati di Failed_runs

        ; ---------------------
        ; Ordinamento di Best_times
        ; ---------------------

Sort_BestTimes
        MOV R5, #0                ; R5 � l'indice per l'ordinamento di Best_times

Outer_BestTimes_Loop
        CMP R5, R3
        BGE Done_BestTimes_Sort   ; Esci dal loop esterno se completato
        MOV R6, R5                ; R6 � l'indice interno

Inner_BestTimes_Loop
        CMP R6, R3
        BGE Next_BestTime_Pass    ; Se R6 >= Num_days, passa al prossimo ciclo di ordinamento
        ADD R7, R0, R5, LSL #3    ; Calcola l'indirizzo di Best_times[R5]
        LDR R8, [R7, #4]          ; Carica il best time corrente
        ADD R9, R0, R6, LSL #3    ; Calcola l'indirizzo di Best_times[R6]
        LDR R10, [R9, #4]         ; Carica il best time per confronto

        CMP R8, R10               ; Confronta i due best times
        BGT Swap_BestTimes        ; Se il valore attuale � maggiore, esegui swap
        B No_Swap_BestTimes

Swap_BestTimes
        ; Swap degli ID dei giorni
        LDR R8, [R7]              ; Carica l'ID del giorno attuale
        LDR R10, [R9]             ; Carica l'ID del giorno per confronto
        STR R10, [R7]             ; Memorizza l'ID del giorno pi� grande nella posizione attuale
        STR R8, [R9]              ; Memorizza l'ID del giorno pi� piccolo nella posizione di confronto

No_Swap_BestTimes
        ADD R6, R6, #1            ; Incrementa l'indice interno
        B Inner_BestTimes_Loop

Next_BestTime_Pass
        ADD R5, R5, #1            ; Incrementa l'indice esterno
        B Outer_BestTimes_Loop

Done_BestTimes_Sort
        ; Salva il peggior giorno in R11
        LDR R11, [R0, #24]        ; Il peggior best time sar� alla fine
		B Sort_FailedRuns

		; ---------------------
        ; Ordinamento di Failed_runs
        ; ---------------------

Sort_FailedRuns
        MOV R5, #0                ; R5 � l'indice per l'ordinamento di Failed_runs

Outer_FailedRuns_Loop
        CMP R5, R3
        BGE Done_FailedRuns_Sort  ; Esci dal loop esterno se completato
        MOV R6, R5                ; R6 � l'indice interno

Inner_FailedRuns_Loop
        CMP R6, R3
        BGE Next_FailedRun_Pass   ; Se R6 >= Num_days, passa al prossimo ciclo di ordinamento
        ADD R7, R1, R5, LSL #3    ; Calcola l'indirizzo di Failed_runs[R5]
        LDR R8, [R7, #4]          ; Carica il numero di failed runs corrente
        ADD R9, R1, R6, LSL #3    ; Calcola l'indirizzo di Failed_runs[R6]
        LDR R10, [R9, #4]         ; Carica il numero di failed runs per confronto

        CMP R8, R10               ; Confronta i due valori di failed runs
        BGT Swap_FailedRuns       ; Se il valore attuale � maggiore, esegui swap
        B No_Swap_FailedRuns

Swap_FailedRuns
        ; Swap degli ID dei giorni
        LDR R8, [R7]              ; Carica l'ID del giorno attuale
        LDR R10, [R9]             ; Carica l'ID del giorno per confronto
        STR R10, [R7]             ; Memorizza l'ID del giorno pi� grande nella posizione attuale
        STR R8, [R9]              ; Memorizza l'ID del giorno pi� piccolo nella posizione di confronto

No_Swap_FailedRuns
        ADD R6, R6, #1            ; Incrementa l'indice interno
        B Inner_FailedRuns_Loop

Next_FailedRun_Pass
        ADD R5, R5, #1            ; Incrementa l'indice esterno
        B Outer_FailedRuns_Loop

Done_FailedRuns_Sort
        ; Fine del programma
        B End

End
        ; R11 contiene il numero totale di giorni con best time >= 1300
        ; R10 contiene il totale di failed_runs per quei giorni

        ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]

                B       .
				
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                ; your code
				orr r0,r0,#1
				mov r1, r2
				BX	r0
                ENDP

						LTORG
ALIGN2
Boundary space 4096

Days                DCB 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07

Best_times          DCD 0x06, 1300, 0x03, 1700, 0x02, 1200, 0x04, 1900, 0x05, 1110, 0x01, 1670, 0x07, 1000

Failed_runs         DCD 0x02, 50, 0x05, 30, 0x06, 100, 0x01, 58, 0x03, 40, 0x04, 90, 0x07, 25

Num_days           DCB 7

Best_times_ordered      DCD 0, 0, 0, 0, 0, 0, 0    ; Vettore di output per ID giorni ordinati per Best_times
Failed_runs_ordered     DCD 0, 0, 0, 0, 0, 0, 0    ; Vettore di output per ID giorni ordinati per Failed_runs
	
Boundary2 space 4096					
					
					

MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  TIMER0_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler         [WEAK]
                EXPORT  TIMER2_IRQHandler         [WEAK]
                EXPORT  TIMER3_IRQHandler         [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART3_IRQHandler          [WEAK]
                EXPORT  PWM1_IRQHandler           [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  SPI_IRQHandler            [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  PLL0_IRQHandler           [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  EINT0_IRQHandler          [WEAK]
                EXPORT  EINT1_IRQHandler          [WEAK]
                EXPORT  EINT2_IRQHandler          [WEAK]
                EXPORT  EINT3_IRQHandler          [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  CAN_IRQHandler            [WEAK]
                EXPORT  DMA_IRQHandler            [WEAK]
                EXPORT  I2S_IRQHandler            [WEAK]
                EXPORT  ENET_IRQHandler           [WEAK]
                EXPORT  RIT_IRQHandler            [WEAK]
                EXPORT  MCPWM_IRQHandler          [WEAK]
                EXPORT  QEI_IRQHandler            [WEAK]
                EXPORT  PLL1_IRQHandler           [WEAK]
                EXPORT  USBActivity_IRQHandler    [WEAK]
                EXPORT  CANActivity_IRQHandler    [WEAK]

WDT_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
PWM1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI_IRQHandler
SSP0_IRQHandler
SSP1_IRQHandler
PLL0_IRQHandler
RTC_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
ADC_IRQHandler
BOD_IRQHandler
USB_IRQHandler
CAN_IRQHandler
DMA_IRQHandler
I2S_IRQHandler
ENET_IRQHandler
RIT_IRQHandler
MCPWM_IRQHandler
QEI_IRQHandler
PLL1_IRQHandler
USBActivity_IRQHandler
CANActivity_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit                

                END
