Total Nodes = 6

Node number = 0, Variable = u, live state = 1
	Adjacency List : tmp$1 z 	Degree = 2 
	Node cost = 4 
Node number = 1, Variable = x, live state = 1
	Adjacency List : tmp$0 y 	Degree = 2 
	Node cost = 4 
Node number = 2, Variable = y, live state = 1
	Adjacency List : x z 	Degree = 2 
	Node cost = 8 
Node number = 3, Variable = z, live state = 1
	Adjacency List : y u 	Degree = 2 
	Node cost = 8 
Node number = 4, Variable = tmp$0, live state = 1
	Adjacency List : x 	Degree = 1 
	Node cost = 4 
Node number = 5, Variable = tmp$1, live state = 1
	Adjacency List : u 	Degree = 1 
	Node cost = 4 
Printing Stack
 u
Printing Stack
 x
 u
Printing Stack
 y
 x
 u
Printing Stack
 z
 y
 x
 u
Printing Stack
 tmp$0
 z
 y
 x
 u
Printing Stack
 tmp$1
 tmp$0
 z
 y
 x
 u
 VAR tmp$1 is in REGISTER $t0
 VAR tmp$0 is in REGISTER $t0
 VAR z is in REGISTER $t0
 VAR y is in REGISTER $t1
 VAR x is in REGISTER $t2
 VAR u is in REGISTER $t1
.text
# function main
# formals: 
# locals: u (loc: -4); x (loc: -8); y (loc: -12); z (loc: -16); tmp$0 (loc: -20); tmp$1 (loc: -24); 
# space for locals: 24 bytes
#
_main:

#   freq=2
    la $sp, -8($sp)    # allocate space for old $fp and $ra
    sw $fp, 4($sp)     # save old $fp
    sw $ra, 0($sp)     # save old $ra
    la $fp, 0($sp)     # $fp := $sp
    la $sp, -24($sp)   # allocate stack frame


#   freq=2


#   freq=2
    li $t0, 12345
    sw $t0, -20($fp)	# tmp$0


#   freq=2
    lw $t0, -20($fp)	# tmp$0
    sw $t0, -8($fp)	# x


#   freq=2


#   freq=2
    li $t0, 98765
    sw $t0, -24($fp)	# tmp$1


#   freq=2
    lw $t0, -24($fp)	# tmp$1
    sw $t0, -4($fp)	# u


#   freq=2


#   freq=2


#   freq=2
    lw $t0, -8($fp)	# x
    sw $t0, -12($fp)	# y


#   freq=2


#   freq=2


#   freq=2
    lw $t0, -12($fp)	# y
    sw $t0, -16($fp)	# z


#   freq=2


#   freq=2
    lw $t0, -16($fp)	# z
    la $sp, -4($sp)
    sw $t0, 0($sp)


#   freq=2
    jal _println
    la $sp, 4($sp)


#   freq=2


#   freq=2


#   freq=2


#   freq=2
    lw $t0, -4($fp)	# u
    sw $t0, -16($fp)	# z


#   freq=2


#   freq=2


#   freq=2
    lw $t0, -16($fp)	# z
    sw $t0, -12($fp)	# y


#   freq=2


#   freq=2
    lw $t0, -12($fp)	# y
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

