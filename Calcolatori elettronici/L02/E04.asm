                .data
                .text
                .globl main
                .ent main

main:           li		$t0, 0		# $t0 = 0
                li		$t1, 10		# $t1 = 10
                li      $t2, 0

for:            beq		$t2, $t1, end	# if $t2 == $t1 then goto end
                add		$t0, $t0, $t2		# $t0 = $t0 + $t2
                li      $v0, 1
                move 	$a0, $t0
                syscall
                addi	$t2, $t2, 1			# $t2 = $t2 + 1
                j		for				# jump to for
                
                

end:            li $v0, 10
                syscall
                .end main
