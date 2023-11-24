                .data
                .text
                .globl main
                .ent main

main:           li		$t0, 4
                li		$t1, 2
                li		$t2, -5
                li		$t3, 3

                li		$s0, 8		# $s0 = 8
                li		$s1, 4		# $s1 = 4
                li		$s2, 27		# $s2 = 27
                li		$s3, 9		# $s3 = 9
                li		$s4, 64		# $s4 = 64
                li		$s5, 16		# $s5 = 16
                
                add		$a0, $t0, $t1		# $a0 = $t0 + $t1
                add		$a0, $a0, $t2		# $a0 = $a0 + $t2
                add		$a0, $a0, $t3		# $a0 = $a0 + $t3
                
                mult	$t0, $s0			# $t0 * $s0 = Hi and Lo registers
                mflo	$a1					# copy Lo to $a1
                mult	$t1, $s1			# $t1 * $s1 = Hi and Lo registers
                mflo	$t5					# copy Lo to $t5
                add		$a1, $a1, $t5		# $a1 = $a1 + $t5
                li		$t5, 2		        # $t5 = 2
                mult	$t2, $t5			# $t2 * $t5 = Hi and Lo registers
                mflo	$t5					# copy Lo to $t5
                add		$a1, $a1, $t5		# $a1 = $a1 + $t5
                add		$a1, $a1, $t3		# $a1 = $a1 + $t3
                
                mult	$t0, $s2			# $t0 * $s2 = Hi and Lo registers
                mflo	$a2					# copy Lo to $a2
                mult	$t1, $s3			# $t1 * $s3 = Hi and Lo registers
                mflo	$t5					# copy Lo to $t5
                add		$a2, $a2, $t5		# $a2 = $a2 + $t5
                li		$t5, 3		        # $t5 = 3
                mult	$t2, $t5			# $t2 * $t5 = Hi and Lo registers
                mflo	$t5					# copy Lo to $t5
                add		$a2, $a2, $t5		# $a2 = $a2 + $t5
                add		$a2, $a2, $t3		# $a2 = $a2 + $t3

                mult	$t0, $s4			# $t0 * $s4 = Hi and Lo registers
                mflo	$a3					# copy Lo to $a3
                mult	$t1, $s5			# $t1 * $s5 = Hi and Lo registers
                mflo	$t5					# copy Lo to $t5
                add		$a3, $a3, $t5		# $a3 = $a3 + $t5
                li		$t5, 4		        # $t5 = 4
                mult	$t2, $t5			# $t2 * $t5 = Hi and Lo registers
                mflo	$t5					# copy Lo to $t5
                add		$a3, $a3, $t5		# $a3 = $a3 + $t5
                add		$a3, $a3, $t3		# $a2 = $a2 + $t3

                li		$t4, 7 		        # $t4 = 7  <------- N
                subu    $sp, $sp, 24		# $sp = $sp - 24    
                sw		$t0, 0($sp)		    # 
                sw		$t1, 4($sp)		    # 
                sw		$t2, 8($sp)		    # 
                sw		$t3, 12($sp)	    # 
                sw		$t4, 16($sp)	    # 
                sw		$ra, 20($sp)	    #
                
                jal		polinomio			# jump to polinomio and save position to $ra
                
                lw		$ra, 20($sp)		# 
                lw		$t4, 16($sp)		# 
                lw		$t3, 12($sp)		# 
                lw		$t2, 8($sp)		    # 
                lw		$t1, 4($sp)		    # 
                lw		$t0, 0($sp)		    #
                addu	$sp, $sp, 24		# $sp = $sp + 24 

                move $a0, $v0
                li $v0, 1
                syscall
                
                jr		$ra					# jump to $ra
                

polinomio:      lw		$t4, 16($sp)		# 

                subu	$sp, $sp, 24	    # $sp = $sp - 24
                sw		$s0, 0($sp)		    # 
                sw		$s1, 4($sp)		    #
                sw		$s2, 8($sp)		    #
                sw		$s3, 12($sp)		#
                sw		$s4, 16($sp)		#
                sw		$s5, 20($sp)		#

                sub		$t0, $a1, $a0		# $t0 = $a1 - $a0
                sub		$t1, $a2, $a1		# $t1 = $a2 - $a1
                sub		$t2, $a3, $a2		# $t2 = $a3 - $a2
                sub		$s0, $t1, $t0		# $s0 = $t1 - $t0
                sub		$s1, $t2, $t1		# $s1 = $t2 - $t1
                sub		$s2, $s1, $s0		# $s2 = $s1 - $s0
                move 	$v0, $a3		    # $v0 = $a3

                li		$t5, 0		        # $t5 = 0
                addi	$t4, $t4, -4		# $t4 = $t4 + -4
                
                j		for				    # jump to for

for:            add		$s1, $s1, $s2		# $s1 = $s1 + $s2
                add		$t2, $t2, $s1		# $t2 = $t2 + $s1
                add		$v0, $v0, $t2		# $v0 = $v0 + $t2

                addi	$t5, $t5, 1			# $t5 = $t5 + 1
                beq		$t5, $t4, return	# if $t5 == $t4 then goto return
                j		for				# jump to for
                
                
return:         lw		$s5, 20($sp)		# 
                lw		$s4, 16($sp)		# 
                lw		$s3, 12($sp)		# 
                lw		$s2, 8($sp)		    # 
                lw		$s1, 4($sp)		    # 
                lw		$s0, 0($sp)		    # 
                addu	$sp, $sp, 24		# $sp = $sp + 24
                
                jr		$ra					# jump to $ra

                
                