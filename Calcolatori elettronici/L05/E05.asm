                .data
wMat: .word 154, 123, 109, 86, 4, 0, 412, -23, -231, 9, 50, 0, 123, -24, 12, 55, -45, 0, 0, 0, 0, 0, 0, 0
NUMCOL:         .byte 6
NUMRIG:         .byte 4
DIMRIG:         .byte 24 

                .text
                .globl main
                .ent main

main:           li		$t0, 0		# $t0 = 0  <------- Contatore
                lb		$t1, NUMCOL		# 
                lb		$t2, NUMRIG		# 
                lb		$t3, DIMRIG		#
                mult	$t3, $t2			# $t3 * $t2 = Hi and Lo registers
                mflo	$t4					# copy Lo to $t4
                 

                j		for1				# jump to for1
                
for1:           beq		$t0, $t4, end	# if $t0 == $t4 then goto end
                li		$t5, 0		# $t4 = 0
                j		for2				# jump to for2
                
for2:           lw		$t6, wMat($t0)		# 
                add		$t5, $t5, $t6 		# $t5 = $t5 + $t6
                addi	$t0, $t0, 4			# $t0 = $t0 + 4

                div		$t0, $t3			# $t0 / $t3
                mfhi	$t6					# $t6 = $t0 % $t3 
                beq		$t6, $0, printRow	# if $t6 == $0 then goto printRow
                j		for2				# jump to for2
                

printRow:       sw		$t5, wMat($t0)		# 
                li $v0, 1
                lw		$t6, wMat($t0)		# 
                move 	$a0, $t6
                syscall
                
                li $v0, 11 
                li 	$a0, '\n'
                syscall
                j		for1				# jump to for1
                


end:            li $v0, 10
                syscall
                .end main