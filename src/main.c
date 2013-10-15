#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#include "tproc.h"
#include "jmp.h"

int
main ( int argc, char** argv )
{
  
  init_sched();

  /* On créé un processus et on le met dans la table */
  new_proc(&f, 0);
  new_proc(&g, 1);
  printf("\n");
  /* On débute l'ordonnancement */
  start_sched();
  
  return EXIT_SUCCESS;
}
