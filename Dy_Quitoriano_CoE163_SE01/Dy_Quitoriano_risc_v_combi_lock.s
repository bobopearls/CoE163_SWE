# RISC-V code to find the minimum combinational 
# number of times to unlock a lock based on the given C code  

.text
.globl main

main:
    # read num_dials
    li a0, 3
    li a1, 123
    li a2, 321

    jal find_min_combi
    
    # exit the program:
    addi a7, x0, 10
    ecall # return 0 



# =====================================================
# FUNCTION: find_min_combi
# Arguments:
#   a0 = num_dials, int
#   a1 = start, int
#   a2 = end, int
# Returns:
#   a0 = turns, int
# =====================================================
find_min_combi:
    # prologue (start of the program) -> this is where we do all the necessary set ups (ready the registers)
    addi sp, sp, -20
    sw   ra, 16(sp)
    sw   s0, 12(sp)
    sw   s1, 8(sp)
    sw   s2, 4(sp)
    sw   s3, 0(sp)

    # initialize variables:
    li s0, 0 # load number of turns = 0
    li s1, 0 # load i = 0

    # load a value of integer 10 to one of the registers 
    li s2, 10

loop_start: # main loop where the bulk of the program is in
    # case 1: if i > num_dials, break - branch to end the loop
    bge s1, a0, loop_end

    # case 2: if i < num_dials, do the main loop
    mv t0, a1 

    remainder_sub_start:
        blt  t0, s2, remainder_start_done 
        addi t0, t0, -10 
        j    remainder_sub_start 

    remainder_start_done:
        mv t1, a2 
    
    remainder_sub_end:
        blt  t1, s2, remainder_end_done
        addi t1, t1, -10 
        j    remainder_sub_end
    
    remainder_end_done:
        sub t2, t0, t1 
        bge t2, zero, abs_val_done 
        sub t2, zero, t2

    abs_val_done:
        sub t3, s2, t2

        ble t2, t3, use_dist
        add s0, s0, t3
        j after_add
    
    use_dist:
        add s0, s0, t2

    after_add:
        # a1 = a1 /10 
        mv t4, a1
        li t5, 0

    div_start_loop:
        blt t4, s2, div_start_done
        addi t4, t4, -10
        addi t5, t5, 1
        j div_start_loop

    div_start_done:
        mv a1, t5

        # a2 = a2 / 10
        mv t4, a2
        li t5, 0

    div_end_loop:
        blt t4, s2, div_end_done
        addi t4, t4, -10
        addi t5, t5, 1
        j div_end_loop

    div_end_done:
        mv a2, t5
        addi s1, s1, 1
        j loop_start

loop_end: # restore the registers
    mv a0, s0
    lw   ra, 16(sp)
    lw   s0, 12(sp)
    lw   s1, 8(sp)
    lw   s2, 4(sp)
    lw   s3, 0(sp)
    addi sp, sp, 20
    ret