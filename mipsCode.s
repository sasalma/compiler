
.text
# function main
# formals: 
# locals: res (loc: -4); a (loc: -8); b (loc: -12); c (loc: -16); d (loc: -20); e (loc: -24); tmp$0 (loc: -28); tmp$1 (loc: -32); tmp$2 (loc: -36); tmp$3 (loc: -40); tmp$4 (loc: -44); tmp$5 (loc: -48); tmp$6 (loc: -52); tmp$7 (loc: -56); tmp$8 (loc: -60); tmp$9 (loc: -64); tmp$10 (loc: -68); tmp$11 (loc: -72); tmp$12 (loc: -76); tmp$13 (loc: -80); tmp$14 (loc: -84); tmp$15 (loc: -88); tmp$16 (loc: -92); tmp$17 (loc: -96); tmp$18 (loc: -100); LIM (loc: -104); 
# space for locals: 104 bytes
#
_main:
    la $sp, -8($sp)    # allocate space for old $fp and $ra
    sw $fp, 4($sp)     # save old $fp
    sw $ra, 0($sp)     # save old $ra
    la $fp, 0($sp)     # $fp := $sp
    la $sp, -104($sp)   # allocate stack frame



    li $t0, 0
    move $s1, $t0	# a



    li $t0, 3
    move $s3, $t0	# LIM


    li $t0, 0
    move $s0, $t0	# tmp$2

    move $s2, $s0	# res

Lbl0:



    blt $s1, $s3, Lbl1

    j Lbl2

Lbl1:


    li $t0, 0
    move $s0, $t0	# tmp$3

    move $s0, $s0	# b

Lbl3:



    blt $s0, $s3, Lbl4

    j Lbl5

Lbl4:


    li $t0, 0
    move $s4, $t0	# tmp$4

    move $s7, $s4	# c

Lbl6:



    blt $s7, $s3, Lbl7

    j Lbl8

Lbl7:


    li $t0, 0
    move $s4, $t0	# tmp$5

    move $s6, $s4	# d

Lbl9:



    blt $s6, $s3, Lbl10

    j Lbl11

Lbl10:


    li $t0, 0
    move $s4, $t0	# tmp$6

    move $s5, $s4	# e

Lbl12:



    blt $s5, $s3, Lbl13

    j Lbl14

Lbl13:




    li $t1, 1
    add $s2, $s2, $t1

    move $s2, $s2	# res




    li $t1, 1
    add $s4, $s5, $t1

    move $s5, $s4	# e

    j Lbl12

Lbl14:




    li $t1, 1
    add $s4, $s6, $t1

    move $s6, $s4	# d

    j Lbl9

Lbl11:




    li $t1, 1
    add $s4, $s7, $t1

    move $s7, $s4	# c

    j Lbl6

Lbl8:




    li $t1, 1
    add $s0, $s0, $t1

    move $s0, $s0	# b

    j Lbl3

Lbl5:




    li $t1, 1
    add $s0, $s1, $t1

    move $s1, $s0	# a

    j Lbl0

Lbl2:


    la $sp, -4($sp)
    sw $s2, 0($sp)

    jal _println
    la $sp, 4($sp)



    la $sp, 0($fp)     # deallocate locals
    lw $ra, 0($sp)     # restore return address
    lw $fp, 4($sp)     # restore frame pointer
    la $sp, 8($sp)     # restore stack pointer
    jr $ra


    la $sp, 0($fp)     # deallocate locals
    lw $ra, 0($sp)     # restore return address
    lw $fp, 4($sp)     # restore frame pointer
    la $sp, 8($sp)     # restore stack pointer
    jr $ra

# end function main


.data
.align 2

.align 2
.data
__nl: .asciiz "\n"
.align 2
.text
# println: print out an integer followed by a newline
 _println:
    li $v0, 1
    lw $a0, 0($sp)
    syscall
    li $v0, 4
    la $a0, __nl
    syscall
    jr $ra

# jump to _main, where user code starts, at start of execution
main:
    j _main

