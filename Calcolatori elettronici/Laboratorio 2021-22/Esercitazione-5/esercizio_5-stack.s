
.data
.text
.globl main
.ent main

main: 
        li      $s0, 0xF0
        li      $s1, 0xF1
        li      $s2, 0xF2
        
        subu    $sp, $sp, 12
        sw      $s0, ($sp) 
        sw      $s1, 4($sp) 
        sw      $s2, 8($sp)
        
        lw      $s0, ($sp) 
        lw      $s1, 4($sp) 
        lw      $s2, 8($sp)  
        addu    $sp, $sp, 12
        
        li $v0, 10
        syscall
.end main