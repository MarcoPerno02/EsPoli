        .data
v1:     .double 43, 23, 57, 34, 79, 6, 30, 44, 82, 18, 37, 12, 94, 59, 31, 77, 58, 21, 62, 1, 44, 94, 56, 67, 23, 78, 37, 14, 9, 52, 90, 33

v2:     .double 37, 12, 94, 59, 31, 77, 58, 21, 62, 1, 44, 94, 56, 67, 23, 78, 37, 14, 9, 52, 90, 33, 17, 82, 27, 11, 55, 28, 10, 41, 66, 99

v3:     .double 3,  1,  2,  7, 11, 9,  4,  5,  8,  7,  6,  7,  8,  3,  5,  1,  2,  4,  7,  8,  9,  5,  4,  6,  3,  2,  9,  8, 3, 7, 5, 9

v4:     .space 256  # 32 double values (32 * 8 bytes = 256 bytes)

v5:     .space 256  # 32 double values (32 * 8 bytes = 256 bytes)

v6:     .space 256  # 32 double values (32 * 8 bytes = 256 bytes)

        .text
MAIN:
    dadd $t0, R0, R0        # i = 0       
    daddi $t1, R0, 32       # The for's limit
    j CALULCATE # 3 + 6

CALULCATE:
    # v4[i] = v1[i]*v1[i] – v2[i];
    # ld R1, v1($t0)
    # ld R2, v1($t0)
    # ld R3, v2($t0)

    l.d F1, v1($t0)
    l.d F2, v1($t0)
    l.d F3, v2($t0)
    mul.d F4, F1, F2
    sub.d F4, F4, F3
    s.d F4, v4($t0) # 4 + 4 + 6 = 14

    # v5[i] = v4[i]/v3[i] – v2[i];
    l.d F1, v4($t0)
    l.d F2, v3($t0)
    l.d F3, v2($t0)
    div.d F4, F1, F2
    sub.d F4, F4, F3
    s.d F4, v5($t0) # 4 + 4 + 30 = 38

    # # v6[i] = (v4[i]-v1[i])*v5[i];
    l.d F1, v4($t0)
    l.d F2, v1($t0)
    l.d F3, v5($t0)
    sub.d F4, F1, F2
    mul.d F4, F4, F3
    s.d F4, v6($t0) # 4 + 4 + 6 = 14

    daddi $t0, $t0, 8
    daddi $t1, $t1, -1    
    bnez $t1, CALULCATE   # (2 + 1) + 2 + 14 + 38 + 14 = 71 

    HALT # - 1


