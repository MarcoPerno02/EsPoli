                .data
outputNoPalindromo: .asciiz "No"
outputSiPalindromo: .asciiz "Si"
                .text
                .globl main
                .ent main

main:           li		$t1, 0		    # $t1 = 0
                move 	$t0, $sp		# $t0 = $sp
                move 	$s0, $sp		# $s0 = $sp
                j		ciclo_lettura	# jump to ciclo_lettura
                
ciclo_lettura:  li		$v0, 12		    # $v0 = 12
                syscall
                beq		$v0, '\n', pre_verifica	# if $v0 == $t1 then goto pre_verifica
                addi    $t1, $t1, 1
                subu    $sp, $sp, 4
                sw      $v0, ($sp)
                b       ciclo_lettura

pre_verifica:   li		$t2, 2		# $t2 = 2
                div		$t1, $t2			# $t1 / $t2
                mflo	$t1					# $t1 = floor($t1 / $t2) 
                j		verifica				# jump to verifica
                
verifica:       subu    $t0, $t0, 4		# $t0 = $sp - 4
                lw		$t2, ($t0)		# 
                lw		$t3, ($sp)		# 
                bne		$t2, $t3, noPal	# if $t2 != $t3 then goto noPal
                
                addu    $sp, $sp, 4		# $sp = $sp + 4
                addi    $t1, $t1, -1
                beq		$t1, $0, pal	# if $t1 == $0 then goto pal
                j		verifica				# jump to verifica
                
noPal:
                la $a0, outputNoPalindromo
                b stampa

pal:            la $a0, outputSiPalindromo
                b stampa

stampa:
                li $v0, 4
                syscall
                move $sp, $s0 # ripristino lo stack pointer
                li $v0, 10
                syscall
                .end main

                

                
