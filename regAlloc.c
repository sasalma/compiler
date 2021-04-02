#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protos.h"
#include "syntax-tree.h"
#include "util.h"
#include "codegen.h"
#include "regAlloc.h"


#define HASHTBLSZ 256
extern symtabnode *SymTab[2][HASHTBLSZ];


static void constructInterfGraph(tnode *ast);
static void makeEdge(int i, int j);
static void pushToAdjList(int i, int j);
static void updateCost( int index, int frequency);
static int getNodeIndex(symtabnode *sptr);
static void initializeNodes();
static void getLocalVars();


// print routiens start
static void printNodes(void);
static void printGraph(void);
// print routiens end


void doRegAllocation(tnode *ast){
    //printf("do reg alloc here!\n");
    getLocalVars();
    initializeNodes();
    constructInterfGraph(ast);
    
}



static void constructInterfGraph(tnode *ast){
    //GraphNode *dstNode, *src1Node, *src2Node;
    int dstNodeIndex, src1NodeIndex, src2NodeIndex;
    for(Quad *qptr=ast->code_hd;qptr!=ast->code_tl; qptr = qptr->next){
        dstNodeIndex = src1NodeIndex = src2NodeIndex = -1;
        if(qptr->dst && qptr->dst->optype == SYMTBL_PTR)  dstNodeIndex = getNodeIndex(qptr->dst->val.stptr);
        if(qptr->src1 && qptr->src1->optype == SYMTBL_PTR)  src1NodeIndex = getNodeIndex(qptr->src1->val.stptr);
        if(qptr->src2 && qptr->src2->optype == SYMTBL_PTR)  src2NodeIndex = getNodeIndex(qptr->src2->val.stptr);
    
        // for x = x + x; how to handle? right now it will add cost thrice
        if(dstNodeIndex != -1)  updateCost( dstNodeIndex, qptr->frequency);
        if(src1NodeIndex != -1)  updateCost( src1NodeIndex, qptr->frequency);
        if(src2NodeIndex != -1)  updateCost( src2NodeIndex, qptr->frequency);

        // make edge in the graph
        if(src1NodeIndex != dstNodeIndex)  makeEdge(src1NodeIndex, dstNodeIndex);
        if(src2NodeIndex != dstNodeIndex)  makeEdge(src2NodeIndex, dstNodeIndex);
        if(src1NodeIndex != src2NodeIndex)  makeEdge(src1NodeIndex, src2NodeIndex);
        
    }


    printGraph();
}

static void makeEdge(int i, int j){
    if(i==-1 || j==-1) return; // either one or both are not vertex of the graph
    pushToAdjList(i,j);
    pushToAdjList(j,i);
}

static void pushToAdjList(int i, int j){  // make an edge from i to j
    struct adjacencyList *l = nodeList[i]->adjList, *newNode = zalloc(sizeof(struct adjacencyList));
    newNode->node = nodeList[j];
    newNode->next = NULL;
    if(l==NULL){
        nodeList[i]->adjList = newNode;
        return;
    }

    while(l->next){
        l = l->next;
    }
    l->next = newNode;
}



static void updateCost( int index, int frequency){
    nodeList[index]->cost += frequency;
}


static int getNodeIndex(symtabnode *sptr){
    if(sptr->type == t_Func) return -1;
    for(int i=0; i<totalNodes; i++){
        if(liveRangeNodes[i]==sptr) return i;
    }
    return -1;
}

static void initializeNodes(){
    GraphNode *nodePtr;
    for(int i=0;i<totalNodes;i++){
        nodePtr = zalloc(sizeof(GraphNode));
        nodePtr->sptr = liveRangeNodes[i];
        nodePtr->isLive = true;
        
        nodeList[i] = nodePtr;
        nodePtr = NULL;
    }
}


static void getLocalVars()
{
  int i;
  symtabnode *stptr;
  totalNodes = 0;

  //printf("----------- LOCAL Variables -------------\n");

  for (i = 0; i < HASHTBLSZ; i++) {
    for (stptr = SymTab[Local][i]; stptr != NULL; stptr = stptr->next) {
        if(!stptr->formal){
            liveRangeNodes[totalNodes] = stptr;
            totalNodes++;
        }
    }
  }
    //printNodes();
}



/************************************************************************
 *                           Print Routiens                             *
 * **********************************************************************/
static void printNodes(void){
    printf("\nTotal Nodes = %d", totalNodes);
    for(int i=0; i< totalNodes;i++)
        printf("\n%s", liveRangeNodes[i]->name);
}

static void printGraph(void){
    struct adjacencyList *tmp;
    for(int i=0;i<totalNodes;i++){
        printf("\nNode number = %d, Variable = %s, live state = %d", i, nodeList[i]->sptr->name, nodeList[i]->isLive);
        printf("\n Adjacency List : ");
        tmp = nodeList[i]->adjList;
        while(tmp){ 
            printf("%s ", tmp->node->sptr->name);
            tmp = tmp->next;
        }
    }
}
