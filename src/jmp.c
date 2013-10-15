#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jmp.h"
#include "tproc.h"
#include <unistd.h>

char* top_stack;


/* Le paramètre index correspond à l'index dans la table des processus de celui
   que l'on veut sauvegarder ou restaurer */
int
mysetjmp( int index )
{
  int old = index;
  /* Si setjmp renvoi 0 c'est que l'on a pas encore sauvegardé le contexte du
     processus index */
  if ( setjmp(tproc[old].buff) == 0 )
    {
      /* 1. Calcul de la taille de la pile du processus que l'on va swapper */
      tproc[old].p_size = top_stack - (char*)&old;

      /* 2. Allocation de la taille de la pile */
      tproc[old].p_stack = malloc(tproc[old].p_size);

      /* 3. Copie de la pile courante dans la structure */
      tproc[old].p_addr = (char*)&old;
      memcpy(tproc[old].p_stack, tproc[old].p_addr, tproc[old].p_size);
      /* 4. Sauvegarde du contexte dans le buffer du processus courant :
	 effectué dans le if */
      
      /* 5. On change l'état du processus */
      tproc[old].p_state = SNO;
      
      if ( DEBUG )
	puts("DEBUG: fin de sauvegarde du contexte");

      return 0;
    }
  else 
    {
      /* Si le jmp_buf n'est pas égal à zéro celà signifie que l'on est arrivé
	  ici par la fonction mylongjmp et qu'il faut restaurer la pile du
	  processus élu. La variable elu a été mise à jour par mylongjmp, ainsi
	  que le jmp_buff */
      memcpy(top_stack - tproc[elu].p_size, tproc[elu].p_stack, tproc[elu].p_size);

      tproc[elu].p_state = SRUNNING;

      if ( DEBUG )
	printf("DEBUG: le processus n°%d est a l'état RUNNING\n", elu);
      return 1;
    }
}

int
mylongjmp( int index )
{
  /* On positionne l'index du nouveau processus élu et on restaure ses
     registres */
  elu = index;
  sleep(1);
  longjmp(tproc[elu].buff, 1);

  return 1;
}
