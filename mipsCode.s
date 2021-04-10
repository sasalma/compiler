Total Nodes = 14

Node number = 0, Variable = c, live state = 1
	Adjacency List : 	Degree = 0 
	Node cost = 0 
Node number = 1, Variable = u, live state = 1
	Adjacency List : tmp$1 z 	Degree = 2 
	Node cost = 4 
Node number = 2, Variable = x, live state = 1
	Adjacency List : tmp$0 y tmp$2 tmp$3 tmp$8 tmp$4 tmp$5 	Degree = 7 
	Node cost = 38 
Node number = 3, Variable = y, live state = 1
	Adjacency List : x z tmp$8 	Degree = 3 
	Node cost = 16 
Node number = 4, Variable = z, live state = 1
	Adjacency List : y u tmp$8 	Degree = 3 
	Node cost = 16 
Node number = 5, Variable = tmp$0, live state = 1
	Adjacency List : x 	Degree = 1 
	Node cost = 4 
Node number = 6, Variable = tmp$1, live state = 1
	Adjacency List : u 	Degree = 1 
	Node cost = 4 
Node number = 7, Variable = tmp$2, live state = 1
	Adjacency List : x 	Degree = 1 
	Node cost = 4 
Node number = 8, Variable = tmp$3, live state = 1
	Adjacency List : x 	Degree = 1 
	Node cost = 16 
Node number = 9, Variable = tmp$4, live state = 1
	Adjacency List : x tmp$5 	Degree = 2 
	Node cost = 16 
Node number = 10, Variable = tmp$5, live state = 1
	Adjacency List : tmp$4 x 	Degree = 2 
	Node cost = 16 
Node number = 11, Variable = tmp$6, live state = 1
	Adjacency List : tmp$7 	Degree = 1 
	Node cost = 16 
Node number = 12, Variable = tmp$7, live state = 1
	Adjacency List : tmp$6 	Degree = 1 
	Node cost = 16 
Node number = 13, Variable = tmp$8, live state = 1
	Adjacency List : x y z 	Degree = 3 
	Node cost = 16 
Printing Stack
 c
Printing Stack
 u
 c
Printing Stack
 y
 u
 c
Printing Stack
 z
 y
 u
 c
Printing Stack
 tmp$0
 z
 y
 u
 c
Printing Stack
 tmp$1
 tmp$0
 z
 y
 u
 c
Printing Stack
 tmp$2
 tmp$1
 tmp$0
 z
 y
 u
 c
Printing Stack
 tmp$3
 tmp$2
 tmp$1
 tmp$0
 z
 y
 u
 c
Printing Stack
 tmp$4
 tmp$3
 tmp$2
 tmp$1
 tmp$0
 z
 y
 u
 c
Printing Stack
 tmp$5
 tmp$4
 tmp$3
 tmp$2
 tmp$1
 tmp$0
 z
 y
 u
 c
Printing Stack
 tmp$6
 tmp$5
 tmp$4
 tmp$3
 tmp$2
 tmp$1
 tmp$0
 z
 y
 u
 c
Printing Stack
 tmp$7
 tmp$6
 tmp$5
 tmp$4
 tmp$3
 tmp$2
 tmp$1
 tmp$0
 z
 y
 u
 c
Printing Stack
 tmp$8
 tmp$7
 tmp$6
 tmp$5
 tmp$4
 tmp$3
 tmp$2
 tmp$1
 tmp$0
 z
 y
 u
 c
Printing Stack
 x
 tmp$8
 tmp$7
 tmp$6
 tmp$5
 tmp$4
 tmp$3
 tmp$2
 tmp$1
 tmp$0
 z
 y
 u
 c
 VAR x is in REGISTER $a0
 VAR tmp$8 is in REGISTER $a1
 VAR tmp$7 is in REGISTER $a0
 VAR tmp$6 is in REGISTER $a1
 VAR tmp$5 is in REGISTER $a1
 VAR tmp$4 is in REGISTER $a2
 VAR tmp$3 is in REGISTER $a1
 VAR tmp$2 is in REGISTER $a1
 VAR tmp$1 is in REGISTER $a0
 VAR tmp$0 is in REGISTER $a1
 VAR z is in REGISTER $a0
 VAR y is in REGISTER $a2
 VAR u is in REGISTER $a1
 VAR c is in REGISTER $a0
.text
# function main
# formals: 
# locals: b (loc: -40); c (loc: -41); u (loc: -48); x (loc: -52); y (loc: -56); z (loc: -60); tmp$0 (loc: -64); tmp$1 (loc: -68); tmp$2 (loc: -72); tmp$3 (loc: -76); tmp$4 (loc: -80); tmp$5 (loc: -84); tmp$6 (loc: -88); tmp$7 (loc: -92); tmp$8 (loc: -96); 
# space for locals: 96 bytes
#
_main:

#   freq=2
    la $sp, -8($sp)    # allocate space for old $fp and $ra
    sw $fp, 4($sp)     # save old $fp
    sw $ra, 0($sp)     # save old $ra
    la $fp, 0($sp)     # $fp := $sp
    la $sp, -96($sp)   # allocate stack frame


#   freq=2


#   freq=2
    li $t0, 12345
    move $a1, $t0	# tmp$0


#   freq=2
    move $t0, $a1	# tmp$0
    move $a0, $t0	# x


#   freq=2


#   freq=2
    li $t0, 98765
    move $a0, $t0	# tmp$1


#   freq=2
    move $t0, $a0	# tmp$1
    move $a1, $t0	# u


#   freq=2


#   freq=2


#   freq=2
    move $t0, $a0	# x
    move $a2, $t0	# y


#   freq=2


#   freq=2


#   freq=2
    move $t0, $a2	# y
    move $a0, $t0	# z


#   freq=2


#   freq=2
    move $t0, $a0	# z
    la $sp, -4($sp)
    sw $t0, 0($sp)


#   freq=2
    jal _println
    la $sp, 4($sp)


#   freq=2


#   freq=2


#   freq=2


#   freq=2
    move $t0, $a1	# u
    move $a0, $t0	# z


#   freq=2


#   freq=2


#   freq=2
    move $t0, $a0	# z
    move $a2, $t0	# y


#   freq=2


#   freq=2
    move $t0, $a2	# y
    la $sp, -4($sp)
    sw $t0, 0($sp)


#   freq=2
    jal _println
    la $sp, 4($sp)


#   freq=2


#   freq=2


#   freq=2
    li $t0, 0
    move $a1, $t0	# tmp$2


#   freq=2
    move $t0, $a1	# tmp$2
    move $a0, $t0	# x


#   freq=2
Lbl0:


#   freq=8


#   freq=8
    li $t0, 10
    move $a1, $t0	# tmp$3


#   freq=8
    move $t0, $a0	# x
    move $t1, $a1	# tmp$3
    blt $t0, $t1, Lbl1


#   freq=8
    j Lbl2


#   freq=2
Lbl1:


#   freq=8
    li $t0, 1
    move $a1, $t0	# tmp$6


#   freq=8
    li $t0, 0
    move $a0, $t0	# tmp$7


#   freq=8
    move $t0, $a1	# tmp$6
    move $t1, $a0	# tmp$7
    bgt $t0, $t1, Lbl3


#   freq=8
    j Lbl4


#   freq=8
Lbl3:


#   freq=8


#   freq=8


#   freq=8


#   freq=8
    move $t0, $a0	# x
    move $t1, $a2	# y
    add $t2, $t0, $t1
    move  $a1,  $t2	# tmp$8


#   freq=8
    move $t0, $a1	# tmp$8
    move $a0, $t0	# z


#   freq=8
    j Lbl5


#   freq=8
Lbl4:


#   freq=8
Lbl5:


#   freq=8


#   freq=8


#   freq=8
    li $t0, 1
    move $a1, $t0	# tmp$5


#   freq=8
    move $t0, $a0	# x
    move $t1, $a1	# tmp$5
    add $t2, $t0, $t1
    move  $a2,  $t2	# tmp$4


#   freq=8
    move $t0, $a2	# tmp$4
    move $a0, $t0	# x


#   freq=2
    j Lbl0


#   freq=2
Lbl2:


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

