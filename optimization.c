#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protos.h"
#include "syntax-tree.h"
#include "util.h"
#include "codegen.h"
#include "optimization.h"


bool optLocalFlag, optGlobalFlag;




static void findLeaders(void);
static bool IsNewLeader(Quad *qptr);
static bool noBranchJump(Op op);
static void initBlock(int blockNumber);
static void addPredecessorSuccessor(int block_number, Quad *q_ptr);
static void addPredSucc(int block_number, int b);
static int findBlock_of_leader(Quad *q);

static void setBackwardPtrs(void);
static void peepholeOptimization(void);
static void peepholeAssgOpt(void);

static void copyPropForBlock(int i);


static bool eiliminateDeadCode(int blockNumber);
static void dumpLiveSET(void);
static bool checkLive(symtabnode *sym_tab_Ptr);
static void insertIntoLiveSet(symtabnode *sym_tab_Ptr);
static void removeFromLiveSet(symtabnode *sym_tab_Ptr);
static void initLiveSet(int blockNumber);


static void livenessAnalysys(void);
static void initDefUseList(void);
static void printDefUseList();
static struct liveAnalisysVarList *insertToList(struct liveAnalisysVarList *p, symtabnode *varPtr);
static struct liveAnalisysVarList *removeFromList(struct liveAnalisysVarList *p, symtabnode *varPtr);
static void updateInList(int blockNumber);
static bool updateOutList(int blockNumber);
static bool checkList(struct liveAnalisysVarList *p, symtabnode *varPtr);
static bool anyChange(struct liveAnalisysVarList *varList, struct liveAnalisysVarList *varListNew);


static tnode *ast;
static void destructor(void);



void doOptimization(tnode *ast_codegen){
//optGlobalFlag = true; 
//optLocalFlag = true;   


    if(!optLocalFlag && !optGlobalFlag) return; // no optimization

    ast = ast_codegen;
    setBackwardPtrs();
    //peepholeOptimization();


    //printf(" \n **  do local optimization here **\n");
    findLeaders();

    // construct all the blocks
    Block *block_ptr;
    for(int i=0; i<totalBlockLeaders; i++){
        block_ptr= zalloc(sizeof(struct block));
        block_ptr->leader = leadersList[i];
        block_ptr->total_predecessor = 0;
        block_ptr->total_successor = 0; 
        block_ptr->inList = NULL;
        block_ptr->outList = NULL;
        block_ptr->defList = NULL;
        block_ptr->useList = NULL;
        blockList[i] = block_ptr;    
    }


    // initialize info for all the blocks
    for(int i=0; i<totalBlockLeaders; i++){
        initBlock(i);
    }


    /*
    // print all predecessor list
    for(int i=0;i<totalBlockLeaders;i++){
        printf("\n total # of predecessors of Block-%d : %d\n", i, blockList[i]->total_predecessor );
        for(int j= 0; j< blockList[i]->total_predecessor;j++ )
            printf("\t%d",blockList[i]->predecessorList[j]);
    }*/
    /*
    // print all successor list
    for(int i=0;i<totalBlockLeaders;i++){
        printf("\n total # of successors of Block-%d : %d\n", i, blockList[i]->total_successor );
        for(int j= 0; j< blockList[i]->total_successor;j++ )
            printf("\t%d",blockList[i]->successorList[j]);
    }*/


    
    if(optLocalFlag) localOptimization();
    if(optGlobalFlag) globalOptimization();

    // destructor
    destructor();
}

static void destructor(void){
    //free(ast);
    ast = NULL;
    for(int i=0; i<totalBlockLeaders; i++){
        free(blockList[i]);
        blockList[i] = NULL;
    } 
    totalBlockLeaders = 0;
    dumpLiveSET();   
}


/******************************************************************
 *
 *       local optimization  
 * 
 * ****************************************************************/
static void localOptimization(void){
    //printf("\nDo LOCAL optimization\n");
    copyPropagation();
}


static void copyPropagation(void){
    for(int i=0; i<totalBlockLeaders; i++){
        copyPropForBlock(i);
    }

}

static void copyPropForBlock(int i){
    Quad *qptr, *qptr_next_ins=NULL;   
    for(qptr= blockList[i]->leader; qptr && qptr != leadersList[i+1]; qptr = qptr->next){
        if(qptr->op==MOVE){
            for(qptr_next_ins=qptr->next; qptr_next_ins!=NULL && qptr_next_ins->op==NOP; qptr_next_ins = qptr_next_ins->next){
            }
            if(qptr_next_ins!=NULL && qptr_next_ins->op==MOVE &&  qptr->dst->val.stptr->type == qptr_next_ins->dst->val.stptr->type && qptr->dst->val.stptr == qptr_next_ins->src1->val.stptr){
                qptr_next_ins->src1= qptr->src1;
            }
        }
    }
}
/******************* END OF LOCAL OPTIMIZATION ****************************/



/******************************************************************
 *
 *       Global optimization  
 * 
 * ****************************************************************/
static void globalOptimization(void){
    //printf("\nDo GLOBAL optimization\n");
    //dumpLiveSET();
  //  initDefUseList();
    //printDefUseList();

    bool changeFlag = true, flag;
    //Quad *codeQuad;
    while(changeFlag){
        changeFlag = false;
        initDefUseList();
        livenessAnalysys();
        for(int i=totalBlockLeaders-1; i>=0; i--){
            initLiveSet(i);// initialyze live set for block i
            flag = eiliminateDeadCode(i);
            if(flag==true) changeFlag = true;
        }
    }
}

static bool eiliminateDeadCode(int blockNumber){
    bool changeFlag = false;   
    int i = blockNumber;
    Quad *qptr, *qptr_next_ins=NULL;   
    for(qptr= blockList[i]->tail_leader; ; qptr = qptr->previous){
        switch(qptr->op){
            case UMINUS_OP:
            case MOVE: 
                if(qptr->src1->optype==SYMTBL_PTR && qptr->src1->val.stptr->type == t_Func) 
                    break;
                
                if(qptr->dst->optype == DEREF || checkLive(qptr->dst->val.stptr)){
                        removeFromLiveSet(qptr->dst->val.stptr);
                    if(qptr->dst->optype == DEREF )  
                        insertIntoLiveSet(qptr->dst->val.stptr);

                    if(qptr->src1->optype==SYMTBL_PTR  || qptr->src1->optype == DEREF)
                        insertIntoLiveSet(qptr->src1->val.stptr);
                }
                else { qptr->op = NOP; // mark as dead
                    changeFlag = true;
                }
                break;
                
            case ADD_OP:
            case SUB_OP:
            case MUL_OP:
            case DIV_OP:
                if(checkLive(qptr->dst->val.stptr)){
                    removeFromLiveSet(qptr->dst->val.stptr);
                    if(qptr->src1->optype==SYMTBL_PTR && qptr->src1->val.stptr->type != t_Func)
                        insertIntoLiveSet(qptr->src1->val.stptr);
                    if(qptr->src2->optype==SYMTBL_PTR && qptr->src1->val.stptr->type != t_Func)
                        insertIntoLiveSet(qptr->src2->val.stptr);
                }
                else { qptr->op = NOP; // mark as dead
                    changeFlag = true;
                }
                break;

            case PARAM:
                if((qptr->src1->optype==SYMTBL_PTR && qptr->src1->val.stptr->type != t_Func)||qptr->src1->optype==DEREF)
                    insertIntoLiveSet(qptr->src1->val.stptr); 
                break;

            case RETRIEVE:
                if(checkLive(qptr->src1->val.stptr)){
                    removeFromLiveSet(qptr->src1->val.stptr);
                }            
                break;

            case RET:
                if(qptr->src1!=NULL && qptr->src1->optype==SYMTBL_PTR )
                    insertIntoLiveSet(qptr->src1->val.stptr); 
                break;


            case IF_EQ: 
            case IF_NE: 
            case IF_LE: 
            case IF_LT: 
            case IF_GE: 
            case IF_GT:
                if(qptr->src1->optype==SYMTBL_PTR)
                    insertIntoLiveSet(qptr->src1->val.stptr);
                if(qptr->src2->optype==SYMTBL_PTR)
                    insertIntoLiveSet(qptr->src2->val.stptr);
                break;    
            default: break;
        }

        if(qptr==blockList[i]->leader) break; //reached to the top of the block
    }
    return changeFlag;
}

static void initLiveSet(int blockNumber){
    struct liveAnalisysVarList *out = blockList[blockNumber]->outList;
    dumpLiveSET();
    while(out){
        insertIntoLiveSet(out->sptr);
        out = out->next;
    }
}

static void dumpLiveSET(void){
    for(int i=0;i<MAX_LOCAL_VARS;i++){
        liveSet[i]=NULL;
    }
}

static bool checkLive(symtabnode *sym_tab_Ptr){
    if(sym_tab_Ptr->scope==Global) return true; //Global vars are always live => always return true

    for(int i=0;i<MAX_LOCAL_VARS;i++){
        if(liveSet[i]==sym_tab_Ptr) {
            return true;
        }
    }
    return false;    
}

static void insertIntoLiveSet(symtabnode *sym_tab_Ptr){
    if(sym_tab_Ptr->scope==Global) return; //Global vars are always live => no need to deal with
    if(checkLive(sym_tab_Ptr)) return;

    for(int i=0;i<MAX_LOCAL_VARS;i++){
        if(liveSet[i]==NULL) {
            liveSet[i]=sym_tab_Ptr;
            return;
        }
    }
}

static void removeFromLiveSet(symtabnode *sym_tab_Ptr){
    if(sym_tab_Ptr->scope==Global) return; //Global vars are always live => no need to deal with

    for(int i=0;i<MAX_LOCAL_VARS;i++){
        if(liveSet[i]==sym_tab_Ptr) {
            liveSet[i]=NULL;
            return;
        }
    }
}

static void printDefUseList(){
    struct liveAnalisysVarList *tmp;
    for(int i = 0; i<totalBlockLeaders; i++){
        printf("\nDEF list of block-%d :   ", i);
        tmp = blockList[i]->defList;
        while(tmp){
            printf(" %s,", tmp->sptr->name);
            tmp = tmp->next;
        }
        printf("\n\tUSE list of block-%d :   ", i);
        tmp = blockList[i]->useList;
        while(tmp){
            printf(" %s,", tmp->sptr->name);
            tmp = tmp->next;
        }    }
}

// Liveness analisys START
static void livenessAnalysys(void){    
    // for each basic block B, set in[B] = use[B];
    for(int i=totalBlockLeaders-1; i>=0; i--){
        blockList[i]->inList = blockList[i]->useList;
    }

    bool changeFlag = true, flagOut;//, flagIn;
    while(changeFlag){ //repeat
        changeFlag = false;
        for(int i=totalBlockLeaders-1; i>=0; i--){
            flagOut = updateOutList(i);
            if(flagOut==true) { 
                changeFlag = true;                
            }
            updateInList(i);
            //if(flagIn==true) changeFlag = true;
            
            //if(flagOut!=flagIn)  printf("\nCONTRAdicttion flagIn: %d \t flagOut = %d", flagIn, flagOut );
        }   
    }
}


static void updateInList(int blockNumber){ //        in[B] = use[B] ∪ (out[B] – def[B]);
    struct liveAnalisysVarList *out;
    Block *currBlock;
    //bool changeFlag = false;   
    currBlock = blockList[blockNumber];
    currBlock->inList = currBlock->useList;

    out = currBlock->outList;
    while(out){
        if(!checkList(currBlock->defList, out->sptr ) ){  //&&  !checkList(currBlock->inList, out->sptr)  ){
            currBlock->inList = insertToList(currBlock->inList, out->sptr);
            //changeFlag=true;
        }
        out = out->next;
    }

    //return changeFlag;    
}

static bool updateOutList(int blockNumber){
    struct liveAnalisysVarList *inSucc, *newOutList=NULL;
    Block *succBlock, *currBlock;
    bool changeFlag = false;
    
    currBlock = blockList[blockNumber];
    for(int i=0; i<currBlock->total_successor; i++){
        succBlock = blockList[currBlock->successorList[i]];
        inSucc = succBlock->inList;
        while(inSucc){
            if(!checkList(newOutList, inSucc->sptr)) {
                //currBlock->outList = insertToList(currBlock->outList, inSucc->sptr);
                newOutList = insertToList(newOutList,inSucc->sptr);
            }
            inSucc = inSucc->next;
        }
    }

    changeFlag = anyChange(currBlock->outList, newOutList);
    if(changeFlag) currBlock->outList = newOutList;
    return changeFlag;
}

static bool anyChange(struct liveAnalisysVarList *varList, struct liveAnalisysVarList *varListNew){
    struct liveAnalisysVarList *tmp;
    for(tmp=varList; tmp!=NULL; tmp = tmp->next){
        if(!checkList(varListNew, tmp->sptr)) return true;
    }

    for(tmp=varListNew; tmp!=NULL; tmp = tmp->next){
        if(!checkList(varList, tmp->sptr)) return true;
    }

    return false;
}

static void initDefUseList(void){
    struct liveAnalisysVarList *D, *U;
    Quad *qptr;
    for(int i = totalBlockLeaders-1; i>=0; i--){
        D = NULL;
        U = NULL;
        for(qptr= blockList[i]->tail_leader; ; qptr = qptr->previous){
            switch (qptr->op)
            {
            case UMINUS_OP:    
            case MOVE:
                if(qptr->dst->optype != DEREF){
                    D = insertToList(D, qptr->dst->val.stptr);                    
                    U = removeFromList(U, qptr->dst->val.stptr); 
                }
                else 
                    U = insertToList(U, qptr->dst->val.stptr);
               
                if((qptr->src1->optype == SYMTBL_PTR || qptr->src1->optype == DEREF) && qptr->src1->val.stptr->type != t_Func){
                    D = removeFromList(D, qptr->src1->val.stptr);
                    U = insertToList(U, qptr->src1->val.stptr);
                }
                break;

            case ADD_OP:
            case SUB_OP:
            case MUL_OP:
            case DIV_OP:
                D = insertToList(D, qptr->dst->val.stptr);                    
                U = removeFromList(U, qptr->dst->val.stptr); 

                if(qptr->src1->optype == SYMTBL_PTR && qptr->src1->val.stptr->type != t_Func){
                    D = removeFromList(D, qptr->src1->val.stptr);
                    U = insertToList(U, qptr->src1->val.stptr);
                }                
                if(qptr->src2->optype == SYMTBL_PTR && qptr->src1->val.stptr->type != t_Func){
                    D = removeFromList(D, qptr->src2->val.stptr);
                    U = insertToList(U, qptr->src2->val.stptr);
                }                 
                break;

            case PARAM:
                if(qptr->src1->optype == SYMTBL_PTR && qptr->src1->val.stptr->type != t_Func){
                    U = insertToList(U, qptr->src1->val.stptr);
                }
                break;

            case RETRIEVE:
                D = insertToList(D, qptr->src1->val.stptr);                    
                U = removeFromList(U, qptr->src1->val.stptr);            
                break;

            case RET : 
                if (qptr->src1 != NULL && qptr->src1->optype == SYMTBL_PTR )
                    U = insertToList(U, qptr->src1->val.stptr);
                break;
                
            case IF_EQ: 
            case IF_NE: 
            case IF_LE: 
            case IF_LT: 
            case IF_GE: 
            case IF_GT:
                if(qptr->src1->optype == SYMTBL_PTR){
                    U = insertToList(U, qptr->src1->val.stptr);
                }
                if(qptr->src2->optype == SYMTBL_PTR){
                    U = insertToList(U, qptr->src2->val.stptr);
                }                                
                break;

            default:
                break;
            }

            if(qptr==blockList[i]->leader) { //reached to the top of the block
                blockList[i]->defList = D;
                blockList[i]->useList = U;
                break;
            }            
        }
    }

}

static struct liveAnalisysVarList *insertToList(struct liveAnalisysVarList *p, symtabnode *varPtr){
    if(checkList(p, varPtr)) return p; // already inserted, so return doing nothing

    struct liveAnalisysVarList *newVarListNode, *ptr;
    newVarListNode = zalloc(sizeof(struct liveAnalisysVarList));
    newVarListNode->sptr = varPtr;
    newVarListNode->next = NULL;

    if(p==NULL){ // list is initially empty
        p = newVarListNode;
        return p;
    }

    ptr = p;
    while(ptr->next){ ptr = ptr->next; }
    ptr->next = newVarListNode;

    return p;
} 

static struct liveAnalisysVarList *removeFromList(struct liveAnalisysVarList *p, symtabnode *varPtr){
    if(!checkList(p, varPtr)) return p; // varPtr not existed, so return doing nothing

    if(p==NULL) return NULL;
    if(p->sptr == varPtr) { p = p->next; return p;} // remove the first node from the list 
    
    struct liveAnalisysVarList *ptr=p;
    while (ptr->next)
    {
        if(ptr->next->sptr == varPtr){
            ptr->next = ptr->next->next;
            return p;
        }
        ptr = ptr->next;
    }
    return p;
}

static bool checkList(struct liveAnalisysVarList *p, symtabnode *varPtr){
    while(p){
        if(p->sptr == varPtr) {return true;}
        p = p->next;
    }
    return false;
}
// Liveness analisys END

/******************* END OF Global OPTIMIZATION ****************************/






/******************************************************************
 *
 *       peephole optimization  
 * 
 * ****************************************************************/
static void peepholeOptimization(){
    peepholeAssgOpt();
}

static void peepholeAssgOpt(){  //  optimization for assignments
    Quad *qptr, *qptr_next_ins=NULL;   
    for(qptr= ast->code_hd; qptr->next!=NULL; qptr = qptr->next){
        if(qptr->op==MOVE && qptr->src1->optype==SYMTBL_PTR){
            for(qptr_next_ins=qptr->next; qptr_next_ins!=NULL && qptr_next_ins->op==NOP; qptr_next_ins = qptr_next_ins->next){
            }
            if(qptr_next_ins!=NULL && qptr_next_ins->op==MOVE &&  qptr->dst->val.stptr->type == qptr_next_ins->dst->val.stptr->type && qptr->dst->val.stptr == qptr_next_ins->src1->val.stptr){
                qptr_next_ins->src1->val.stptr = qptr->src1->val.stptr;
            }
        }
    }
}




/******************* END OF PEEPHOLE OPTIMIZATION ****************************/






/******************************************************************
 *
 *       Initial Operations  
 * 
 * ****************************************************************/
static void setBackwardPtrs(void){
    Quad *qptr;
    qptr= ast->code_hd;
    qptr->previous = NULL;
    for(; qptr->next!=NULL; qptr = qptr->next){
        qptr->next->previous = qptr;
    }
    ast->code_tl = qptr;
}


static int findBlock_of_leader(Quad *q){
    for(int i=0; i<totalBlockLeaders;i++){
        if(q==blockList[i]->leader) return i;
    }
    return -1;
}

//block_number=predecessor , b = successor
static void addPredSucc(int block_number, int b){
    Block *predecessorBlock, *successorBlock;
    predecessorBlock = blockList[block_number];
    successorBlock = blockList[b];    
    bool flagAlready = false;
    for(int i=0; i< successorBlock->total_predecessor; i++)
        if(successorBlock->predecessorList[i]== block_number) {flagAlready =true; break;}
    if(!flagAlready){    
        successorBlock->predecessorList[successorBlock->total_predecessor] = block_number;
        successorBlock->total_predecessor++;
    }

    flagAlready = false;
    for(int i=0; i< predecessorBlock->total_successor;i++)
        if(predecessorBlock->successorList[i]== b) {flagAlready =true; break;}
    if(!flagAlready){    
        predecessorBlock->successorList[predecessorBlock->total_successor] = b;
        predecessorBlock->total_successor++;
    }
} 

// block_number is the predecessor of Block with leader q_ptr
static void addPredecessorSuccessor(int block_number, Quad *q_ptr){ 
    int b = findBlock_of_leader(q_ptr);
    addPredSucc(block_number,b);
}


static void initBlock(int blockNumber){
    Quad *q_ptr;
    int nextBlockNumber = -1;
    bool branch_flag = false;
    for(q_ptr = blockList[blockNumber]->leader; q_ptr && nextBlockNumber==-1;  q_ptr = q_ptr->next, nextBlockNumber = findBlock_of_leader(q_ptr))
    {        
        //if(q_ptr->next==NULL || q_ptr->next == leadersList[blockNumber+1]) // q_ptr is the tail 
          //  blockList[blockNumber]->tail_leader = q_ptr;
        
        switch(q_ptr->op){
            case NOP:
            case ENTER:
                /* do nothing */
                break;

            case IF_EQ: 
            case IF_NE: 
            case IF_LE: 
            case IF_LT: 
            case IF_GE: 
            case IF_GT:           
                        //branch_flag=true;                            
            case GOTO:   
                        addPredecessorSuccessor( blockNumber,  (q_ptr->dst->val).insptr );   
                        break;   
            default: break;
        }
    }

    if(q_ptr)   blockList[blockNumber]->tail_leader = q_ptr->previous;
        else    blockList[blockNumber]->tail_leader = ast->code_tl;

    if(q_ptr && blockList[blockNumber]->tail_leader->op!= GOTO) // "!branch_flag &&  no jump of branch instruction found"
        {
            addPredSucc(blockNumber, nextBlockNumber);
        }
}



static void findLeaders(){
    Quad *qptr;
    totalBlockLeaders = 0;

    //leadersList[0] = ast->code_hd;  // Every first statement is a leader.
    //totalBlockLeaders++;

    qptr = ast->code_hd;
    while(qptr)  
    {
        //printf("\n%d",qptr->op);
        switch(qptr->op){
            case ENTER: //the entry point of the function is a leader.
                    leadersList[totalBlockLeaders]= qptr; 
                    totalBlockLeaders++;
                    break; 

            //any instruction that is the target of a branch is a leader;
            case IF_EQ: 
            case IF_NE: 
            case IF_LE: 
            case IF_LT: 
            case IF_GE: 
            case IF_GT:
            case GOTO:
                if(IsNewLeader((qptr->dst->val).insptr)){
                    leadersList[totalBlockLeaders]= (qptr->dst->val).insptr; 
                    totalBlockLeaders++;
                }
                
                //any instruction following a (conditional or unconditional) branch is a leader.
                if(qptr->next && IsNewLeader(qptr->next)){  // && noBranchJump(qptr->next->op)
                    leadersList[totalBlockLeaders]= qptr->next; 
                    totalBlockLeaders++;
                    //qptr = qptr->next;
                }
                break; 

            default: break;
        }
        qptr = qptr->next;    
    }

    // print the leaders
    /*
    printf("\nTotal # of leaders : %d", totalBlockLeaders);
    for(int i=0;i<totalBlockLeaders;i++){
        printf("\n LEADER %d:   %d", i, leadersList[i]->op);
        if(leadersList[i]->op == LABEL) printf("    Lbl %d", leadersList[i]->src1->val.numval);
    }
    printf("\n All leaders are printed!");
    */
}

static bool IsNewLeader(Quad *qptr){
    for(int i=0;i<totalBlockLeaders;i++){
        if(qptr == leadersList[i]) return false;
    }
    return true;
}

static bool noBranchJump(Op op){
    switch(op){
            case IF_EQ: 
            case IF_NE: 
            case IF_LE: 
            case IF_LT: 
            case IF_GE: 
            case IF_GT:
            case GOTO:
                    return false;
                    break; 
            default: return true;
                    break;       
    }
    return true;
}