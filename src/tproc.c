#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tproc.h"
#include "jmp.h"


/* Variable globale permettant de calculer le haut de pile */
char* top_stack;
/* Variable globale contenant l'index du processus élu */
int elu;

void
f(int arg)
{
  printf("Le processus n°%d exécute f\n", arg);
  return;
}

void
g(int arg)
{
  printf("Le processus %d exécute g\n", arg);
  return;
}

void
new_proc(ptr_f function, int arg)
{
  int i;
  /* 1. On recherche une entrée libre dans la table. Ici, on va
     chercher dans tproc la premère entrée dont l'état du processus
     est SNO */
  for ( i = 0; i < NPROC; i++)
    {
      /* Si on trouve une entrée libre */
      if ( tproc[i].p_state == SNO )
	{
	  if ( DEBUG )
	    printf("DEBUG: L'entrée %d de la table des processus est libre\n", i);

	  /* On sauvegarde le contexte du processus à cet endroit */
	  if ( mysetjmp(i) != 0 )
	    {
	      /* Si on le restaure, on exécute la fonction */
	      function(arg);
	      break;
	    }
	    /* Sinon, une fois le contexte sauvegardé, on sort de la boucle */
	  else 
	    break;
	}
    }
  return;
}


int
election(void)
{
  elu++;
  return elu;
}
