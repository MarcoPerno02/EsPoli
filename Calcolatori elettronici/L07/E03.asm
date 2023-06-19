                .data
str1:           .asciiz "ciao\n"
                .text
                .globl main
                .ent main

main:           li		$t0, 0		# $t0 = 0
                j       printaCarMaiusc

printaCarMaiusc:    lb		$a0, str1($t0)		#
                    li		$t1, '\n'		# 
                    beq		$a0, $t1, end	# if $a0 == $t1 then goto end
                    
                    jal		carMaiusc				# jump to carMaiusc and save position to $ra
                    addi	$t0, $t0, 1			# $t0 = $t0 + 1
                    j		printaCarMaiusc				# jump to printaCarMaiusc
                    

carMaiusc:          li		$v0, 11		        # $v0 = 11
                    addi	$a0, $a0, -32		# $a0 = $a0 + -32
                    syscall
                    jr		$ra					# jump to $ra

end:                        li $v0, 10
                            syscall
                            .end main
                    
                    