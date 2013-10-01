#ifndef _H_JMP
#define _H_JMP

extern char* top_stack;

/* Surcharge des fonctions longjmp et setjmp */
int mysetjmp( int index );
int mylongjmp( int index );

#endif
