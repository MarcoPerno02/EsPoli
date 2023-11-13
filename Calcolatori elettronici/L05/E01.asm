                .data
vett:           .space 80
DIM:            .byte 80

                .text
                .globl main
                .ent main

main:           li $t0, 0 # contatore
                lb		$t3, DIM		# 
                # Caricamento primi 2 valori
                li $t1, 1
                sw $t1, vett($t0)
                lw		$t2, vett($t0)		# 
                li $v0, 1 
                move 	$a0, $t2		# $a0 = $t2
                syscall
                addi $t0, $t0, 4

                sw $t2, vett($t0)
                lw		$t2, vett($t0)
                li $v0, 1 
                move 	$a0, $t2		# $a0 = $t2
                syscall
                addi $t0, $t0, 4
                
                
                j       for
                j		end				# jump to for

for:            beq		$t0, $t3, end	# if $t1 == $t2 then goto end
                move 	$t4, $t0		# $t4 = $t0
                addi	$t4, $t4, -8			# $t4 = $t4 + -8
                li      $t5, 0
                lw      $t6, vett($t4)
                add     $t5, $t5, $t6
                addi	$t4, $t4, 4
                lw      $t6, vett($t4)
                add     $t5, $t5, $t6
                li $v0, 1 
                move 	$a0, $t5
                syscall
                li $v0, 11 
                li 	$a0, '\n'
                syscall
                sw		$t5, vett($t0)		# 
                
                
                addi $t0, $t0, 4
                j		for				# jump to for
                

end:            li $v0, 10
                syscall
                .end main