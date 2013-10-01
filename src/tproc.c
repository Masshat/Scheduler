#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include "tproc.h"

struct {

  char    p_state;
  char    p_stack[65536];
  int     p_addr;
  int     p_size;
  jmp_buf buff;
} Tproc[NPROC];


int
main ( int argc, char** argv )
{
  char* top_stack;
  init_schred();

  return EXIT_SUCCESS;
}
