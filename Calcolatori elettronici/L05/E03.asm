                .data
vett1:          .space 16
vett2:          .space 16
mat:            .space 48
DIM:            .byte  16
                .text
                .globl main
                .ent main                             

main:           j loadVett1

loadVett1:      li		$t0, 0		# $t0 = 0
                li		$t1, 1		        # $t1 = 1
                sb		$t1, vett1($t0)		# 
                addi	$t0, $t0, 4			# $t0 = $t0 + 4
                li		$t1, 2		        # $t1 = 2
                sb		$t1, vett1($t0)		# 
                addi	$t0, $t0, 4			# $t0 = $t0 + 4
                li		$t1, 3		        # $t1 = 3
                sb		$t1, vett1($t0)		# 
                addi	$t0, $t0, 4			# $t0 = $t0 + 4
                li		$t1, 4		        # $t1 = 4
                sb		$t1, vett1($t0)		# 
                addi	$t0, $t0, 4			# $t0 = $t0 + 4
                j		loadVett2			# jump to loadVett2
                
loadVett2:      li		$t0, 0		# $t0 = 0
                li		$t1, 1		        # $t1 = 1
                sb		$t1, vett2($t0)		# 
                addi	$t0, $t0, 4			# $t0 = $t0 + 4
                li		$t1, 2		        # $t1 = 2
                sb		$t1, vett2($t0)		# 
                addi	$t0, $t0, 4			# $t0 = $t0 + 4
                li		$t1, 3		        # $t1 = 3
                sb		$t1, vett2($t0)		# 
                addi	$t0, $t0, 4			# $t0 = $t0 + 4
                li		$t1, 4		        # $t1 = 4
                sb		$t1, vett2($t0)		# 
                addi	$t0, $t0, 4			# $t0 = $t0 + 4
                j		setIndexes		    # jump to setIndexes
                
                

setIndexes:     # Indici
                li		$t0, 0		# $t0 = 0 
                li		$t1, 0		# $t1 = 0
                li      $t2, 0      # $t2 = 0

                # DIM
                lb		$t3, DIM	# 
                
                j		for1				# jump to for1

updateFor1:     li		$t1, 0		        # $t1 = 0
                addi	$t0, $t0, 4			# $t0 = $t0 + 4
                j		for1				# jump to for1
                

for1:           beq		$t0, $t3, printMat	# if $t0 == $t1 then goto printMat
                j		for2				# jump to for2

for2:           beq		$t1, $t3, updateFor1	# if $t1 == $t3 then goto target
                lw		$t4, vett1($t0)		# 
                lw      $t5, vett2($t1)	
                mult	$t4, $t5			# $t4 * $t5 = Hi and Lo registers
                mflo	$t4					# copy Lo to $t4
                sw		$t4, mat($t2)		# 
                addi	$t2, $t2, 4			# $t2 = $t2 + 4
                addi	$t1, $t1, 4			# $t1 = $t1 + 4
                j		for2				# jump to for2
                


printMat:       li      $t2, 0              # $t2 = 0
                li		$t4, 4		        # $t4 = 4
                mult	$t3, $t4			# $t3 * $t4 = Hi and Lo registers
                mflo	$t3					# copy Lo to $t3
                li      $t4, 16		        # $t4 = 16
                j		forPrintMat		    # jump to forPrintMat
                
forPrintMat:    beq		$t2, $t3, end	   # if $t2 == $t3 then goto end
                li		$v0, 1		        # $v0 = 1
                lw		$a0, mat($t2)		# 
                syscall
                li $v0, 11 
                li 	$a0, ' '
                syscall
                addi	$t2, $t2, 4			# $t2 = $t2 + 4
                div		$t2, $t4			# $t2 / $t4
                mfhi	$t5					# $t5 = $t2 % $t4 
                beq		$t5, $0, printNewRow	# if $t5 == $0 then goto printNewRow
                j		forPrintMat			# jump to forPrintMat
                
printNewRow:    li $v0, 11 
                li 	$a0, '\n'
                syscall
                j		forPrintMat			# jump to forPrintMat
                

end:            li $v0, 10
                syscall
                .end main
