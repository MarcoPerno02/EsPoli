                    .data
vettore: .byte 14, 16, 18, 134, 24, 22, 23, 149, 140, 141, 145, 146 
vettoreCompresso: .space 12
INTERVALLO_QUANT = 10
                    .text
                    .globl main
                    .ent main
main:
                    subu $sp, $sp, 4
                    sw $ra, ($sp)
                    la $a0, vettore
                    li $a1, 12
                    la $a2, vettoreCompresso
                    jal comprimi
                    lw $ra, ($sp)
                    addu $sp, $sp, 4
                    move 	$a0, $v0		# $a0 = $v0
                    li		$v0, 1		# $v0 = 1
                    syscall
                    jr $ra
                    .end main

comprimi:           move    $t2, $a1
                    add		$t2, $a0, $t2		# $t2 = $a0 + $t2
                    move 	$t1, $a0		# $t1 = $a0
                    j		for1			# jump to for1
                    
for1:               subu    $sp, $sp, 8
                    sw      $a0, ($sp)
                    lb		$a0, 0($t1)		#
                    sw      $ra, 4($sp)

                    jal		quantizza				# jump to quantizza and save position to $ra
                    
                    sb		$v0, 0($t1)		# 
                    
                    #move 	$a0, $v0		# $a0 = $v0
                    #li		$v0, 1		# $v0 = 1
                    #syscall

                    lw      $ra, 4($sp)
                    lw      $a0, 0($sp)
                    addu    $sp, $sp, 8

                    addi	$t1, $t1, 1			# $t1 = $t1 + 1
                    bne		$t1, $t2, for1	# if $a0 != $t2 then goto for1
                    j		calcolaLung				# jump to calcolaLung
                    
calcolaLung:        move    $t2, $a1
                    add		$t2, $a0, $t2		# $t1 = $a0 + $t2
                    addi	$t2, $t2, -1			# $t2 = $t2 + -1
                    move 	$t1, $a0		# $t1 = $a0
                    li		$v0, 1		# $v0 = 1
                    j		for2			# jump to for2

for2:               lb		$t3, 0($t1)		# 
                    lb      $t4, 1($t1)
                    bne		$t3, $t4, incrementa	# if $t3 != $t4 then goto incrementa
                    j		contFor2				# jump to contFor2
                    
                    
incrementa:         addi    $v0, $v0, 1
                    j		contFor2				# jump to contFor2
                    

contFor2:           addi	$t1, $t1, 1			# $t1 = $t1 + 1
                    bne		$t1, $t2, for2	# if $a0 != $t2 then goto for2
                    jr		$ra					# jump to $ra
                    
                    

quantizza:          divu $t0, $a0, INTERVALLO_QUANT
                    mulou $v0, $t0, INTERVALLO_QUANT
                    jr $ra 