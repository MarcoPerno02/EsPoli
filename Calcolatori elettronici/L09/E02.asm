                    .data
anni:               .word 1945, 2008, 1800, 2006, 1748, 1600
risultato:          .byte 0, 0, 0, 0, 0, 0
                    .text
                    .globl main
                    .ent main

main:               la		$a0, anni		    # 
                    la		$a1, risultato		# 
                    li		$a2, 6		        # $a2 = 6
                    subu	$sp, $sp, 4			# $sp = $sp - 4
                    sw		$ra, 0($sp)		    # 
                    li		$t0, 0		        # $t0 = 0
                    jal		bisestile			# jump to bisestile and save position to $ra
                    lw		$ra, 0($sp)		    # 
                    addu	$sp, $sp, 4			# $sp = $sp + 4
                    li		$t0, 0		        # $t0 = 0
                    la		$a1, risultato		# 
                    j		stampa				# jump to stampa  

stampa:             lb		$t1, 0($a1)		    # 
                    li		$v0, 1		        # $v0 = 1
                    move 	$a0, $t1		    # $a0 = $t1
                    syscall
                    addi	$a1, $a1, 1			# $a1 = $a1 + 1
                    addi	$t0, $t0, 1			# $t0 = $t0 + 1
                    bne		$t0, $a2, stampa	# if $t0 != $a2 then goto stampa
                    jr		$ra					# jump to $ra  

bisestile:          lw		$t1, 0($a0)		    # 
                    li		$t2, 100		    # $t2 = 100
                    div		$t1, $t2			# $t1 / $t2
                    mfhi	$t3					# $t3 = $t1 % $t2 
                    beq		$t3, $0, div400	# if $t3 == $0 then goto div400
                    li		$t2, 4		        # $t2 = 4
                    div		$t1, $t2			# $t1 / $t2
                    mfhi	$t3					# $t3 = $t1 % $t2 
                    beq		$t3, $0, bisOk	    # if $t3 == $0 then goto bisOk
                    j		bisNo				# jump to bisNo

div400:             li		$t2, 400		    # $t2 = 400
                    div		$t1, $t2			# $t1 / $t2
                    mfhi	$t3					# $t3 = $t1 % $t2 
                    beq		$t3, $0, bisOk	    # if $t3 == $a0 then goto bisOk
                    j		bisNo				# jump to bisNo

bisOk:              li		$t4, 1		# $t4 = 1
                    sb		$t4, 0($a1)		# 
                    j		checkReturn				# jump to checkReturn

bisNo:              li		$t4, 0		# $t4 = 0
                    sb		$t4, 0($a1)		# 
                    j		checkReturn				# jump to checkReturn
                    
checkReturn:
                    addi	$t0, $t0, 1			# $t0 = $t0 + 1
                    addi	$a0, $a0, 4			# $a0 = $a0 + 4
                    addi	$a1, $a1, 1 		# $a1 = $a1 + 1
                    bne		$t0, $a2, bisestile	# if $t0 != $a2 then goto bisestile
                    jr		$ra					# jump to $ra
                    
                    
