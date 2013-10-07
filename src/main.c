#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#include "tproc.h"
#include "jmp.h"

int
main ( int argc, char** argv )
{
  init_sched();
  if ( DEBUG )
    printf("adresse de la pile du main: %p\n", top_stack);
  if ( mysetjmp(1) == 0)
    {
      f();
    }
  else
    {
      g();
    }



  return EXIT_SUCCESS;
}
