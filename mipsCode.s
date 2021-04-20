.text
# function main
# formals: 
# locals: tmp$0 (loc: -4); tmp$1 (loc: -8); tmp$2 (loc: -12); tmp$3 (loc: -16); tmp$4 (loc: -20); tmp$5 (loc: -24); tmp$6 (loc: -28); tmp$7 (loc: -32); tmp$8 (loc: -36); tmp$9 (loc: -40); tmp$10 (loc: -44); tmp$20 (loc: -48); tmp$11 (loc: -52); tmp$30 (loc: -56); tmp$21 (loc: -60); tmp$12 (loc: -64); tmp$31 (loc: -68); tmp$22 (loc: -72); tmp$13 (loc: -76); x10 (loc: -80); x01 (loc: -84); tmp$32 (loc: -88); tmp$23 (loc: -92); tmp$14 (loc: -96); y10 (loc: -100); y01 (loc: -104); x02 (loc: -108); tmp$24 (loc: -112); tmp$15 (loc: -116); z10 (loc: -120); z01 (loc: -124); y02 (loc: -128); x03 (loc: -132); tmp$25 (loc: -136); tmp$16 (loc: -140); z02 (loc: -144); y03 (loc: -148); x04 (loc: -152); tmp$26 (loc: -156); tmp$17 (loc: -160); z03 (loc: -164); y04 (loc: -168); x05 (loc: -172); tmp$27 (loc: -176); tmp$18 (loc: -180); z04 (loc: -184); y05 (loc: -188); x06 (loc: -192); tmp$28 (loc: -196); tmp$19 (loc: -200); z05 (loc: -204); y06 (loc: -208); x07 (loc: -212); tmp$29 (loc: -216); z06 (loc: -220); y07 (loc: -224); x08 (loc: -228); z07 (loc: -232); y08 (loc: -236); x09 (loc: -240); z08 (loc: -244); y09 (loc: -248); z09 (loc: -252); 
# space for locals: 252 bytes
#
_main:
    la $sp, -8($sp)    # allocate space for old $fp and $ra
    sw $fp, 4($sp)     # save old $fp
    sw $ra, 0($sp)     # save old $ra
    la $fp, 0($sp)     # $fp := $sp
    la $sp, -252($sp)   # allocate stack frame



    li $t0, 1
    sw $t0, -84($fp)	# x01





    lw $t0, -84($fp)	# x01
    sw $t0, -108($fp)	# x02





    lw $t0, -108($fp)	# x02
    sw $t0, -132($fp)	# x03





    lw $t0, -132($fp)	# x03
    sw $t0, -152($fp)	# x04





    lw $t0, -152($fp)	# x04
    sw $t0, -172($fp)	# x05





    lw $t0, -172($fp)	# x05
    sw $t0, -192($fp)	# x06





    lw $t0, -192($fp)	# x06
    sw $t0, -212($fp)	# x07





    lw $t0, -212($fp)	# x07
    sw $t0, -228($fp)	# x08





    lw $t0, -228($fp)	# x08
    sw $t0, -240($fp)	# x09





    lw $t0, -240($fp)	# x09
    sw $t0, -80($fp)	# x10





    lw $t0, -80($fp)	# x10
    sw $t0, -104($fp)	# y01





    lw $t0, -104($fp)	# y01
    sw $t0, -128($fp)	# y02





    lw $t0, -128($fp)	# y02
    sw $t0, -148($fp)	# y03





    lw $t0, -148($fp)	# y03
    sw $t0, -168($fp)	# y04





    lw $t0, -168($fp)	# y04
    sw $t0, -188($fp)	# y05





    lw $t0, -188($fp)	# y05
    sw $t0, -208($fp)	# y06





    lw $t0, -208($fp)	# y06
    sw $t0, -224($fp)	# y07





    lw $t0, -224($fp)	# y07
    sw $t0, -236($fp)	# y08





    lw $t0, -236($fp)	# y08
    sw $t0, -248($fp)	# y09





    lw $t0, -248($fp)	# y09
    sw $t0, -100($fp)	# y10





    lw $t0, -100($fp)	# y10
    sw $t0, -124($fp)	# z01





    lw $t0, -124($fp)	# z01
    sw $t0, -144($fp)	# z02





    lw $t0, -144($fp)	# z02
    sw $t0, -164($fp)	# z03





    lw $t0, -164($fp)	# z03
    sw $t0, -184($fp)	# z04





    lw $t0, -184($fp)	# z04
    sw $t0, -204($fp)	# z05





    lw $t0, -204($fp)	# z05
    sw $t0, -220($fp)	# z06





    lw $t0, -220($fp)	# z06
    sw $t0, -232($fp)	# z07





    lw $t0, -232($fp)	# z07
    sw $t0, -244($fp)	# z08





    lw $t0, -244($fp)	# z08
    sw $t0, -252($fp)	# z09





    lw $t0, -252($fp)	# z09
    sw $t0, -120($fp)	# z10


    lw $t0, -120($fp)	# z10
    la $sp, -4($sp)
    sw $t0, 0($sp)

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

