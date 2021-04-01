#include "global.h"
#include "symbol-table.h"

extern int yydebug;
extern int yyparse();

extern bool optLocalFlag, optGlobalFlag, optRegAllocFlag;


int status = 0;

void checkOptimizationType(int total_args, char *argv[]){
  optLocalFlag = false;
  optGlobalFlag= false;

  for(int i=1; i<total_args; i++){
    if(strcmp(argv[i], "-Olocal")==0) optLocalFlag = true;
    else if(strcmp(argv[i], "-Oglobal")==0) optGlobalFlag = true;
    else if(strcmp(argv[i], "-Oregalloc")==0) optRegAllocFlag = true;
    else
      fprintf(stderr, "Unrecognised argument: %s\n", argv[i]);
  }  
}

int main(int total_args, char *argv[])
{
  checkOptimizationType(total_args,argv);

  SymTabInit(Global);
  SymTabInit(Local);
  
  if (yyparse() < 0) {
    printf("main: syntax error\n");
    status = 1;
  }

  return status;
}
