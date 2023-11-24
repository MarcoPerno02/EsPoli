                .data
var:            .word 0x3FFFFFF0

                .text
                .globl main
                .ent main

main:   lw		$t1, var
        sll		$t1, $t1, 1
        move 	$a0, $t1
        li      $v0, 1
        syscall
        li		$t3, 40		        # $t3 = 40 
        addu	$t2, $t1, $t3			# $t2 = $t1 + $t3
        li      $v0, 1
        move 	$a0, $t2
        syscall
        li $v0, 10
        syscall
        .end main
        
        
