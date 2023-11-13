                    .data
inizio:             .byte 12, 47
fine:               .byte 18, 14
                    .text
                    .globl main
                    .ent main

main:               li		$a2, 1		# $a2 = 1
                    li		$a3, 40		# $a3 = 40
                    la		$a0, inizio		# 
                    la		$a1, fine		# 
                    subu	$sp, $sp, 4			# $sp = $sp - 4
                    sw		$ra, 0($sp)		# 
                    jal		costoParcheggio				# jump to costoParcheggio and save position to $ra
                    lw		$ra, 0($sp)		# 
                    addu	$sp, $sp, 4			# $sp = $sp + 4
                    jr		$ra					# jump to $ra
                
costoParcheggio:    li		$t2, 60     	# $t2 = 60
                    lb		$t1, 1($a0)		# 
                    sub		$t0, $t2, $t1		# $t0 = $t2 - $t1
                    lb		$t1, 1($a1)		# 
                    add		$t0, $t0, $t1		# $t0 = $t0 + $t1
                    lb		$t1, 0($a0)	
                    addi	$t1, $t1, 1		# $t1 = $t1 + 1
                    lb      $t3, 0($a1)	
                    sub		$t3, $t3, $t1		# $t3 = $t3 - $t1
                    mult	$t3, $t2			# $t3 * $t2 = Hi and Lo registers
                    mflo	$t3					# copy Lo to $t3
                    add		$t0, $t0, $t3		# $t0 = $t0 + $t3
                    div		$t0, $a3			# $t0 / $a3
                    mflo	$t2					# $t2 = floor($t0 / $a3) 
                    mfhi	$t3					# $t3 = $t0 % $a3 
                    mult	$a2, $t2			# $a2 * $t2 = Hi and Lo registers
                    mflo	$v0					# copy Lo to $v0
                    beq		$t3, $a0, return	# if $t3 == $a0 then goto return
                    add		$v0, $v0, $a2		# $v0 = $v0 + $a2
                    j		return				# jump to return
                    
return:             jr		$ra					# jump to $ra
                    
                    
                