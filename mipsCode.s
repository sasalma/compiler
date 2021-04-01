.text
# function fun
# formals: testFormal (loc: 8); 
# locals: localInt (loc: -4); localCH (loc: -5); tmp$0 (loc: -12); 
# space for locals: 12 bytes
#
_fun:

#   freq=2
    la $sp, -8($sp)    # allocate space for old $fp and $ra
    sw $fp, 4($sp)     # save old $fp
    sw $ra, 0($sp)     # save old $ra
    la $fp, 0($sp)     # $fp := $sp
    la $sp, -12($sp)   # allocate stack frame


#   freq=2
    li $t0, 5
    sw $t0, -12($fp)	# tmp$0


#   freq=2


#   freq=2
    lw $v0, -12($fp)	# tmp$0
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
    sw $t0, -24($fp)	# tmp$1


#   freq=2
    li $t0, 0
    sw $t0, -28($fp)	# tmp$2


#   freq=2
    lw $t0, -24($fp)	# tmp$1
    lw $t1, -28($fp)	# tmp$2
    bgt $t0, $t1, Lbl0


#   freq=2
    j Lbl1


#   freq=2
Lbl0:


#   freq=1


#   freq=1
    li $t0, 1111
    sw $t0, -32($fp)	# tmp$3


#   freq=1
    lw $t0, -32($fp)	# tmp$3
    sw $t0, -16($fp)	# res1


#   freq=2
    j Lbl2


#   freq=2
Lbl1:


#   freq=1


#   freq=1
    li $t0, 2222
    sw $t0, -36($fp)	# tmp$4


#   freq=1
    lw $t0, -36($fp)	# tmp$4
    sw $t0, -16($fp)	# res1


#   freq=2
Lbl2:


#   freq=2


#   freq=2
    li $t0, 1
    sw $t0, -40($fp)	# tmp$5


#   freq=2
    lw $t0, -40($fp)	# tmp$5
    sw $t0, -8($fp)	# x


#   freq=2


#   freq=2
    li $t0, 1
    sw $t0, -48($fp)	# tmp$7


#   freq=2
    lw $t0, -48($fp)	# tmp$7
    neg $t2, $t0
    sw $t2, -44($fp)	# tmp$6


#   freq=2
    lw $t0, -44($fp)	# tmp$6
    sw $t0, -12($fp)	# y


#   freq=2


#   freq=2


#   freq=2
    lw $t0, -8($fp)	# x
    lw $t1, -12($fp)	# y
    bgt $t0, $t1, Lbl3


#   freq=2
    j Lbl4


#   freq=2
Lbl3:


#   freq=1


#   freq=1
    li $t0, 3333
    sw $t0, -52($fp)	# tmp$8


#   freq=1
    lw $t0, -52($fp)	# tmp$8
    sw $t0, -20($fp)	# res2


#   freq=2
    j Lbl5


#   freq=2
Lbl4:


#   freq=1


#   freq=1
    li $t0, 4444
    sw $t0, -56($fp)	# tmp$9


#   freq=1
    lw $t0, -56($fp)	# tmp$9
    sw $t0, -20($fp)	# res2


#   freq=2
Lbl5:


#   freq=2


#   freq=2
    lw $t0, -16($fp)	# res1
    la $sp, -4($sp)
    sw $t0, 0($sp)


#   freq=2
    jal _println
    la $sp, 4($sp)


#   freq=2


#   freq=2


#   freq=2
    li $t0, 10
    sw $t0, -60($fp)	# tmp$10


#   freq=2
    lw $t0, -60($fp)	# tmp$10
    la $sp, -4($sp)
    sw $t0, 0($sp)


#   freq=2
    jal _fun
    la $sp, 4($sp)


#   freq=2
    sw $v0, -68($fp)	# tmp$11


#   freq=2
    lw $t0, -68($fp)	# tmp$11
    sw $t0, -4($fp)	# k


#   freq=2


#   freq=2
    li $t0, 0
    sw $t0, -76($fp)	# tmp$12


#   freq=2
    lw $t0, -76($fp)	# tmp$12
    sw $t0, -4($fp)	# k


#   freq=2
Lbl6:


#   freq=8


#   freq=8
    li $t0, 10
    sw $t0, -84($fp)	# tmp$13


#   freq=8
    lw $t0, -4($fp)	# k
    lw $t1, -84($fp)	# tmp$13
    blt $t0, $t1, Lbl7


#   freq=8
    j Lbl8


#   freq=2
Lbl7:


#   freq=8


#   freq=8
    li $t0, 100
    sw $t0, -96($fp)	# tmp$16


#   freq=8
    lw $t0, -96($fp)	# tmp$16
    sw $t0, -8($fp)	# x


#   freq=8


#   freq=8
    li $t0, 222
    sw $t0, -100($fp)	# tmp$17


#   freq=8
    lw $t0, -100($fp)	# tmp$17
    sw $t0, -12($fp)	# y


#   freq=8


#   freq=8


#   freq=8
    li $t0, 1
    sw $t0, -92($fp)	# tmp$15


#   freq=8
    lw $t0, -4($fp)	# k
    lw $t1, -92($fp)	# tmp$15
    add $t2, $t0, $t1
    sw $t2, -88($fp)	# tmp$14


#   freq=8
    lw $t0, -88($fp)	# tmp$14
    sw $t0, -4($fp)	# k


#   freq=2
    j Lbl6


#   freq=2
Lbl8:


#   freq=2


#   freq=2
    li $t0, 9
    sw $t0, -104($fp)	# tmp$18


#   freq=2
    lw $t0, -104($fp)	# tmp$18
    sw $t0, -4($fp)	# k


#   freq=8
Lbl9:


#   freq=8


#   freq=8
    li $t0, 0
    sw $t0, -108($fp)	# tmp$19


#   freq=8
    lw $t0, -4($fp)	# k
    lw $t1, -108($fp)	# tmp$19
    bgt $t0, $t1, Lbl10


#   freq=8
    j Lbl11


#   freq=8
Lbl10:


#   freq=8


#   freq=8
    li $t0, 9090
    sw $t0, -64($fp)	# tmp$20


#   freq=8
    lw $t0, -64($fp)	# tmp$20
    sw $t0, -16($fp)	# res1


#   freq=8


#   freq=8


#   freq=8
    li $t0, 1
    sw $t0, -80($fp)	# tmp$22


#   freq=8
    lw $t0, -4($fp)	# k
    lw $t1, -80($fp)	# tmp$22
    sub $t2, $t0, $t1
    sw $t2, -72($fp)	# tmp$21


#   freq=8
    lw $t0, -72($fp)	# tmp$21
    sw $t0, -4($fp)	# k


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

