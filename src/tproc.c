#include <stdio.h>
#include <stdlib.h>
#include "tproc.h"

/* Variable globale permettant de calculer le haut de pile */
char* top_stack;

int
main ( int argc, char** argv )
{
  char up;
  top_stack = &up;
  init_schred();
  return EXIT_SUCCESS;
}
