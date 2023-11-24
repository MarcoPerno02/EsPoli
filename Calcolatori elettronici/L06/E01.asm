                .data
num:            .word 3141592653

                .text
                .globl main
                .ent main

main:           lw		$t0, num		    # 
                li		$t4, 0		        # $t4 = 0
                
                j		divisione			# jump to divisione

divisione:      li		$t1, 10		        # $t1 = 10
                divu	$t0, $t1			# $t0 / $t1
                mflo	$t0					# $t0 = floor($t0 / $t1) 
                mfhi	$t2					# $t2 = $t0 % $t1 
                subu    $sp, $sp, 4
                sw		$t2, 0($sp)		    # 
                addi	$t4, $t4, 1			# $t4 = $t4 + 1
                beq		$t0, $0, stampa	    # if $t0 == $0 then goto stampa
                j		divisione			# jump to divisione

stampa:         beq		$t4, $0, end	# if $t4 == $0 then goto end
                lw		$a0, 0($sp)		# 
                addi	$a0, $a0, 48			# $a0 = $a0 + 48
                li      $v0, 11
                syscall
                addu    $sp, $sp, 4
                addi	$t4, $t4, -1			# $t4 = $t4 + -1
                bne		$t4, $0, stampa	# if $t4 != $0 then goto stampa
                j		end				# jump to end
                
                


end:            li $v0, 10
                syscall
                .end main

