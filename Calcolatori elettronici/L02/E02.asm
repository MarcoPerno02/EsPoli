                .data
message:        .asciiz "Inserisci un numero: "
noOverflowMessage: .asciiz "No overflow\n"
overflowMessage: .asciiz "overflow\n"

                .text
                .globl main
                .ent main

main:           la $a0, message
                li $v0, 4
                syscall
                li $v0, 5
                syscall
                move $t0, $v0

                la $a0, message
                li $v0, 4
                syscall
                li $v0, 5
                syscall
                move $t1, $v0
                
                addu		$t2, $t0, $t1		# $t2 = $t0 + $t1

                slti	$t3, $t0, 0			# $t2 = ($t0 < 0) ? 1 : 0
                bne		$t3, $0, primoNumNeg	# if $t2 != $0 then goto primoNumNeg
                j		primoNumPos				# jump to primoNumPos
                
                

primoNumPos:    slti	$t3, $t1, 0			# $t2 = ($t1 < 0) ? 1 : 0
                bne		$t3, $0, noOverflow	# if $t3 != $0 (quindi negativo) then goto noOverflow
                # second number positive
                # check if the result is negative
                slti	$t3, $t2, 0			# $t3 = ($t2 < 0) ? 1 : 0
                bne		$t3, $0, overflow	# if $t3 != $0 (quindi negativo) then goto overflow
                j		noOverflow				# jump to noOverflow




primoNumNeg:    slti	$t3, $t1, 0			# $t2 = ($t1 < 0) ? 1 : 0
                beq		$t3, $0, noOverflow	# if $t3 == $0 (quindi positivo) then goto noOverflow
                # second number negative
                # check if the result is positive
                slti	$t3, $t2, 0			# $t3 = ($t2 < 0) ? 1 : 0
                beq		$t3, $0, overflow	# if $t3 == $0 (quindi positivo) then goto overflow
                j		noOverflow				# jump to noOverflow
                
                


overflow:       la $a0, overflowMessage
                li $v0, 4
                syscall
                j		end				# jump to end


noOverflow:     la $a0, noOverflowMessage
                li $v0, 4
                syscall
                j		end				# jump to end
                

end:            li $v0, 10
                syscall
                .end main