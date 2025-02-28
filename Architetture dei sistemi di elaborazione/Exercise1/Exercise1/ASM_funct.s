				AREA svc_code, CODE, READONLY				
				EXPORT  call_svc
call_svc		
				; save current SP for a faster access 
				; to parameters in the stack
				;MOV   r12, sp
				; save volatile registers
				;STMFD sp!,{lr}				
				MOV R0,R13 ;PASS INTO THE SVC HANDLER ADDRESS OF PSP			
				; your code
				SVC 0x5
				LDR R0,[SP,#-32]
				NOP
				B .
				
				; restore volatile registers
				;LDMFD sp!,{pc}
				END