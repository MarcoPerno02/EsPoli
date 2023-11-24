                        .data
stringa1:               .asciiz "calcolatori elettronici0"
stringa2:               .asciiz "raccolta0"
                        .text 
                        .globl main 
                        .ent main 

main:                   subu $sp, $sp, 4 
                        sw $ra, ($sp) 
                        li		$v0, 0		# $v0 = 0
                        la $a0, stringa1 
                        la $a1, stringa2 
                        move 	$t0, $a1		# $t0 = $a1
                        li		$t7, '0'		# $t7 = '0'
                        jal cercaSequenza 

                        lw $ra, ($sp) 
                        addiu $sp, $sp, 4 

                        move 	$a0, $v0		# $a0 = $v0
                        li		$v0, 1		# $v0 = 1
                        syscall
                        jr $ra 
.end main


cercaSequenza:          lb		$t1, 0($t0)		# 
                        move    $t4, $a0
                        move    $t2, $t0
                        li		$t6, 0		# $t6 = 0
                        
                        j       controllaDim
                        slt		$v0, $t6, $s1		# $v0 = ($t6 < $s1) ? 1 : 0
                        bne		$s1, $0, target	# if $s1 != $0 then goto nuovoMax
                        j		cercaSequenzaFine				# jump to cercaSequenzaFine
                        

nuovoMax:               move    $v0, $t6
                        j		cercaSequenzaFine				# jump to cercaSequenzaFine
                        


cercaSequenzaFine:      addi	$t0, $t0, 1			# $t0 = $t0 + 1
                        lb		$t1, 0($t0)		# 
                        bne	    $t1, $t7, cercaSequenza	# if $t1 != '0' then goto cercaSequenza
                        jr		$ra					# jump to $ra

controllaDim:           lb		$t5, 0($t4)		#
                        move 	$a0, $t5		# $a0 = $t5
                        li $v0, 11    # print_character
                        syscall
                        lb		$t3, 0($t2)		# 
                        beq		$t5, $t3, aggiungi	# if $t5 == 4t3 then goto aggiungi
                        j		incrementaIndiceA0				# jump to incrementaIndiceA0
                        

aggiungi:               addi	$t6, $t6, 1			# $t6 = $t6 + 1
                        addi	$t2, $t2, 1			# $t2 = $t2 + 1
                        j       incrementaIndiceA0

incrementaIndiceA0:     addi	$t4, $t4, 1			# $t4 = $t4 + 1
                        lb		$t5, 0($t4)		#
                        lb		$t3, 0($t2)		# 
                        
                        
                        beq		$t5, $t7, cercaSequenza	# if $t5 == $t7 then goto cercaSequenza
                        beq		$t3, $t7, cercaSequenza	# if $t5 == $t7 then goto cercaSequenza
                        j		controllaDim				# jump to controllaDim
                        
                        

                        
                        
                        


                        
                        

                        
   
