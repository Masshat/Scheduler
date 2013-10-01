#ifndef _H_TPROC
#define _H_TPROC

#include "setjmp.h"

/* Nombre maximum de processus que notre table peut accepter */
#define NPROC 42

/* Défini les deux états possibles pour un processus */
#define SNO 0
#define SRUNNING 1

/* Cette macro permet de calculer le début de la pile de la fonction main */
#define init_schred() ( { char var; top_stack = &var; } )

int elu;

struct tproc{
  char     p_state;
  char*    p_stack;
  int      p_addr;
  int      p_size;
  jmp_buf  buff;
} tproc[NPROC];

#endif
