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
extern int Total_Local_Max;
static char* LoadIns[3] = {"lb", "lw", "lw"};
static char* StoreIns[3] = {"sb", "sw", "sw"};




static void destructor(void);

static void colorGraph(void);
static void assignRegisters(void);
static int getRegisterNumber( struct stack *stackPtr );
static bool isGraphEmpty(void);
static bool isSpillRequired(void);
static int getDegree(GraphNode *node);
static void sendNodeToStack();
static void spillNode(void);
static void spillNodeSimple(void);




static void constructInterfGraph(tnode *ast);
 void makeEdge(int i, int j);
 bool chkEdgeAlready(int i, int j);
 void pushToAdjList(int i, int j);
static void updateCost( int index, int frequency);
int getNodeIndex(symtabnode *sptr);
void initializeNodes();
void getLocalVars();


void storeToStackFrmReg(void); // before calling a function  
void loadFromStackToReg(void); // after returning from a function
static int getRegIndex(symtabnode *sptr);

// print routiens start
static void printNodes(void);
static void printGraph(void);
static void printStack(void);
// print routiens end


void doRegAllocation(tnode *ast){


    //printf("do reg alloc here!\n");
    //getLocalVars();
    //initializeNodes();
    constructInterfGraph(ast); //actually updating cost; interference graph is constructed in optimization.c file
    colorGraph();


    printf("\n");
    destructor();
}

static void destructor(void){
    int index;
    statckTop = NULL;
    for(int i=0;i<totalNodes;i++){
        index = nodeList[i]->registerIndex;
        if(index!=-1){
            if(registerAvailable[index]){
                totalUsedRegister++;            
                registerAvailable[index] = false;
            }
        }
        nodeList[i] = NULL;
    }    
    totalNodes = 0;
}



/************************************************************************
 *                           Graph  Coloring                             *
 * **********************************************************************/
static void colorGraph(void){
    int k, totalIteration =0;
    totalAvailRegs = totalRegister - totalUsedRegister;
    //k = totalAvailRegs;
    while(!isGraphEmpty()){
        sendNodeToStack();
        if(isSpillRequired()) spillNode();    // spillNode();  //  spillNodeSimple();
        totalIteration++;          
    //printf("\nso far iterations : %d", totalIteration);
        if(totalIteration>=100) break;
    }
    //printf("\nTotal iterations : %d", totalIteration);
    assignRegisters();
}

static void assignRegisters(void){
    int i;
//    totalMapping = 0;
    struct stack *stackPtr = statckTop;
    while(stackPtr){
        i = getRegisterNumber(stackPtr);
        stackPtr->node->registerIndex = i;
        stackPtr->node->sptr->registerAddr = registerAddress[i];
      //  printf("\n VAR %s is in REGISTER %s", stackPtr->node->sptr->name, stackPtr->node->sptr->registerAddr  );        
        stackPtr = stackPtr->next;

    }
}

static int getRegisterNumber( struct stack *stackPtr ){
    bool isAvailable;
    struct adjacencyList *tmp;
    for(int i=0; i<totalRegister; i++){//totalAvailRegs; i++){
      if(registerAvailable[i])  {
        isAvailable = true;        
        for(tmp = stackPtr->node->adjList;tmp; tmp = tmp->next){
            if(tmp->node->registerIndex == i) {
                isAvailable = false;
                break;
            }
        }

        if(isAvailable) {   return i;}
      }

    }
    return -1;
}



static bool isGraphEmpty(void){
    for(int i=0;i<totalNodes;i++){
        if(nodeList[i]->isLive) return false;
    }
    return true;
}

static bool isSpillRequired(void){
    for(int i=0;i<totalNodes;i++){
        if(nodeList[i]->isLive && getDegree(nodeList[i]) < totalAvailRegs) 
            return false;
    }
    return true;
}

static int getDegree(GraphNode *node){
    int degree = 0;
    struct adjacencyList *tmp = node->adjList;
    while(tmp){
        if(tmp->node->isLive) degree++;
        tmp = tmp->next;
    }
    return degree;
} 

static void sendNodeToStack(){
    bool changeFlag = true;
    while(changeFlag){ // do repeatedly
        changeFlag = false;
        for(int i=0;i<totalNodes;i++){
            if(nodeList[i]->isLive && getDegree(nodeList[i]) < totalAvailRegs){ 
                insertTop(nodeList[i]);
                nodeList[i]->isLive = false;
                changeFlag = true;
                //printStack();
            }
        } 
    }
    
   // printStack();
}


static void spillNodeSimple(void){
    float minCostPerDeg=0, costPerDeg;
    GraphNode *nodePtr;
    int spillNodeIndex=-1, degree;

    for(int i=0; i<totalNodes; i++){
        nodePtr = nodeList[i];
        if(nodePtr->isLive ){
            spillNodeIndex = i;
            break;
        }
    }

    if(spillNodeIndex!=-1) nodeList[spillNodeIndex]->isLive = false;
}


static void spillNode(void){
    float minCostPerDeg=0, costPerDeg;
    GraphNode *nodePtr;
    int spillNodeIndex=-1, degree;

    for(int i=0; i<totalNodes; i++){
        nodePtr = nodeList[i];
        if(nodePtr->isLive ){
            degree = getDegree(nodePtr);
            if(degree!=0){
                costPerDeg = nodePtr->cost / degree;
                if( minCostPerDeg > costPerDeg ){
                    minCostPerDeg = costPerDeg;
                    spillNodeIndex = i;
                }
            }
        }
    }

    if(spillNodeIndex!=-1) nodeList[spillNodeIndex]->isLive = false;
}


/************************************************************************
 *              Functions to make Interference Graph                    *
 * **********************************************************************/
static void constructInterfGraph(tnode *ast){
    // actually UPDATE costs of the graph nodes

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

        /*
        // make edge in the graph
        if(src1NodeIndex != dstNodeIndex)  makeEdge(src1NodeIndex, dstNodeIndex);
        if(src2NodeIndex != dstNodeIndex)  makeEdge(src2NodeIndex, dstNodeIndex);
        if(src1NodeIndex != src2NodeIndex)  makeEdge(src1NodeIndex, src2NodeIndex);
        */
        
    }

    //printGraph();
}

void makeEdge(int i, int j){
    if(i==j) return;
    if(i==-1 || j==-1) return; // either one or both are not vertex of the graph
    if(chkEdgeAlready(i,j)) return;
    pushToAdjList(i,j);
    pushToAdjList(j,i);
}

 bool chkEdgeAlready(int i, int j){
    if(nodeList[i]->adjList==NULL) return false; // no edges so far = adjacency list is empty
    struct adjacencyList *lptr = nodeList[i]->adjList;
    while(lptr){
        if(lptr->node == nodeList[j]) return true;
        lptr = lptr->next;
    }
    return false;
}

 void pushToAdjList(int i, int j){  // make an edge from i to j
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
    if(!nodeList[index]) return;
    nodeList[index]->cost += frequency;
}


int getNodeIndex(symtabnode *sptr){
    if(sptr->type == t_Func) return -1;
    for(int i=0; i<totalNodes; i++){
        if(liveRangeNodes[i]==sptr) return i;
    }
    return -1;
}

void initializeNodes(){
    GraphNode *nodePtr;
    for(int i=0;i<totalNodes;i++){
        nodePtr = zalloc(sizeof(GraphNode));
        nodePtr->sptr = liveRangeNodes[i];
        nodePtr->isLive = true;
        nodePtr->cost = 0;
        nodePtr->registerIndex = -1;
        //nodePtr->varRegister = "";
        
        nodeList[i] = nodePtr;
        nodePtr = NULL;
    }
}


void getLocalVars()
{
  int i;
  symtabnode *stptr;
  totalNodes = 0;

  //printf("----------- LOCAL Variables -------------\n");

  for (i = 0; i < HASHTBLSZ; i++) {
    for (stptr = SymTab[Local][i]; stptr != NULL; stptr = stptr->next) {
        if(!stptr->formal && stptr->type!=t_Array){ // why not formal vars into register?
            liveRangeNodes[totalNodes] = stptr;
            totalNodes++;
        }
    }
  }
    //printNodes();

    Total_Local_Max = totalNodes + 4;
}


void storeToStackFrmReg(void){

    symtabnode *s0;
    int i, regN;  
    printf("\n    # Before function call store values of local variables to stack from register\n");  
    for (i = 0; i < HASHTBLSZ; i++) {
        for (s0 = SymTab[Local][i]; s0 != NULL; s0 = s0->next) {
            if (s0->argpos == 0) {
                printf("\n    %s (loc: %d); ", s0->name, s0->offset);
                regN = getRegIndex(s0);
                if(regN != -1)
                    printf("\n    %s %s, %d($fp)     #%s", StoreIns[s0->type], registerAddress[regN],  s0->offset, s0->name);
            }
        }
    }  

  printf("\n\n");  
}

static int getRegIndex(symtabnode *sptr){
    for(int i=0;i<totalNodes;i++){
        if(sptr==nodeList[i]->sptr && nodeList[i]->isLive){
            return nodeList[i]->registerIndex;
        }
    }
    return -1;
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
    int d;
    struct adjacencyList *tmp;
    printf("Total Nodes = %d\n", totalNodes);
    for(int i=0;i<totalNodes;i++){
        if(nodeList[i]->isLive){
            printf("\nNode number = %d, Variable = %s, live state = %d", i, nodeList[i]->sptr->name, nodeList[i]->isLive);
            printf("\n\tAdjacency List : ");
            tmp = nodeList[i]->adjList;
            while(tmp){ 
                printf("%s ", tmp->node->sptr->name);
                tmp = tmp->next;
            }
            d = getDegree(nodeList[i]);
            printf("\tDegree = %d ", d);
            printf("\n\tNode cost = %d ", nodeList[i]->cost);
        }
    }
}

static void printStack(void){
    struct stack *stackPtr = statckTop;
    printf("\nPrinting Stack");
    while(stackPtr){
        printf("\n %s", stackPtr->node->sptr->name);
        stackPtr = stackPtr->next;
    }
}