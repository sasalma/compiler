/*
 * syntax-tree.h
 *
 * Author: Saumya Debray
 */

#ifndef _SYNTAX_TREE_H_
#define _SYNTAX_TREE_H_

#include "symbol-table.h"

typedef enum SyntaxNodeType {
  Error,
  Intcon,
  Charcon,
  Stringcon,
  Var,
  ArraySubscript,
  Plus,
  UnaryMinus,
  BinaryMinus,
  Mult,
  Div,
  Equals,
  Neq,
  Leq,
  Lt,
  Geq,
  Gt,
  LogicalAnd,
  LogicalOr,
  LogicalNot,
  FunCall,
  Assg,
  Return,
  For,
  While,
  If,
  STnodeList
} SyntaxNodeType; 

struct stref {  // symbol table reference: subscripted expr or function call
  symtabnode *stptr;
  struct treenode *exp;
};

struct node {  // statements, unary and binary expressions, and expression lists
  struct treenode *child0, *child1, *child2, *child3;
};

typedef struct treenode {
  enum SyntaxNodeType ntype;   // the node type for a syntax tree node
  int etype;  // the type of the value of a syntax tree node, once that
              // node has been evaluated.  For nodes that don't have a
              // value, e.g., statements, this is set to t_None.
  union {
    int iconst;
    char *strconst;
    struct stref strefNode;
    struct node  Node;
  } val;
  /* ---------- fields for code generation ---------- */
  symtabnode *place;    /* location where an expression's value will be placed */
  struct quad *code_hd, *code_tl;    /* three-address instruction list */
} tnode, *tnptr;

tnode *mkConstNode(SyntaxNodeType ntype, int etype, int n);
tnode *mkStrNode(char *s);
tnode *mkSymTabRefNode(SyntaxNodeType ntype, int etype, symtabnode *stptr, tnode *t0);
tnode *mkExprNode(SyntaxNodeType ntype, int etype, tnode *e1, tnode *e2);
tnode *mkSTNode(SyntaxNodeType ntype, int etype, tnode *x0, tnode *x1, tnode *x2, tnode *x3);
tnode *mkErrorNode(void);
tnode *mkListNode(tnode *hd, tnode *tl);
tnode *AppendReturn(tnode *t);

bool ActualsMatchFormals(symtabnode *fn, tnode *actuals);
tnode *SynTreeUnExp(SyntaxNodeType ntype, tnode *e1);
tnode *SynTreeBinExp(SyntaxNodeType ntype, tnode *e1, tnode *e2);

#define ConstVal(x)   (x)->val.iconst
#define StrVal(x)     (x)->val.strconst

#define SymTabPtr(x)  (x)->val.strefNode.stptr
#define ExprPtr(x)    (x)->val.strefNode.exp

#define LChild(x)     (x)->val.Node.child0
#define RChild(x)     (x)->val.Node.child1

#define Child0(x)     (x)->val.Node.child0
#define Child1(x)     (x)->val.Node.child1
#define Child2(x)     (x)->val.Node.child2
#define Child3(x)     (x)->val.Node.child3

#define ListNode(x)  (x)->val.Node.child0
#define ListNext(x)  (x)->val.Node.child1

#endif /* _SYNTAX_TREE_H_ */
