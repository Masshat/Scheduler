#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jmp.h"
#include "tproc.h"


char* top_stack;


/* Le paramètre index correspond à l'index dans la table des processus de celui
   que l'on veut sauvegarder ou restauter */
int
mysetjmp( int index )
{
  int old = index;

  /* Si le jmp_buf est à zéro c'est que l'on a pas encore sauvegardé le contexte
     du processus index */
  if ( mysetjmp(tproc[old].buff) == 0 )
    {
      /* 1. Calcul de la taille de la pile du processus que l'on va swapper */
      tproc[old].p_size = top_stack - (char*)&old;
      /* 2. Allocation de la taille de la pile */
      tproc[old].p_stack = malloc(sizeof(tproc[old].p_size));
      /* 3. Copie de la pile courante dans la structure */
      memcpy(tproc[old].p_stack, &tproc[old].p_addr, tproc[old].p_size);
      /* 4. Sauvegarde du contexte dans le buffer du processus courant */
      setjmp(tproc[old].buff);
      return 0;
    }
  else /* Si le jmp_buf n'est pas égal à zéro celà signifie que l'on est arrivé
	  ici par la fonction mylongjmp et qu'il faut restaurer le contexte du
	  processus elu (elu a été mis à jour par mylonghmp */
    {
      memcpy(top_stack - tproc[elu].p_size, tproc[elu].p_stack, tproc[elu].p_size);
      return 1;
    }
}

int
mylongjmp( int index )
{
  elu = index;
  return mysetjmp(elu);
}


