
.text
# function main
# formals: 
# locals: x (loc: -1); y (loc: -8); tmp$0 (loc: -12); 
# space for locals: 12 bytes
#
_main:

#   freq=2
    la $sp, -8($sp)    # allocate space for old $fp and $ra
    sw $fp, 4($sp)     # save old $fp
    sw $ra, 0($sp)     # save old $ra
    la $fp, 0($sp)     # $fp := $sp
    la $sp, -12($sp)   # allocate stack frame


#   freq=2


#   freq=2
    li $t0, 255
    move $s0, $t0	# tmp$0


#   freq=2
    move $t0, $s0	# tmp$0
    sll $t0, $t0, 24 # Takes the 8th bit to the 32th position
    sra $t0, $t0, 24 # Takes the 32th bit back to the 8th position preserving the sign
    move $s1, $t0	# x


#   freq=2


#   freq=2


#   freq=2
    move $t0, $s1	# x
    move $s0, $t0	# y


#   freq=2


#   freq=2
    move $t0, $s0	# y
    la $sp, -4($sp)
    sw $t0, 0($sp)


#   freq=2
    jal _println
    la $sp, 4($sp)


#   freq=2


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

