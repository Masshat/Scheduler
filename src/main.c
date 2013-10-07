#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#include "tproc.h"
#include "jmp.h"

int
main ( int argc, char** argv )
{

  init_sched();

  #ifdef JMP

  if ( DEBUG )
    printf("adresse de la pile du main: %p\n", top_stack);

  if ( mysetjmp(1) == 0)
      f();
  else
      g();

  #else

  ptr_f f_ = &f;
  new_proc(f_, 0);
  #endif

  return EXIT_SUCCESS;
}
