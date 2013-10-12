#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#include "tproc.h"
#include "jmp.h"

int
main ( int argc, char** argv )
{

  ptr_f f_;

  init_sched();

  f_ = &f;
  new_proc(f_, 0);

  return EXIT_SUCCESS;
}
