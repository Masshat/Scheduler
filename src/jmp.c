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
  if ( DEBUG )
    printf("mysetjmp: &old = %p\n", &old);
  /* Si setjmp renvoi 0 c'est que l'on a pas encore sauvegardé le contexte du
     processus index */
  if ( setjmp(tproc[old].buff) == 0 )
    {
      if ( DEBUG )
	printf("mysetjmp: On sauvegarde le contexte du processus %d\n", old);
      /* 1. Calcul de la taille de la pile du processus que l'on va swapper */
      tproc[old].p_size = top_stack - (char*)&old;

      /* 2. Allocation de la taille de la pile */
      tproc[old].p_stack = malloc(tproc[old].p_size);

      /* 3. Copie de la pile courante dans la structure */
      tproc[old].p_addr = (char*)&old;
      memcpy(tproc[old].p_stack, tproc[old].p_addr, tproc[old].p_size);

      /* 4. Sauvegarde du contexte dans le buffer du processus courant :
	 effectué dans le if */

      return 0;
    }
  else 
    {
      /* Si le jmp_buf n'est pas égal à zéro celà signifie que l'on est arrivé
	  ici par la fonction mylongjmp et qu'il faut restaurer la pile du
	  processus élu. La variable elu a été mise à jour par mylongjmp, ainsi
	  que le jmp_buff */
      if ( DEBUG )
	printf("mysetjmp: On restaure le contexte du processus %d\n", elu);

      memcpy(top_stack - tproc[elu].p_size, tproc[elu].p_stack, tproc[elu].p_size);
      return 1;
    }
}

int
mylongjmp( int index )
{
  if ( DEBUG ) 
    printf("mylonjmp: Restaure le contexte du processus %d\n", index);
  /* On positionne l'index du nouveau processus élu et on restaure ses
     registres */
  elu = index;
  longjmp(tproc[elu].buff, 1);

  /* On va ensuite dans la fonction mysetjmp pour restaurer la pile du processus
     nouvellement élu */
  return mysetjmp(elu);
}


