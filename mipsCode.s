
.text
# function fun
# formals: testFormal (loc: 8); 
# locals: tmp$0 (loc: -4); 
# space for locals: 4 bytes
#
_fun:

#   freq=2
    la $sp, -8($sp)    # allocate space for old $fp and $ra
    sw $fp, 4($sp)     # save old $fp
    sw $ra, 0($sp)     # save old $ra
    la $fp, 0($sp)     # $fp := $sp
    la $sp, -4($sp)   # allocate stack frame


#   freq=2
    li $t0, 5
    move $a0, $t0	# tmp$0


#   freq=2


#   freq=2
    move $v0, $a0	# tmp$0
    la $sp, 0($fp)     # deallocate locals
    lw $ra, 0($sp)     # restore return address
    lw $fp, 4($sp)     # restore frame pointer
    la $sp, 8($sp)     # restore stack pointer
    jr $ra


#   freq=2


#   freq=2
    la $sp, 0($fp)     # deallocate locals
    lw $ra, 0($sp)     # restore return address
    lw $fp, 4($sp)     # restore frame pointer
    la $sp, 8($sp)     # restore stack pointer
    jr $ra

# end function fun


.text
# function main
# formals: 
# locals: k (loc: -4); x (loc: -8); y (loc: -12); res1 (loc: -16); res2 (loc: -20); tmp$1 (loc: -24); tmp$2 (loc: -28); tmp$3 (loc: -32); tmp$4 (loc: -36); tmp$5 (loc: -40); tmp$6 (loc: -44); tmp$7 (loc: -48); tmp$8 (loc: -52); tmp$9 (loc: -56); tmp$10 (loc: -60); tmp$20 (loc: -64); tmp$11 (loc: -68); tmp$21 (loc: -72); tmp$12 (loc: -76); tmp$22 (loc: -80); tmp$13 (loc: -84); tmp$14 (loc: -88); tmp$15 (loc: -92); tmp$16 (loc: -96); tmp$17 (loc: -100); tmp$18 (loc: -104); tmp$19 (loc: -108); 
# space for locals: 108 bytes
#
_main:

#   freq=2
    la $sp, -8($sp)    # allocate space for old $fp and $ra
    sw $fp, 4($sp)     # save old $fp
    sw $ra, 0($sp)     # save old $ra
    la $fp, 0($sp)     # $fp := $sp
    la $sp, -108($sp)   # allocate stack frame


#   freq=2
    li $t0, 1
    move $a1, $t0	# tmp$1


#   freq=2
    li $t0, 0
    move $a0, $t0	# tmp$2


#   freq=2
    move $t0, $a1	# tmp$1
    move $t1, $a0	# tmp$2
    bgt $t0, $t1, Lbl0


#   freq=2
    j Lbl1


#   freq=2
Lbl0:


#   freq=1


#   freq=1
    li $t0, 1111
    move $a1, $t0	# tmp$3


#   freq=1
    move $t0, $a1	# tmp$3
    move $a0, $t0	# res1


#   freq=2
    j Lbl2


#   freq=2
Lbl1:


#   freq=1


#   freq=1
    li $t0, 2222
    move $a1, $t0	# tmp$4


#   freq=1
    move $t0, $a1	# tmp$4
    move $a0, $t0	# res1


#   freq=2
Lbl2:


#   freq=2


#   freq=2
    li $t0, 1
    move $a2, $t0	# tmp$5


#   freq=2
    move $t0, $a2	# tmp$5
    move $a1, $t0	# x


#   freq=2


#   freq=2
    li $t0, 1
    move $a2, $t0	# tmp$7


#   freq=2
    move $t0, $a2	# tmp$7
    neg $t2, $t0
    move  $a3,  $t2	# tmp$6


#   freq=2
    move $t0, $a3	# tmp$6
    move $s0, $t0	# y


#   freq=2


#   freq=2


#   freq=2
    move $t0, $a1	# x
    move $t1, $s0	# y
    bgt $t0, $t1, Lbl3


#   freq=2
    j Lbl4


#   freq=2
Lbl3:


#   freq=1


#   freq=1
    li $t0, 3333
    move $a1, $t0	# tmp$8


#   freq=1
    move $t0, $a1	# tmp$8
    move $a1, $t0	# res2


#   freq=2
    j Lbl5


#   freq=2
Lbl4:


#   freq=1


#   freq=1
    li $t0, 4444
    move $a1, $t0	# tmp$9


#   freq=1
    move $t0, $a1	# tmp$9
    move $a1, $t0	# res2


#   freq=2
Lbl5:


#   freq=2


#   freq=2
    move $t0, $a0	# res1
    la $sp, -4($sp)
    sw $t0, 0($sp)


#   freq=2
    jal _println
    la $sp, 4($sp)


#   freq=2


#   freq=2


#   freq=2
    li $t0, 10
    move $a0, $t0	# tmp$10


#   freq=2
    move $t0, $a0	# tmp$10
    la $sp, -4($sp)
    sw $t0, 0($sp)


#   freq=2
    jal _fun
    la $sp, 4($sp)


#   freq=2
    move  $a0,  $v0	# tmp$11


#   freq=2
    move $t0, $a0	# tmp$11
    move $a2, $t0	# k


#   freq=2


#   freq=2
    li $t0, 0
    move $a0, $t0	# tmp$12


#   freq=2
    move $t0, $a0	# tmp$12
    move $a2, $t0	# k


#   freq=2
Lbl6:


#   freq=8


#   freq=8
    li $t0, 10
    move $a0, $t0	# tmp$13


#   freq=8
    move $t0, $a2	# k
    move $t1, $a0	# tmp$13
    blt $t0, $t1, Lbl7


#   freq=8
    j Lbl8


#   freq=2
Lbl7:


#   freq=8


#   freq=8
    li $t0, 100
    move $a0, $t0	# tmp$16


#   freq=8
    move $t0, $a0	# tmp$16
    move $a1, $t0	# x


#   freq=8


#   freq=8
    li $t0, 222
    move $a0, $t0	# tmp$17


#   freq=8
    move $t0, $a0	# tmp$17
    move $s0, $t0	# y


#   freq=8


#   freq=8


#   freq=8
    li $t0, 1
    move $a0, $t0	# tmp$15


#   freq=8
    move $t0, $a2	# k
    move $t1, $a0	# tmp$15
    add $t2, $t0, $t1
    move  $a1,  $t2	# tmp$14


#   freq=8
    move $t0, $a1	# tmp$14
    move $a2, $t0	# k


#   freq=2
    j Lbl6


#   freq=2
Lbl8:


#   freq=2


#   freq=2
    li $t0, 9
    move $a0, $t0	# tmp$18


#   freq=2
    move $t0, $a0	# tmp$18
    move $a2, $t0	# k


#   freq=8
Lbl9:


#   freq=8


#   freq=8
    li $t0, 0
    move $a0, $t0	# tmp$19


#   freq=8
    move $t0, $a2	# k
    move $t1, $a0	# tmp$19
    bgt $t0, $t1, Lbl10


#   freq=8
    j Lbl11


#   freq=8
Lbl10:


#   freq=8


#   freq=8
    li $t0, 9090
    move $a0, $t0	# tmp$20


#   freq=8
    move $t0, $a0	# tmp$20
    move $a0, $t0	# res1


#   freq=8


#   freq=8


#   freq=8
    li $t0, 1
    move $a0, $t0	# tmp$22


#   freq=8
    move $t0, $a2	# k
    move $t1, $a0	# tmp$22
    sub $t2, $t0, $t1
    move  $a1,  $t2	# tmp$21


#   freq=8
    move $t0, $a1	# tmp$21
    move $a2, $t0	# k


#   freq=8
    j Lbl9


#   freq=8
Lbl11:


#   freq=2


#   freq=2
    la $sp, 0($fp)     # deallocate locals
    lw $ra, 0($sp)     # restore return address
    lw $fp, 4($sp)     # restore frame pointer
    la $sp, 8($sp)     # restore stack pointer
    jr $ra


#   freq=2


#   freq=2
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

