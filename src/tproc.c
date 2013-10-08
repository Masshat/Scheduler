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

	  if ( mysetjmp(i) != 0 )
	    {
	      function(arg);
	      return;
	    }
	}
    }
}

/* TOFINISH */
void
election(void)
{
  /* int i = elu; */
  /* for ( ; i < NPROC; i++ ) */
  /*   { */
  /*     sleep(1); */
  /*     if ( tproc[i+1].p_state == SNO ) */
  /* 	{ */
  /* 	  if ( DEBUG ) */
  /* 	    printf("DEBUG: Le processus élu est le n°%d\n", i); */
  /* 	  break; */
  /* 	} */
  /*     printf("elu = %d\n", elu); */
  /*     if ( i == NPROC-1 ) */
  /* 	{ */
  /* 	  puts("on réinitialise elu"); */
  /* 	  i = 0; */
  /* 	  printf("elu = %d\n", elu); */
  /* 	}  */
  /*   } */
  /* elu = i; */
  /* mylongjmp(elu); */
}


#endif
