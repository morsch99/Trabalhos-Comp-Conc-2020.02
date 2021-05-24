/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 7 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NTHREADS  4

/* Variaveis globais */
sem_t condt2e3, condt4;


/* Thread t1 */
void *t1 (void *t) {
  //printf("T1: Comecei\n");
  sem_wait(&condt4);
  sem_post(&condt2e3);
  sem_wait(&condt4);
  
  printf("Volte Sempre!\n");
  //printf("Thread : T1 terminou!\n"); 


  pthread_exit(NULL);
}

/* Thread t2 */
void *t2 (void *t) {
  //printf("T2: Comecei\n");
  sem_wait(&condt2e3);
  printf("Fique a vontade.\n");
  //printf("Thread : T2 terminou!\n");
  sem_post(&condt4);
 

 
  pthread_exit(NULL);
}

/* Thread t3 */
void *t3 (void *t) {
  //printf("T3: Comecei\n");
  sem_wait(&condt2e3);
  printf("Sente-se por favor.\n");
  //printf("Thread : T3 terminou!\n");
  sem_post(&condt4);
  

  pthread_exit(NULL);
}

/* Thread t4 */
void *t4 (void *t) {
  //printf("T4: Comecei\n");

  printf("Seja bem-vindo!\n");
  //printf("Thread : T4 terminou!\n");
  sem_post(&condt2e3);
  
  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {

  pthread_t threads[NTHREADS];

  //inicia os semaforos
  sem_init(&condt2e3, 0, 0);
  sem_init(&condt4, 0, 0);

  /* Cria as threads */
  pthread_create(&threads[2], NULL, t1, NULL);
  pthread_create(&threads[1], NULL, t2, NULL);  
  pthread_create(&threads[3], NULL, t3, NULL);
  pthread_create(&threads[0], NULL, t4, NULL);

  /* Espera todas as threads completarem */
  for (int i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("\nFIM\n");

  /* Desaloca variaveis e termina */
  sem_destroy(&condt2e3);
  sem_destroy(&condt4);
}
