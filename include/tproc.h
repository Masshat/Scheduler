#ifndef _H_TPROC
#define _H_TPROC

#include <setjmp.h>

/* Nombre maximum de processus que notre table peut accepter */
#define NPROC 2

/* Défini les deux états possibles pour un processus */
#define SNO 0
#define SRUNNING 1

/* Cette macro permet de calculer le début de la pile de la fonction main */
#define init_sched() ( { char var; top_stack = &var; } )

#define DEBUG 1

/* #define JMP */

extern int elu;
extern char* top_stack;
/* On déclare un type pointeur de fonction */
typedef void(*ptr_f) (int); 

/* Dans cette structure sont regroupé uniquement les informations qui nous sont
   utiles */
struct tproc{
  int      p_state;
  char*    p_stack;
  char*    p_addr;
  int      p_size;
  jmp_buf  buff;
} tproc[NPROC];

#ifdef JMP
void f(void);
void g(void);
#else
void f(int arg);
void g(int arg);
void new_proc(ptr_f function, int arg);
void election(void);
#endif

#endif
