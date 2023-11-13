                .data
message:        .asciiz ", "
num0:           .word 4
num1:           .word 55
num2:           .word 16


                .text
                .globl main
                .ent main

main:           lw		$t0, num0		# 
                lw		$t1, num1		# 
                lw		$t2, num2		# 
                
                j		firstIf				# jump to firstIf
                

firstIf:        ble		$t0, $t1, secondIf	# if $t0 <= $t1 then goto secondIf
                move 	$t3, $t0		# $t3 = $t0
                move 	$t0, $t1		# $t0 = $t1
                move 	$t1, $t3		# $t1 = $t3


secondIf:       ble		$t0, $t2, thirdIf	# if $t0 <= $t2 then goto thirdIf
                move 	$t3, $t0		# $t3 = $t0
                move 	$t0, $t2		# $t0 = $t2
                move 	$t2, $t3		# $t2 = $t3

thirdIf:        ble		$t1, $t2, end	# if $t1 <= $t2 then goto end
                move 	$t3, $t1		# $t3 = $t1
                move 	$t1, $t2		# $t1 = $t2
                move 	$t2, $t3		# $t2 = $t3
                j		end				# jump to end
                

end:            li $v0, 1
                move $a0, $t0
                syscall
                la $a0, message
                li $v0, 4
                syscall
                li $v0, 1
                move $a0, $t1
                syscall
                la $a0, message
                li $v0, 4
                syscall
                li $v0, 1
                move $a0, $t2
                syscall
                li $v0, 10
                syscall
                .end main
