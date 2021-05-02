#include "symbol-table.h"
#include "syntax-tree.h"
#include "codegen.h"
#include "optimization.h"



/*struct mapVarToReg{
    symtabnode *sptrVar;
    char *varRegister;
};
struct mapVarToReg mapping[MAX_LOCAL_VARS];
int totalMapping;*/

static tnode *ast;
static symtabnode *liveRangeNodes[MAX_LOCAL_VARS];
static int totalNodes, totalAvailRegs, totalRegister=18, totalUsedRegister=0;
static char registerAddress[18][4] = { "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9","$a1", "$a2", "$a3"};
static bool registerAvailable[18] = {true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };
struct graphNode{ 
    symtabnode *sptr;
    bool isLive; // isLive is true if the node is live in the graph and not spilled yet;
    int cost;
    //char *varRegister;
    struct adjacencyList *adjList;
    int registerIndex;
};

typedef struct graphNode GraphNode;
GraphNode *nodeList[MAX_LOCAL_VARS];

struct adjacencyList{
    GraphNode *node;    
    struct adjacencyList *next;
};


struct stack{
    GraphNode *node;
    struct stack *next;
} *statckTop;


static void insertTop(GraphNode *node){
    struct stack *newSpace = zalloc(sizeof(struct stack));
    newSpace->node = node;
    if(statckTop==NULL) statckTop = newSpace; // stack was empty ; first element inserted
    else {
        newSpace->next = statckTop;
        statckTop = newSpace;
    }
}



void doRegAllocation(tnode *ast);