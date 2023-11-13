                .data
message:        .asciiz "Inserisci stringa: "
input:        .space 81
inputSize:    .word 80
car:            .byte 'a'

                .text
                .globl main
                .ent main

main:
                la $a0, message
                li $v0, 4
                syscall

                # Read the string. 
                li $v0, 8
                la $a0, input
                lw $a1, inputSize 
                syscall
                
                la  $t0, input
                li	$t1, 0		# $t1 = 0
                lb	$t2, car
                

for:            lb		$a0, 0($t0)		#
                beqz	$a0, end	# if $a0 == $0 then goto end

                li $v0, 11    # print_character
                syscall

                beq		$a0, $t2, Increment	# if $a0 == $t2 then goto Increment
                j		NoIncrement				# jump to NoIncrement
                

Increment:      addi	$t1, $t1, 1		# $t1 = $t1 + 1
                add		$t0, $t0, 1		# $t0 = $t0 + 1
                j		for				# jump to for

NoIncrement:    add		$t0, $t0, 1		# $t0 = $t0 + 1
                j		for				# jump to for
                
                
end:            move 	$a0, $t1		# $a0 = $t1
                li $v0, 1
                syscall
                li $v0, 10
                syscall
                .end main


