#include "symbol-table.h"
#include "syntax-tree.h"
#include "codegen.h"
#include "optimization.h"


#define MAX_LOCAL_VARS 40


static tnode *ast;
static symtabnode *liveRangeNodes[MAX_LOCAL_VARS];
static int totalNodes;
struct graphNode{
    symtabnode *sptr;
    bool isLive; // isLive is true if the node is live in the graph and not spilled yet;
    int cost, degree;
    char varRegister[4];
    struct adjacencyList *adjList;
};

typedef struct graphNode GraphNode;
GraphNode *nodeList[MAX_LOCAL_VARS];

struct adjacencyList{
    GraphNode *node;    
    struct adjacencyList *next;
};



void doRegAllocation(tnode *ast);