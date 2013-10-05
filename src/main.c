#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#include "tproc.h"
#include "jmp.h"



int
main ( int argc, char** argv )
{
  /* jmp_buf buff, bufg; */
  init_sched();
  
  if ( mysetjmp(1) == 0)
    f();
  else
    g();

  return EXIT_SUCCESS;
}
