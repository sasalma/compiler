#include "symbol-table.h"
#include "syntax-tree.h"
#include "codegen.h"
#include "optimization.h"

#define MAX_LOCAL_VARS 40


static tnode *ast;
static symtabnode *liveRangeNodes[MAX_LOCAL_VARS];
static int totalNodes, totalAvailRegs=5;
struct graphNode{ 
    symtabnode *sptr;
    bool isLive; // isLive is true if the node is live in the graph and not spilled yet;
    int cost;
    char varRegister[4];
    struct adjacencyList *adjList;
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