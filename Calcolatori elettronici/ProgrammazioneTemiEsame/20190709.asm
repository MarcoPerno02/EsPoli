                    DIM = 4 
                    .data 
matrice:            .word 126, -988, 65, 52 
                    .word 7, 0, 2, 643 
                    .word 66, 532, 43, 9254 
                    .word 5, -51, 4352, -452 
stringa:            .asciiz " "
                    .text 
                    .globl main 
                    .ent main 
main:               subu $sp, $sp, 4 
                    sw $ra, ($sp) 
                    la $a0, matrice 
                    li $a1, DIM 
                    li $t0, 0		# $t0 = 0
                    jal calcolaTrasp 
                    lw $ra, ($sp) 
                    addiu $sp, $sp, 4 
                    jr $ra

calcolaTrasp:       li		$t8, DIM		# $t8 = DIM
                    addi	$t8, $t8, -1			# $t8 = $t8 + -1
                    beq		$t0, $t8, beforePrint	# if $t0 == $t8 then goto beforePrint
                    addi	$t1, $t0, 1			# $t1 = $t0 + 1
                    j		inverti				# jump to inverti
                    

                    
                    
inverti:            li		$t6, DIM		# $t6 = DIM
                    li		$t7, 4		# $t7 = 4

                    # Calcolo indirizzo primo el in $t2 e conteunto in $t3
                    mult	$t0, $t6			# $t0 * $t6 = Hi and Lo registers
                    mflo	$t2					# copy Lo to $t2
                    add		$t2, $t2, $t1		# $t2 = $t2 + $t1
                    mult	$t2, $t7			# $t2 * $t7 = Hi and Lo registers
                    mflo	$t2					# copy Lo to $t2
                    add		$t2, $t2, $a0		# $t2 = $t2 + $a0
                    lw		$t3, 0($t2)		# 
                    

                    # Calcolo indirizzo secondo el in $t4 e contenuto in $t5
                    mult	$t1, $t6			# $t1 * $t6 = Hi and Lo registers
                    mflo	$t4					# copy Lo to $t4
                    add		$t4, $t4, $t0		# $t4 = $t4 + $t1
                    mult	$t4, $t7			# $t4 * $t7 = Hi and Lo registers
                    mflo	$t4					# copy Lo to $t4
                    add		$t4, $t4, $a0		# $t4 = $t4 + $a0
                    lw		$t5, 0($t4)		# 

                    sw		$t5, 0($t2)		# 
                    sw		$t3, 0($t4)		# 
                    addi	$t1, $t1, 1			# $t1 = $t1 + 1

                    bne		$t1, DIM, inverti	# if $t1 != DIM then goto inverti
                    addi	$t0, $t0, 1			# $t0 = $t0 + 1
                    j		calcolaTrasp				# jump to calcolaTrasp
                    
                    
                    
                    
beforePrint:            li		$t6, DIM		# $t6 = DIM
                        li		$t7, 4		    # $t7 = 4
                        mult	$t6, $t6			# $t6 * $t6 = Hi and Lo registers
                        mflo	$t6					# copy Lo to $t6
                        mult	$t6, $t7			# $t6 * $t7 = Hi and Lo registers
                        mflo	$t6					# copy Lo to $t6
                        add		$t6, $t6, $a0		# $t6 = $t6 + $a0
                        move 	$t2, $a0		    # $t2 = $a0
                        j		print				# jump to print
                        
                        
                        

print:              lw		$t3, 0($t2)		# 
                    move 	$a0, $t3		# $a0 = $t3
                    li		$v0, 1		# $v0 = 1
                    syscall
                    addi	$t2, $t2, 4			# $t2 = $t2 + 4
                    la      $a0, stringa
                    addi    $v0, $0, 4
                    syscall
                    bne		$t2, $t6, print	# if $t2 != $t6 then goto print
                    jr		$ra					# jump to $ra

                    
                    
