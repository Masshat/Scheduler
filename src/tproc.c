#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tproc.h"
#include "jmp.h"


/* Variable globale permettant de calculer le haut de pile */
char* top_stack;
/* Variable globale contenant l'index du processus élu */
int elu;

#ifdef JMP
void
f(void)
{
  int n = 0;
  
  while(1)
    {
      printf("Execute f: %d\n", n++);
      sleep(1);
      if ( mysetjmp(0) == 0 )
	mylongjmp(1);
    }
}

void
g(void)
{
  int m = 1000;

  while(1)
    {
      printf("Execute g: %d\n", m++);
      sleep(1);
      if ( mysetjmp(1) == 0 )
	mylongjmp(0);
    }
}

#else

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
      if ( tproc[i].p_state == SNO )
	{
	  if ( DEBUG )
	    printf("DEBUG: L'entrée %d de la table des processus est libre\n", i);
	  break;
	}
    }
  if ( mysetjmp(i) == 0 )
    {
      if ( DEBUG )
	printf("DEBUG: On sauvegarde le contexte du processus %d\n", i);
      return;
    }
  else
    {
      printf("On remet en action le processus %d\n", i);
      function(arg);
      return;
    }

  /* /\* 2. On enregistre le processus à cette entrée *\/ */
  /* if ( mysetjmp(i) == 0 ) */
  /*   { */
  /*     printf("On sauvegarde le contexte du processus à l'entrée n°%d\n", i); */
  /*     return; */
  /*   }  */
  /* /\* 3. Le nouveau processus va exécuter function(arg) *\/ */
  /* else */
  /*   { */
  /*     if ( DEBUG ) */
  /* 	{ */
  /* 	  printf("Le processus n°%d est déjà sauvegardé, il va donc", i); */
  /* 	  printf("exécuter la fonction passée en paramètre\n"); */
  /* 	} */
  /*     function(arg); */
  /*   } */
  /* return; */
}

#endif
