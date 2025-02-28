        .data
v1:     .double 43, 23, 57, 34, 79, 6, 30, 44, 82, 18, 37, 12, 94, 59, 31, 77, 58, 21, 62, 1, 44, 94, 56, 67, 23, 78, 37, 14, 9, 52, 1, 1

v2:     .double 37, 12, 94, 59, 31, 77, 58, 21, 62, 1, 44, 94, 56, 67, 23, 78, 37, 14, 9, 52, 90, 33, 17, 82, 27, 11, 55, 28, 10, 41, 66, 99

v3:     .double 3,  1,  2,  7, 11, 9,  4,  5,  8,  7,  6,  7,  8,  3,  5,  1,  2,  4,  7,  8,  9,  5,  4,  6,  3,  2,  9,  8, 3, 7, 5, 9

v4:     .space 256  # 32 double values (32 * 8 bytes = 256 bytes)

v5:     .space 256  # 32 double values (32 * 8 bytes = 256 bytes)

v6:     .space 256  # 32 double values (32 * 8 bytes = 256 bytes)

        .text
MAIN:
    daddi $t0, R0, 248        # i fo memory       
    daddi $t1, R0, 31       # The for's limit
    daddi $t2, R0, 1        # m variable
    daddi $t8, R0, 0        # b variable
    mtc1 $t8, F8            # cast to double
    cvt.d.l F8, F8
    j LOOP

LOOP:
    l.d F3, v1($t0) # F3 = v1[i]
    J CHECK_DIVISIBILE_BY_THREE

CHECK_DIVISIBILE_BY_THREE:
    daddi $t5, R0, 3

    # Try to divide by 3 and multiply by 3 again the i
    ddiv $t4, $t1, $t5
    dmul $t4, $t4, $t5

    # If the result of division and multiply and then substract to v[i] and you obtain 0 so v[i] was divisible by 3
    dsub $t6, $t1, $t4
    beqz $t6, IS_DIVISIBLE_BY_THREE
    J IS_NOT_DIVISIBLE_BY_THREE

IS_DIVISIBLE_BY_THREE:
    dsllv $t5, $t2, $t1 # ((double) m<< i) 
    mtc1 $t5, F5 # cast to double
    cvt.d.l F5, F5
    div.d F4, F3, F5 # a = (int) v1[i] / ((double) m<< i)

    mtc1 R0, F10 # cast to double
    cvt.d.l F10, F10
    add.d F11, F4, F10

    cvt.l.d F4, F4
    mfc1 $t2, F4 # m = (int) a

    add.d F4, F11, F10

    J CONTINUE

IS_NOT_DIVISIBLE_BY_THREE:
    dmul $t5, $t2, $t1 # ((double) m* i))
    mtc1 $t5, F5 # cast to double
    cvt.d.l F5, F5
    mul.d F4, F3, F5 # a = v1[i] * ((double) m* i))
    
    mtc1 R0, F10 # cast to double
    cvt.d.l F10, F10
    add.d F11, F4, F10

    cvt.l.d F4, F4
    mfc1 $t2, F4 # m = (int) a

    add.d F4, F11, F10

    J CONTINUE

CONTINUE:
    # v4[i] = a*v1[i] - v2[i];
    l.d F6, v2($t0)
    mul.d F5, F4, F3
    sub.d F5, F5, F6
    s.d F5, v4($t0)

    # v5[i] = v4[i]/v3[i] - b;
    l.d F6, v3($t0) # $t6 = v3[i]
    l.d F7, v4($t0) # $t7 = v4[i]
    div.d F5, F7, F6
    sub.d F5, F5, F8
    s.d F5, v5($t0)

    # v6[i] = (v4[i]-v1[i])*v5[i];
    sub.d F6, F7, F3
    mul.d F5, F6, F5
    s.d F5, v6($t0)

    daddi $t0, $t0, -8
    daddi $t1, $t1, -1 

    daddi $t5, R0, -1
    beq $t1, $t5, END

    J LOOP

END:
    HALT