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



static void getLocalVars();

// print routiens start
static void printNodes(void);
// print routiens end


void doRegAllocation(tnode *ast){
    //printf("do reg alloc here!\n");
    getLocalVars();
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
