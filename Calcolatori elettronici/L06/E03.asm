                .data
msg1:           .asciiz "ok"
msg2:           .asciiz "no ok"
                .text
                .globl main
                .ent main

main:           li		$t0, 1		# $t0 = 1
                li		$t1, 1		# $t1 = -3
                li		$t2, 8		# $t2 = 1
                
                mult	$t1, $t1			# $t1 * $t1 = Hi and Lo registers
                mflo	$t1					# copy Lo to $t1
                li		$t3, 4		        # $t3 = 4
                mult	$t0, $t3			# $t0 * $t3 = Hi and Lo registers
                mflo	$t0					# copy Lo to $t0
                mult	$t0, $t2			# $t0 * $t2 = Hi and Lo registers
                mflo	$t0					# copy Lo to $t0
                slt		$t0, $t0, $t1		# $t0 = ($t0 < $t1) ? 1 : 0
                beq		$t0, $0, noSolReal	# if $t0 == $0 then goto noSolReal
                j		solReal				# jump to solReal
                
solReal:        la $a0, msg1
                b stampa    

noSolReal:      la $a0, msg2
                b stampa    

stampa:
                li $v0, 4
                syscall
                li $v0, 10
                syscall
                .end main