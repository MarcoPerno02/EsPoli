                    .data
DIM = 8
vet1:               .byte 1 1 0 1 1 1 0 1
vet2:               .byte 1 1 0 0 1 0 0 1

                    .text
                    .globl main
                    .ent main
                    
                    
                    
                    
main:               subu	$sp, $sp, 8			# $sp = $sp - 8
                    li		$t1, 8		# $t1 = 8
                    sw		$ra, 0($sp)		# 
                    sw      $t1, 4($sp)
                    la		$a0, vet1		# 
                    la		$a1, vet2		# 
                    li		$t0, 0		# $t0 = 0
                    jal		hamming				# jump to hamming and save position to $ra
                    lw		$ra, 0($sp)		# 
                    lw		$t1, 4($sp)		# 
                    addu	$sp, $sp, 8			# $sp = $sp + 8
                    jr		$ra					# jump to $ra

hamming:            lb		$t1, 0($a0)		    # 
                    lb		$t2, 0($a1)		# 
                    addi	$t0, $t0, 1			# $t0 = $t0 + 1
                    addi	$a0, $a0, 1			# $a0 = $a0 + 1+
                    addi	$a1, $a1, 1			# $a1 = $a1 + 1
                    bne		$t0, DIM, hamming	# if $t0 != DIM then goto hamming
                    jr		$ra					# jump to $ra
                    
                    


                    
