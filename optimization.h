#include "symbol-table.h"
#include "syntax-tree.h"
#include "codegen.h"
#include "global.h"

#define MAX_BLOCK 100
#define MAX_PREDECESSOR 30
//#define MAX_LOCAL_VARS 40

Quad *leadersList[MAX_BLOCK];
int totalBlockLeaders; 

struct block{
    Quad *leader, *tail_leader;
    int predecessorList[MAX_PREDECESSOR];
    int total_predecessor;
    int successorList[MAX_PREDECESSOR];
    int total_successor;   
    // in
    // out
    // gen - kill => reaching definition => forward analysis
    // use - def => liveness checking => backward analysis
    struct liveAnalisysVarList *inList, *outList, *defList, *useList;
} *blockList[MAX_BLOCK];
typedef struct block Block;


static void localOptimization(void);
static void globalOptimization(void);
void doOptimization(tnode *ast);

static void copyPropagation(void);


symtabnode *liveSet[MAX_LOCAL_VARS];
struct liveAnalisysVarList{
    symtabnode *sptr;  // symbol table pointer for the variable
    struct liveAnalisysVarList *next;
};