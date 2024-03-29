/*
 * symbol-table.c
 *
 * Author: Saumya Debray
 */

#include <assert.h>
#include "global.h"
#include "symbol-table.h"

extern int CurrScope, CurrType, fnRetType;
extern char *fnName;
extern llistptr lptr;
extern bool is_extern;
extern symtabnode *currFun;

#define HASHTBLSZ 256

symtabnode *SymTab[2][HASHTBLSZ];

static int hash(char *str)
{
  int n = 0;

  for ( ; str != NULL && *str != '\0'; str++) {
    n += *str;
  }

  return n % HASHTBLSZ;
}

/*
 * SymTabInit(sc)
 *
 * Given a scope sc, initialize the symbol table for that scope by setting
 * all the hash table buckets to NULL.
 */
void SymTabInit(int sc)
{
  int i;

  for (i = 0; i < HASHTBLSZ; i++) {
    SymTab[sc][i] = NULL;
  }
}

/*
 * SymTabLookup(str, sc)
 *
 * Look up the string str in the symbol table with scope sc.  If found,
 * return a pointer to the corresponding symbol table node, otherwise
 * return NULL.
 */
symtabnode *SymTabLookup(char *str, int sc)
{
  int hval;
  symtabnode *stptr;

  assert(str);

  hval = hash(str);

  for (stptr = SymTab[sc][hval]; stptr != NULL; stptr = stptr->next) {
    if (strcmp(str, stptr->name) == 0) {
      return stptr;
    }
  }

  return NULL;
}

/*
 * SymTabLookupAll(str)
 *
 * Look up the string str in the symbol table, starting with the
 * local symbol table and then (if not found) in the global table.
 * If found in either table, return a pointer to the corresponding
 * symbol table node, otherwise return NULL.
 */
symtabnode *SymTabLookupAll(char *str)
{
  symtabnode *stptr;

  assert(str);

  stptr = SymTabLookup(str, Local);

  if (stptr == NULL) {
    stptr = SymTabLookup(str, Global);
  }

  return stptr;
}

/*
 * SymTabInsert(str, sc)
 *
 * Add string str to the symbol table with scope sc, and return a
 * pointer to the resulting entry.  This code assumes that str does not
 * already occur in that symbol table; it gives an error message if it does.
 */
symtabnode *SymTabInsert(char *str, int sc)
{
  int hval;
  symtabnode *sptr;
  
  assert(str != 0);

  sptr = SymTabLookup(str, sc);
  CASSERT(sptr == NULL, ("multiple declarations of %s", str));

  if (sptr != NULL) return sptr;

  hval = hash(str);
  
  sptr = (symtabnode *) zalloc(sizeof(symtabnode));
  sptr->name = str;
  sptr->scope = sc;
  
  sptr->next = SymTab[sc][hval];
  SymTab[sc][hval] = sptr;
  
  return sptr;
}

/*
 * SymTabRecordFunInfo(isProto) -- records information in the symbol
 * table about a function.  The argument isProto indicates whether or
 * not this is a prototype.  It communicates with the YACC parser
 * through the globals fnName (the name of the function), fnRetType
 * (the return type), and lptr (a linked list of information about the
 * parameters).  It returns a pointer to the symbol table record of
 * the function.
 */
symtabnode *SymTabRecordFunInfo(bool isProto) 
{
  symtabnode *stptr, *func;
  llistptr ltmp;
  symtabnode *formal_list_hd, *formal_list_tl, *formal;
  int n;

  func = SymTabLookup(fnName, Global);
  /*
   * It's only OK to have an entry for this ID in the symbol table already
   * if the previous entry was the prototype and this is the actual
   * definition.
   */
  if (func != NULL) {
    if (func->fn_proto_state == FN_PROTO && !isProto) {
      /* 
       * the previous definition was a prototype, and this is the
       * real definition.  Check and make sure that the type info
       * in the prototype matches that for the definition.
       */
      formal = func->formals;
      ltmp = lptr;
      n = 1;
      while (formal != NULL && ltmp != NULL) {
	if ((formal->elt_type == t_None 
	     && !ltmp->is_array 
	     && formal->type != ltmp->type)  // neither is an array
	    || (formal->elt_type != t_None && !ltmp->is_array) // formal is array, but not ltmp
	    || (formal->elt_type == t_None && ltmp->is_array)  // ltmp is array, but not formal
	    || (formal->elt_type != t_None
		&& ltmp->is_array
		&& formal->elt_type != ltmp->type /* both are arrays */)) {
	  errmsg("function %s: type of argument %d does not match that of prototype",
		 fnName, n);
	}
	n++;
	formal = formal->next;
	ltmp = ltmp->next;
      }
      if (!(formal == NULL && ltmp == NULL)) {
	errmsg("function %s: no of arguments in definition does not match prototype",
	       fnName);
      }
      if (fnRetType != func->ret_type) {
	errmsg("function %s: return type does not match that of prototype", fnName);
      }
      if (func->is_extern) {
	errmsg("function %s was previously defined as EXTERN", fnName);
      }
    }
    else {
      errmsg("Multiple prototypes/definitions for function %s", fnName);
    }
  }
  else {
    func = SymTabInsert(fnName, Global);
  }

  func->type = t_Func;
  func->ret_type = fnRetType;

  formal_list_hd = formal_list_tl = NULL;
  n = 0;
  
  for (ltmp = lptr; ltmp != NULL; ltmp = ltmp->next) {
    if (CurrType == t_None) {
      errmsg("Illegal type [void] for identifier %s", lptr->name);
    }
    else {
      stptr = SymTabInsert(ltmp->name, CurrScope);
      stptr->formal = true;
      if (ltmp->is_array) {
	stptr->type = t_Array;
	stptr->elt_type = ltmp->type;
      }
      else {
	stptr->type = ltmp->type;
	stptr->elt_type = t_None;
      }
      /*
       * Now create a record for the list of formals, and copy over
       * info from stptr.
       */
      formal = zalloc(sizeof(*formal));
      formal->name =     stptr->name;
      formal->scope =    stptr->scope;
      formal->formal =   stptr->formal;
      formal->type =     stptr->type;
      formal->elt_type = stptr->elt_type;
      formal->argpos = stptr->argpos = ++n;
      
      if (formal_list_hd == NULL) {
	formal_list_hd = formal_list_tl = formal;
      }
      else {
	formal_list_tl->next = formal;
	formal_list_tl = formal;
      }
    }
  } /* for */

  func->formals = formal_list_hd;
  func->nargs = n;

  if (isProto && func->fn_proto_state != FN_DEFINED) {
    func->fn_proto_state = FN_PROTO;
  }
  else {
    func->fn_proto_state = FN_DEFINED;
  }

  func->is_extern = is_extern;
  fnName = NULL;

  return func;
}


/*
 * CleanupFnInfo() -- clean up after processing information
 * for a function prototype/definition.
 */
void CleanupFnInfo(void)
{
  fnName = NULL;
  lptr = NULL;
  currFun = NULL;
  is_extern = false;
  CurrScope = Global;
#if 0
  DumpSymTab(); 
#endif
  SymTabInit(Local);
}

/*********************************************************************
 *                                                                   *
 *                          CODE GENERATION                          #
 *                                                                   *
 *********************************************************************/

/*
 * var_width : the no. of bytes occupied by a variable of type t_Char,
 * t_Int, or t_Addr
 */
int var_width[3] = {1 /* t_Char */,
		    4 /* t_Int */,
		    4 /* t_Addr */
};


/*
 * ARG_OFFSET: the offset from $fp, in bytes, of the first argument
 */
#define ARG_OFFSET  8

/*
 * LOCAL_OFFSET: the offset from $fp, in bytes, of the first local or temp
 */
#define LOCAL_OFFSET  4

/*
 * space_needed() -- the amount of space (in bytes) occupied by a variable
 */
int space_needed(symtabnode *sptr) {
  if (sptr->type == t_Char || sptr->type == t_Int || sptr->type == t_Addr) {
    return var_width[sptr->type];
  }

  if (sptr->type == t_Array) {
    return sptr->num_elts * var_width[sptr->elt_type];
  }

  errmsg("ERROR [space_needed]: Unrecognized type: %d", sptr->type);
  exit(1);
}


/*
 * memory_alignment() -- returns the alignment of memory accesses required
 * by a reference to a value of the given symbol.
 */
static int memory_alignment(symtabnode *sptr) {
  if (sptr->type == t_Char || sptr->type == t_Int || sptr->type == t_Addr) {
    return var_width[sptr->type];
  }

  if (sptr->type == t_Array) {
    return var_width[sptr->elt_type];
  }

  return 1;
}

/*
 * allocate_storage() -- traverses a function's local symbol table and allocates
 * storage locations for each local variable.  The argument stpr is a pointer
 * to the function's global symbol table entry, and is used to store the total
 * size (in bytes) of the space occupied by its locals and temps.  The value 
 * returned is the total amount of space used by the function's locals and temps.
 */
int allocate_storage(symtabnode *sptr) {
  symtabnode *stmp;
  int i, n, sz, stack_frame_size, curr_offset;

  stack_frame_size = 0;
  curr_offset = 0;
  
  for (i = 0; i < HASHTBLSZ; i++) {
    for (stmp = SymTab[Local][i]; stmp != NULL; stmp = stmp->next) {
      if (stmp->argpos > 0) {
	/*
	 * formal parameter.  Since arrays are passed by reference and we assume
	 * a 32-bit architecture, the size of an array parameter is the same as
	 * that of an int
	 */
	stmp->offset = ARG_OFFSET + var_width[t_Int] * (stmp->argpos-1);
      }
      else {
	/*
	 * insert padding if necessary 
	 */
	n = memory_alignment(stmp);
	while (curr_offset % n != 0) {
	  curr_offset += 1;
	  stack_frame_size += 1;
	}

	sz = space_needed(stmp);
	stmp->offset = -(curr_offset+sz);  /* minus because it has a negative offset from $fp */
	curr_offset += sz;
	stack_frame_size += sz;
      }
    }
  }
  /*
   * make sure the stack frame size is a multiple of 4
   */
  while (stack_frame_size % 4 != 0) {
    stack_frame_size += 1;
  }

  return stack_frame_size;
}


/*
 * print_globals() -- print out all the global variables in MIPS asm syntax.
 */
void print_globals() {
  symtabnode *sptr;
  int i, sz;

  printf("\n");
  printf(".data\n");
  printf(".align 2\n");

  for (i = 0; i < HASHTBLSZ; i++) {
    for (sptr = SymTab[Global][i]; sptr != NULL; sptr = sptr->next) {
      if (sptr->skip_print) {
	continue;
      }
      
      if (sptr->type == t_Char
	  || sptr->type == t_Int
	  || sptr->type == t_Array) {
	sz = space_needed(sptr);
	if (sptr->type == t_Int
	    || (sptr->type == t_Array && sptr->elt_type == t_Int)) {
	  printf(".align 2\n");
	}
	printf("_%s:  .space %d\n", sptr->name, sz);
      }
    }
  }

  printf("\n");
}

/*
 * dump_fn_info() takes a pointer to the global symbol table entry for a function 
 * and writes out the symbol table information for that function in the form of
 * a MIPS asm comment.
 */
void dump_fn_info(symtabnode *sptr) {
  symtabnode *s0, *stmp;
  int i;

  printf("# function %s\n", sptr->name);

  printf("# formals: ");
  for (stmp = sptr->formals; stmp; stmp = stmp->next) {
    char *this_var = stmp->name;
    s0 = SymTabLookup(this_var, Local);
    printf("%s (loc: %d); ", this_var, s0->offset);
  }
  printf("\n");

  printf("# locals: ");
  for (i = 0; i < HASHTBLSZ; i++) {
    for (s0 = SymTab[Local][i]; s0 != NULL; s0 = s0->next) {
      if (s0->argpos == 0) {
	printf("%s (loc: %d); ", s0->name, s0->offset);
      }
    }
  }
  printf("\n");
  printf("# space for locals: %d bytes\n", sptr->offset);
  printf("#\n");
}


/*********************************************************************
 *                                                                   *
 *                           for debugging                           *
 *                                                                   *
 *********************************************************************/

void printType(symtabnode *stptr)
{
  symtabnode *formals;
  switch (stptr->type) {
  case t_Char:
    printf("C");
    CASSERT(stptr->elt_type == t_None, ("<?!>"));
    break;
  case t_Int:  printf("I");
    CASSERT(stptr->elt_type == t_None, ("<?!>"));
    break;
  case t_Array:
    switch(stptr->elt_type) {
    case t_Char: printf("C[%d]", stptr->num_elts); break;
    case t_Int: printf("I[%d]", stptr->num_elts); break;
    default: printf("%d?[%d]", stptr->elt_type, stptr->num_elts);
    }
    break;
  case t_Func:
    printf("(");
    if (stptr->formals == NULL) {
      printf("void");
    }
    else {
      for (formals = stptr->formals; formals; formals = formals->next) {
	printType(formals);
	if (formals->next) {
	  printf(", ");
	}
      }
    }
    printf(") -> ");
    switch (stptr->ret_type) {
    case t_Char: printf("C"); break;
    case t_Int: printf("I"); break;
    case t_None: printf("void"); break;
    default: printf("??%d", stptr->ret_type);
    }
    break;
  case t_None:
    printf("-");
    break;
  default: printf("?!?%d", stptr->type);
  }
}

void printSTNode(symtabnode *stptr)
{
  printf(">> %s: scope = %c; ",
	 stptr->name,
	 (stptr->scope == Global ? 'G' : 'L'));
  if (stptr->formal) {
    printf("<formal param #%d>; ", stptr->argpos);
  }
  printf("type: ");
  printType(stptr);
  printf("\n");
}

void DumpSymTabLocal()
{
  int i;
  symtabnode *stptr;

  printf("-------------------- LOCAL SYMBOL TABLE --------------------\n");

  for (i = 0; i < HASHTBLSZ; i++) {
    for (stptr = SymTab[Local][i]; stptr != NULL; stptr = stptr->next) {
      printSTNode(stptr);
    }
  }

  printf("------------------------------------------------------------\n");

}

void DumpSymTabGlobal()
{
  int i;
  symtabnode *stptr;

  printf("-------------------- GLOBAL SYMBOL TABLE --------------------\n");

  for (i = 0; i < HASHTBLSZ; i++) {
    for (stptr = SymTab[Global][i]; stptr != NULL; stptr = stptr->next) {
      printSTNode(stptr);
    }
  }

  printf("------------------------------------------------------------\n");

}

void DumpSymTab()
{
  DumpSymTabGlobal();
  DumpSymTabLocal();
}

/*********************************************************************/
