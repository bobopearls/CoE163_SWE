find_min_combi:
        addi    sp, sp, -48
        sw      ra, 44(sp)
        sw      s0, 40(sp)
        addi    s0, sp, 48
        sw      a0, -12(s0)
        sw      a1, -16(s0)
        sw      a2, -20(s0)
        li      a0, 0
        sw      a0, -24(s0)
        sw      a0, -28(s0)
        j       .LBB0_1
.LBB0_1:
        lw      a0, -28(s0)
        lw      a1, -12(s0)
        bge     a0, a1, .LBB0_12
        j       .LBB0_2
.LBB0_2:
        lw      a0, -16(s0)
        lui     a1, 419430
        addi    a1, a1, 1639
        mulh    a2, a0, a1
        srli    a3, a2, 31
        srai    a2, a2, 2
        add     a3, a3, a2
        li      a2, 10
        mul     a3, a3, a2
        sub     a0, a0, a3
        sw      a0, -32(s0)
        lw      a0, -20(s0)
        mulh    a1, a0, a1
        srli    a3, a1, 31
        srai    a1, a1, 2
        add     a1, a1, a3
        mul     a1, a1, a2
        sub     a0, a0, a1
        sw      a0, -36(s0)
        lw      a0, -32(s0)
        lw      a1, -36(s0)
        sub     a0, a0, a1
        sw      a0, -40(s0)
        lw      a0, -40(s0)
        bgez    a0, .LBB0_4
        j       .LBB0_3
.LBB0_3:
        lw      a0, -36(s0)
        lw      a1, -32(s0)
        sub     a0, a0, a1
        sw      a0, -40(s0)
        j       .LBB0_4
.LBB0_4:
        lw      a1, -40(s0)
        li      a0, 10
        sub     a0, a0, a1
        sw      a0, -44(s0)
        lw      a1, -40(s0)
        lw      a0, -44(s0)
        bge     a0, a1, .LBB0_6
        j       .LBB0_5
.LBB0_5:
        lw      a1, -44(s0)
        lw      a0, -24(s0)
        add     a0, a0, a1
        sw      a0, -24(s0)
        j       .LBB0_10
.LBB0_6:
        lw      a0, -40(s0)
        lw      a1, -44(s0)
        bge     a0, a1, .LBB0_8
        j       .LBB0_7
.LBB0_7:
        lw      a1, -40(s0)
        lw      a0, -24(s0)
        add     a0, a0, a1
        sw      a0, -24(s0)
        j       .LBB0_9
.LBB0_8:
        j       .LBB0_9
.LBB0_9:
        j       .LBB0_10
.LBB0_10:
        lw      a0, -16(s0)
        lui     a1, 419430
        addi    a1, a1, 1639
        mulh    a0, a0, a1
        srli    a2, a0, 31
        srai    a0, a0, 2
        add     a0, a0, a2
        fcvt.d.w        fa5, a0
        fcvt.w.d        a0, fa5, rdn
        sw      a0, -16(s0)
        lw      a0, -20(s0)
        mulh    a0, a0, a1
        srli    a1, a0, 31
        srai    a0, a0, 2
        add     a0, a0, a1
        fcvt.d.w        fa5, a0
        fcvt.w.d        a0, fa5, rdn
        sw      a0, -20(s0)
        j       .LBB0_11
.LBB0_11:
        lw      a0, -28(s0)
        addi    a0, a0, 1
        sw      a0, -28(s0)
        j       .LBB0_1
.LBB0_12:
        lw      a0, -24(s0)
        lw      ra, 44(sp)
        lw      s0, 40(sp)
        addi    sp, sp, 48
        ret

main:
        addi    sp, sp, -32
        sw      ra, 28(sp)
        sw      s0, 24(sp)
        addi    s0, sp, 32
        li      a0, 0
        sw      a0, -28(s0)
        sw      a0, -12(s0)
        lui     a0, %hi(.L.str)
        addi    a0, a0, %lo(.L.str)
        addi    a1, s0, -16
        addi    a2, s0, -20
        addi    a3, s0, -24
        call    scanf
        lw      a0, -16(s0)
        lw      a1, -20(s0)
        lw      a2, -24(s0)
        call    find_min_combi
        mv      a1, a0
        lui     a0, %hi(.L.str.1)
        addi    a0, a0, %lo(.L.str.1)
        call    printf
        lw      a0, -28(s0)
        lw      ra, 28(sp)
        lw      s0, 24(sp)
        addi    sp, sp, 32
        ret

.L.str:
        .asciz  "%d %d %d"

.L.str.1:
        .asciz  "%d"