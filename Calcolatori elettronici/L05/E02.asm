                .data
tab:            .word somma, sottrazione, moltiplic, divisione

                .text
                .globl main
                .ent main

main:           li $v0, 5
                syscall

                move 	$t2, $v0
                sll		$t2, $t2, 2			# $t2 = $t2 << 2
                

                li		$t0, 5		# $t0 = 5
                li		$t1, 8		# $t1 = 8
                
                lw		$t3, tab($t2)		# 
                jr		$t3					# jump to $t3
                

somma:          add		$t4, $t0, $t1		# $t4 = $t0 + $t1
                li $v0, 1 
                move 	$a0, $t4
                syscall
                j		end				# jump to end

sottrazione:    sub		$t4, $t0, $t1		# $t4 = $t0 - $t1
                li $v0, 1
                move 	$a0, $t4
                syscall
                j		end
                
moltiplic:      mult	$t0, $t1			# $t0 * $t1 = Hi and Lo registers
                mflo	$t4					# copy Lo to $t4
                li $v0, 1
                move 	$a0, $t4
                syscall
                j		end

divisione:      div		$t0, $t1			# $t0 / $t1
                mflo	$t2					# $t4 = floor($t0 / $t1) 
                li $v0, 1
                move 	$a0, $t4
                syscall
                j		end	

end:            li $v0, 10
                syscall
                .end main