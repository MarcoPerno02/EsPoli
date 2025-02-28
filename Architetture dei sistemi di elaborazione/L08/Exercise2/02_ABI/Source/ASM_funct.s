				
				
				AREA asm_functions, CODE, READONLY				
					
				EXPORT check_square
check_square    FUNCTION
				PUSH {R4-R7,LR} ;Push in the stack
				
				; Calculate params for elaboration
				MOV R4,R0 ; x_value
				MOV R5,R1 ; y_vlaue
				MOV R6,R2 ; RADIUS
				MUL R4,R4,R4 ; x_value^2
				MUL R5,R5,R5 ; y_value^2
				MUL R6,R6,R6 ; RADIUS^2
				ADD R7,R4,R5 ; x_value^2+y_value^2
				
				; Compare x_value^2+y_value^2 with RADIUS^2
				CMP R7,R6
				MOVLE R0,#1
				MOVGT R0,#0
				
				POP {R4-R7,PC} ; Pop from the stack
				ENDFUNC
				
				IMPORT __aeabi_fdiv
				EXPORT my_division

my_division     FUNCTION
				PUSH {R4-R7, LR} ;Push in the stack
				
				; Load area and radius^2
				LDR R4, [R0]
				LDR R5, [R1]
	
				; Load params in R0 and R1 for __aeabi_fdiv
				MOV R0, R4
				MOV R1, R5

				BL __aeabi_fdiv        

				POP {R4-R7, PC}    ; Pop from the stack
				ENDFUNC

				END