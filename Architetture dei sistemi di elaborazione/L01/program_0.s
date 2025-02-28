    .data                   # Data section
v1:  	.byte    2, 6, -3, 11, 9, 18, -13, 16, 5, 1
v2:  	.byte    4, 2, -13, 3, 9, 9, 7, 16, 4, 7
v3:     .space 10 
flag1:  .byte 1
flag2:  .byte 1
flag3:  .byte 1

    .text                   # Code section

MAIN:
    daddui $t7, R0, 01       # Load immediate 1 into $t7
    sb $t7, flag1(R0) 
    sb $t7, flag2(R0) 
    sb $t7, flag3(R0) 


    dadd $t0, R0, R0        # $t0 <- 0. It is 'i'
    daddui $t1, R0, 10      # $t1 <- 10 It is the length of 'v1' and 'v2'
    dadd $t3, R0, R0        # $t3 <- 0  It is the counter of the v3

LOOP:
    j SEARCH_SETUP

END_LOOP:
    daddi $t0, $t0, 1       # Increment $t0
    daddi $t1, $t1, -1      # Decrement $t1
    bnez $t1, LOOP          # Jump to LOOP if $t1 is not 0

    lb $t7, flag1(R0) 
    bnez $t7, RESET_FLAG2_FLAG3

    HALT

SEARCH_SETUP:
    lb $t2, v1($t0)         # load in $t2 the element in v1 at pos $t0

    dadd $t4, R0, R0
    daddui $t5, R0, 10

    beqz R0, SEARCH

SEARCH:
    lb $t6, v2($t4)         # load in $t6 the element in v2 at pos $t4

    beq $t6, $t2, FOUND_OCCURENCE          # Jump to FOUND_OCCURENCE if $t5 is not 0

    daddi $t4, $t4, 1       # Increment $t4
    daddi $t5, $t5, -1      # Decrement $t5

    bnez $t5, SEARCH

    j END_LOOP                  # Return to the point after jal

FOUND_OCCURENCE:
    # Isolate the lower byte of $t2
    # andi $t7, $t2, 0xFF     # $t7 = $t2 & 0xFF (Extract the lowest byte)

    sb $t2, v3($t3)         # Save $t2 in v3
    daddi $t3, $t3, 1       # Increment $t3, The counter of occurences

    daddui $t6, R0, 0        # Load immediate 0 into $t6
    sb $t6, flag1(R0)        # Store 0 in flag1 (set the flag)

    daddi $t7, R0, 2
    slt $t7, $t3, $t7
    beq $t7, $zero, ANALYITICS

    j END_LOOP                  # Return to the point after jal


# Analytics Section

ANALYITICS:
    j CHECK_FLAG2

CHECK_FLAG2:
    daddi $t4, $t3, -2
    daddi $t5, $t3, -1

    lb $t4, v3($t4)         # load penultimate elemnt in v3
    lb $t5, v3($t5)         # load last element in v3

    slt $t6, $t5, $t4       # Set $t6 to 1 if $t5 < $t4

    bne $t6, $zero, SET_FLAG2  # $t5 <= $t4 -> NOT GOOD -> SET FLAG2 TO 0

    beq $t5, $t4, SET_FLAG2     # Case in which are equals

    j CHECK_FLAG3

SET_FLAG2:
    daddui $t7, R0, 0        # Load immediate 0 into $t7
    sb $t7, flag2(R0)        # Store 0 in flag2 (set the flag)

    j CHECK_FLAG3


CHECK_FLAG3:
    daddi $t4, $t3, -2
    daddi $t5, $t3, -1

    lb $t4, v3($t4)         # load penultimate elemnt in v3
    lb $t5, v3($t5)         # load last element in v3

    slt $t6, $t4, $t5       # Set $t6 to 1 if $t4 < $t5

    bne $t6, $zero, SET_FLAG3  # $t4 < $t5 == 0 NOT GOOD -> SET FLAG3 TO 0

    j END_LOOP

SET_FLAG3:
    daddui $t7, R0, 0        # Load immediate 0 into $t7
    sb $t7, flag3(R0)        # Store 0 in flag3 (set the flag)

    j END_LOOP

RESET_FLAG2_FLAG3:
    daddui $t7, R0, 0       # Load immediate 1 into $t7
    sb $t7, flag2(R0) 
    sb $t7, flag3(R0)

    HALT