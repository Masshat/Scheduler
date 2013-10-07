#ifndef _H_TPROC
#define _H_TPROC

#include <setjmp.h>

/* Nombre maximum de processus que notre table peut accepter */
#define NPROC 42

/* Défini les deux états possibles pour un processus */
#define SNO 0
#define SRUNNING 1

/* Cette macro permet de calculer le début de la pile de la fonction main */
#define init_sched() ( { char var; top_stack = &var; } )

#define DEBUG 0

extern int elu;
extern char* top_stack;

/* Dans cette structure sont regroupé uniquement les informations qui nous sont
   utiles */
struct tproc{
  char     p_state; /* L'état du processus */
  char*    p_stack; /* L'adresse du haut de sa pile */
  char*    p_addr;  /* */
  int      p_size;  /* La taille de sa pile */
  jmp_buf  buff;    /* Son buffer */
} tproc[NPROC];

void f();
void g();

#endif
