CC = gcc
CFLAGS = -g -DDEBUG -DOlocal
DEST = compile

HFILES = error.h  global.h  protos.h symbol-table.h  syntax-tree.h codegen.h optimization.h regAlloc.h

CFILES = error.c \
	lex.yy.c \
	main.c \
	print.c \
	symbol-table.c \
        syntax-tree.c \
	util.c \
	codegen.c \
	optimization.c\
	regAlloc.c\
	y.tab.c

OFILES = $(CFILES:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -c $<

$(DEST) : $(OFILES)
	$(CC) -o $(DEST) $(OFILES) -ll

error.o : error.h global.h syntax-tree.h error.c y.tab.h

main.o : global.h main.c

symbol-table.o : global.h symbol-table.h symbol-table.c

syntax-tree.o : global.h syntax-tree.h syntax-tree.c

util.o : global.h util.h util.c

lex.yy.o : global.h error.h syntax-tree.h symbol-table.h lex.yy.c

y.tab.c : parser.y 
	yacc -d -v parser.y

lex.yy.c : y.tab.h scanner.l 
	flex scanner.l

y.tab.h : parser.y
	yacc -d -v parser.y

clean :
	/bin/rm -f *.o core *.BAK *~ $(DEST) y.output

realclean :
	/bin/rm -f *.o core *.BAK *~ lex.yy.c y.tab.c y.tab.h y.output $(DEST)
