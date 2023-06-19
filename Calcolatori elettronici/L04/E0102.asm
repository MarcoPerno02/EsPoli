                .data
message:        .asciiz "Inserisci carattere: "
carattere:      .asciiz "carattere\n"
numero:         .asciiz "numero\n"
numero_tot:     .space 5


                .text
                .globl main
                .ent main

main:           
                
                j		read				# jump to read
                
read:           li $v0, 4
                la $a0, message
                syscall

                li $v0, 12
                syscall

                slti	$t0, $v0, 48			# $t0 = ($v0 < 48) ? 1 : 0
                bne		$t0, $0, char	# if $t0 != $0 then goto char
                slti	$t0, $v0, 58
                beq		$t0, $0, char	# if $t0 == $0 then goto char
                j		number				# jump to number
                
                

char:           li $v0, 4
                la $a0, carattere
                syscall
                j		end				# jump to read
                

number:         move 	$t1, $v0		# $t1 = $v0
                addi	$t1, $t1, -48			# $t1 = $t1 - 48
                lw		$t2, numero_tot		# 
                li		$t4, 10		# $t4 = 10
                mult	$t2, $t4			# $t2 * $t4 = Hi and Lo registers
                mflo	$t2					# copy Lo to $t2			# copy Lo to $t1
                add	$t2, $t2, $t1	    # $t2 = $t2 + $t1
                sw		$t2, numero_tot		# 
                j		read				# jump to read
                
    

end:            li $v0, 10
                syscall
                .end main