                .data
                .text
                .globl main
                .ent main

main:           li		$t0, 0		# $t0 = 0
                li		$t2, 10		# $t2 = 8
                
                j		forStampaTriangolo				# jump to forStampaTriangolo

forStampaTriangolo:         beq		$t0, $t2, initForStampaQuadrato	# if $t0 == $t2 then goto initForStampaQuadrato
                            subu    $sp, $sp, 4		# $t0 = $sp - 4
                            sw		$t0, 0($sp)		# 
                            move 	$t1, $t0		# $t1 = $t0     <---- limite come secondo for
                            addi	$t1, $t1, 1		# $t1 = $t1 + 1
                            

                            li		$t0, 0		# $t0 = 0  <--- lo inizializzo come indice
                            move 	$a0, $t2		# $a0 = $t2
                            jal		stampaAsterischi				# jump to stampaAsterischi and save position to $ra
                            
                            lw		$t0, 0($sp)		# 
                            addu    $sp, $sp, 4

                            li		$v0, 11		# $v0 = 11
                            li		$a0, '\n'		# $a0 = '\n'
                            syscall

                            addi	$t0, $t0, 1			# $t0 = $t0 + 1
                            j		forStampaTriangolo				# jump to forStampaTriangolo
                            
stampaAsterischi:           move 	$t3, $a0		# $t3 = $a0
                            li		$v0, 11		# $v0 = 11
                            li		$a0, 42		# $a0 = 42
                            syscall
                            move 	$a0, $t3		# $a0 = $t3
                            
                            addi	$t0, $t0, 1			# $t0 = $t0 + 1
                            bne		$t0, $t1, stampaAsterischi	# if $t0 != $t1 then goto stampaAsterischi
                            jr		$ra					# jump to $ra

initForStampaQuadrato:      li		$t0, 0		# $t0 = 0
                            j		forStampaQuadrato				# jump to forStampaQuadrato
                            

forStampaQuadrato:          beq		$t0, $t2, end
                            subu    $sp, $sp, 4		# $t0 = $sp - 4
                            sw		$t0, 0($sp)		# 
                            move 	$t1, $t2		# $t1 = $t2

                            li		$t0, 0		# $t0 = 0  <--- lo inizializzo come indice
                            move 	$a0, $t2		# $a0 = $t2
                            jal		stampaAsterischi				# jump to stampaAsterischi and save position to $ra
                            
                            lw		$t0, 0($sp)		# 
                            addu    $sp, $sp, 4

                            li		$v0, 11		# $v0 = 11
                            li		$a0, '\n'		# $a0 = '\n'
                            syscall

                            addi	$t0, $t0, 1			# $t0 = $t0 + 1
                            j		forStampaQuadrato				# jump to forStampaQuadrato
                            
end:                        li $v0, 10
                            syscall
                            .end main
                            
