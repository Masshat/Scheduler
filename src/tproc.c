#define _XOPEN_SOURCE 700

#include "tproc.h"
#include "jmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


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
	    tproc[i].p_state = SREADY;
	    break;
	}
    }
  return;
}


int
election(void)
{
  int i;
  int flag;

  flag = 0;
  i = elu;

  /* Tant que l'on a pas trouvé de processus à élire */
  while( !flag )
    {
      /* INFINITE LOOP HERE */
      /* Problème: le changement d'état des processus */
      if ( i == NPROC )
	i = 0;

      if ( tproc[i].p_state == SREADY )
	{
	  flag = 1;
	  elu = i;
#ifdef DEBUG
	  printf("DEBUG: processus élu: %d\n", elu);
#endif
	  return elu;
	}
      i++;
    }
  return -1;
}

void
commut(int sig)
{
  printf("DEBUG: COMMUTATION\n");
  mylongjmp(election());
  alarm(1);
}

void
start_sched(void)
{
  sigset_t sig_proc;
  struct sigaction action;

  sigemptyset(&sig_proc);
  action.sa_mask    = sig_proc;
  action.sa_flags   = 0;
  action.sa_handler = commut;
  sigaction(SIGALRM, &action, 0);
  alarm(1);

  /* On le restaure */
  mylongjmp(election());
}
