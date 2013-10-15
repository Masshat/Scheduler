#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tproc.h"
#include "jmp.h"
#include <signal.h>


/* Variable globale permettant de calculer le haut de pile */
char* top_stack;
/* Variable globale contenant l'index du processus élu */
int elu;

void f(int arg)
{
    int numbf;
    for (numbf = 0; numbf < 5;numbf++)
    {
      printf("Le processus n°%d exécute f au tour numéro %d\n", arg, numbf);
      sleep(1);
    };
    return;
} 

void g(int arg)
{
    int numbg;
    for (numbg = 0; numbg < 5;numbg++)
    {
      printf("Le processus %d exécute g au tour numéro %d\n", arg, numbg);
      sleep(1);
    }
    return;
}

void new_proc(ptr_f function, int arg)
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


int election(void)
{
    int i;
    int flag;

    flag = 0;
    i = elu;

    /* Tant que l'on a pas trouvé de processus à élire */
    while( !flag )
      {
        if ( i == NPROC )
          i = 0;

        if ( tproc[i].p_state == SNO )
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

void commut(int no)
{
  /* KB: on réalise un simple affichage*/
  printf("Le processus en cours de traitement est le %d\n", no);
  return;
}
void sig_hand(int sig)
{
  printf("signal reçu %d \n", sig);
  alarm(1);
}

void start_sched(void)
{
  /* initialisation du signal SIGALRM 
  int numbsig = 0; processus en cours d'execution*/
  sigset_t sig_proc;
  struct sigaction action;
  sigemptyset(&sig_proc);
  action.sa_mask=sig_proc;
  action.sa_flags=0;
  action.sa_handler=sig_hand;
  sigaction(SIGALRM, &action,0);
  alarm(1);
  /* test affichage
  while(1){
    if (numbsig == 0)
      { numbsig = 1 ;}
    else numbsig = 0 ;
    commut(numbsig);
    pause();
    }
  choix du processus*/
  int numproc = 0;
  for ( ; numproc < NPROC; numproc++)
  {
    /*on cherche un processus qui a été mis en attente A VERIFIER*/
    if (setjmp(tproc[numproc].buff) == 1)
    {
        /*on le restaure A VERIFIER */
        printf("On va restaurer le processus numéro %d\n", numproc);
        mysetjmp(numproc);
    }
  }
return;
}
