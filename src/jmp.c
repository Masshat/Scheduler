#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jmp.h"
#include "tproc.h"

int
mysetjmp( int index )
{
  int old = index;

  /* Si on ne vient pas de restaurer */
  if ( mysetjmp(tproc[old].buff == 0 ) )
    {
      /* 1. Calcul de la taille de la pile du processus que l'on va swapper */
      tproc[old].p_size = top_stack - (char*)&old;
      /* 2. Allocation de la taille de la pile */
      tproc[old].p_stack = malloc(sizeof(tproc[old].p_size));
      /* 3. Copie de la pile courante dans la structure */
      memcpy(tproc[old].p_stack, &tproc[old].p_addr, tproc[old].p_size);
      /* 4. Sauvegarde du contexte dans le buffer du processus courant */
      /* TODO */
      /* mylongjmp(); */
      return 1;
    }
  else
    {
      /* On restaure le contexte dans lequel on veut aller */
      memcpy(top_stack - tproc[elu].p_size, tproc[elu].p_stack, tproc[elu].p_size);
      return 0;
    }
}

/* int */
/* mylongjmp( int index ) */
/* { */
  
/* } */


