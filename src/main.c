#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#include "tproc.h"
#include "jmp.h"

int
main ( int argc, char** argv )
{

  ptr_f f_;
  ptr_f g_;
  int res;

  init_sched();

  f_ = &f;
  new_proc(f_, 0);
  res = election();
  tproc[res].p_state = SRUNNING;
  g_ = &f;
  new_proc(g_, 1);
  election();

  return EXIT_SUCCESS;
}
