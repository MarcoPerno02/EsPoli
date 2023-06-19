                .data
message:        .asciiz "Inserisci numero: "
messageEven:    .asciiz "Pari"
messageOdd:     .asciiz "Dispari"
num:            .byte 0

                .text
                .globl main
                .ent main

main:           la $a0, message
                li $v0, 4
                syscall

                li $v0, 5
                syscall

                # Moving the integer input to another register
                move $t0, $v0
                li		$t1, 0x0000001		# $t1 = 0x0000001
                and		$t2, $t0, $t1		# $t2 = $t0 & $t1
                beq		$t2, $0, even	# if $t2 == $0 then goto even
                j		odd				# jump to odd
                

even:           la $a0, messageEven
                li $v0, 4
                syscall
                j		end				# jump to end
                

odd:            la $a0, messageOdd
                li $v0, 4
                syscall
                j		end				# jump to end
                

end:            li $v0, 10
                syscall
                .end main