#include "symbol-table.h"
#include "syntax-tree.h"
#include "codegen.h"
#include "optimization.h"


#define MAX_LOCAL_VARS 40


static tnode *ast;
static symtabnode *liveRangeNodes[MAX_LOCAL_VARS];
static int totalNodes;
static struct nodeInformation{
    int cost;
};


void doRegAllocation(tnode *ast);