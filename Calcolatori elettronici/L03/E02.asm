                .data
message:        .asciiz "Inserisci numero: "
messageError:   .asciiz "no minore 255"

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

                li		$t2, 0xFFFFFF00		# $t2 = 0xFFFFFF00
                and		$t3, $t0, $t2		# $t3 = $t0 & $t2
                bne		$t3, $0, error	    # if $t3 != $0 then goto error
                and		$t3, $t1, $t2		# $t3 = $t0 & $t2
                bne		$t3, $0, error	    # if $t3 != $0 then goto error

                j		bitwise				# jump to bitwise
                
bitwise:        nor		$t4, $t1, $t1		# $t4 = ~($t1 | $t1)
                and		$t4, $t0, $t4		# $t4 = $t0 & $t4
                nor		$t4, $t4, $t4		# $t4 = ~($t4 | $t4)
                xor		$t5, $t0, $t1		# $t5 = $t0 ^ $t1
                or		$t4, $t4, $t5		# $t4 = $t4 | $t5
                # Printing out the number
                li $v0, 1
                move $a0, $t4
                syscall
                j		end				# jump to end
                
                


error:          la $a0, messageError
                li $v0, 4
                syscall
                j		end				# jump to end
                

end:            li $v0, 10
                syscall
                .end main
                