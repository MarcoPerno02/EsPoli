                .data
message:        .asciiz "Inserisci un numero: "

                .text
                .globl main
                .ent main

main:           la $a0, message
                li $v0, 4
                syscall
                li $v0, 5
                syscall
                move $t0, $v0

                la $a0, message
                li $v0, 4
                syscall
                li $v0, 5
                syscall
                move $t1, $v0

                slt		$t2, $t0, $t1		# $t2 = ($t0 < $t1) ? 1 : 0
                bne		$t2, $0, L1	# if $t2 != $0 then goto L1
                sub		$t2, $t1, $t0		# $t2 = $t1 - $t0
                j		end				# jump to end
L1:
                add		$t2, $t1, $t0		# $t2 = $t1 + $t0
                j		end				# jump to end
                

end:            li      $v0, 1
                move 	$a0, $t2
                syscall
                li $v0, 10
                syscall
                .end main
    