#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tproc.h"
#include "jmp.h"


/* Variable globale permettant de calculer le haut de pile */
char* top_stack;

int elu;

void
f()
{
  int n = 0;
  
  while(1)
    {
      printf("Execute f: %d\n", n++);
      sleep(1);
      if ( mysetjmp(0) == 0 )
	mylongjmp(1);
    }
}

void
g()
{
  int m = 1000;

  while(1)
    {
      printf("Execute g: %d\n", m++);
      sleep(1);
      if ( mysetjmp(1) == 0 )
	mylongjmp(0);
    }
}
