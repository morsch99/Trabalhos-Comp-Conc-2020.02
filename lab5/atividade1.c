/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Lab 5 - uso de sincronização por barreira */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Variaveis globais */
int bloqueadas = 0;
int *vetor;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
int tamanhoVetor,salto=1; //numero de threads

void barreira1(int nthreads) {
    if(bloqueadas == (nthreads - salto)){
            bloqueadas = 0; 
            pthread_cond_broadcast(&x_cond);
            
        }else{                    
            pthread_cond_wait(&x_cond, &x_mutex);                       
        }
}

void barreira2(int nthreads) {
    if(bloqueadas == (nthreads - salto)){                        
            bloqueadas = 0;
            salto = salto*2;
            pthread_cond_broadcast(&x_cond);
        }else{            
      	    pthread_cond_wait(&x_cond, &x_mutex);          
        }  
}

//funcao das threads
void *tarefa(void *arg){
    int *id = (int *) arg;
    int aux;

    pthread_mutex_lock(&x_mutex);
    while(*id >= salto){
       
        aux = vetor[(*id)-salto];
        
        bloqueadas++;
        
        barreira1(tamanhoVetor);
        
	vetor[*id] = vetor[*id] + aux;
	
	bloqueadas++;   
	    
	barreira2(tamanhoVetor);
          
    }
    pthread_mutex_unlock(&x_mutex); 

    pthread_exit(NULL);
    
    
}


/* Funcao principal */
int main(int argc, char *argv[]) {
  int potenciaVetor;
 
  if(argc<2) {
      printf("Digite: %s <potencia para criacao do vetor>\n", argv[0]);
      return 1;
   }
  
  potenciaVetor = atoi(argv[1]);
  
  /* Alocando tamanho do vetor */
  tamanhoVetor = pow(2,potenciaVetor);
  vetor = (int *)malloc(tamanhoVetor * sizeof(int));
  
  /* inicializacao do vetor */
  for (int i = 0; i < tamanhoVetor; i++){
  	vetor[i] = i;
  	printf("[%d]", vetor[i]);
  }
  
  int *vetorTeste = (int*) malloc(sizeof(int)*tamanhoVetor);
  /* vetor para o teste */
  for (int i = 0; i < tamanhoVetor; i++){
  	vetorTeste[i] = i;
  }
  
  /* somatorio sequencial */
  for (int i = 0; i < tamanhoVetor; i++){
        vetorTeste[i] = vetorTeste[i] + vetorTeste[i-1];
  }
  
  printf("\n");
  
  pthread_t threads[tamanhoVetor];
  
  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);
  
 
  /* Cria as threads */
      for (int i = 0; i < tamanhoVetor; i++){
        int *id = (int*) malloc(sizeof(int));
        *id = i;
        if(pthread_create(&threads[i], NULL, tarefa, (void*) id)){
            puts("Erro em pthread_create()");
            return -2;
        }
    }

  /* Espera todas as threads completarem */
   for (int i = 0; i < tamanhoVetor; i++){
        pthread_join(threads[i], NULL);
    }
  
  for (int i = 0; i < tamanhoVetor; i++){
       printf("[%d]", vetor[i]);
   }
   
   printf("\n");
   
   for (int i = 0; i < tamanhoVetor; i++){
        if(vetorTeste[i] != vetor[i]){
            printf("Soma está errada.\n");
            return 1;
        }
   }
 printf("Soma está correta.\n");
   
        
  printf ("FIM.\n");

  /* libera a memoria */
  free(vetor);


  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
  
  pthread_exit(NULL);
  return 0;
}/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Lab 5 - uso de sincronização por barreira */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Variaveis globais */
int bloqueadas = 0;
int *vetor;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;
int tamanhoVetor,salto=1; //numero de threads

void barreira1(int nthreads) {
    if(bloqueadas == (nthreads - salto)){
            bloqueadas = 0; 
            pthread_cond_broadcast(&x_cond);
            
        }else{                    
            pthread_cond_wait(&x_cond, &x_mutex);                       
        }
}

void barreira2(int nthreads) {
    if(bloqueadas == (nthreads - salto)){                        
            bloqueadas = 0;
            salto = salto*2;
            pthread_cond_broadcast(&x_cond);
        }else{            
      	    pthread_cond_wait(&x_cond, &x_mutex);          
        }  
}

//funcao das threads
void *tarefa(void *arg){
    int *id = (int *) arg;
    int aux;

    pthread_mutex_lock(&x_mutex);
    while(*id >= salto){
       
        aux = vetor[(*id)-salto];
        
        bloqueadas++;
        
        barreira1(tamanhoVetor);
        
	vetor[*id] = vetor[*id] + aux;
	
	bloqueadas++;   
	    
	barreira2(tamanhoVetor);
          
    }
    pthread_mutex_unlock(&x_mutex); 

    pthread_exit(NULL);
    
    
}


/* Funcao principal */
int main(int argc, char *argv[]) {
  int potenciaVetor;
 
  if(argc<2) {
      printf("Digite: %s <potencia para criacao do vetor>\n", argv[0]);
      return 1;
   }
  
  potenciaVetor = atoi(argv[1]);
  
  /* Alocando tamanho do vetor */
  tamanhoVetor = pow(2,potenciaVetor);
  vetor = (int *)malloc(tamanhoVetor * sizeof(int));
  
  /* inicializacao do vetor */
  for (int i = 0; i < tamanhoVetor; i++){
  	vetor[i] = i;
  	printf("[%d]", vetor[i]);
  }
  
  int *vetorTeste = (int*) malloc(sizeof(int)*tamanhoVetor);
  /* vetor para o teste */
  for (int i = 0; i < tamanhoVetor; i++){
  	vetorTeste[i] = i;
  }
  
  /* somatorio sequencial */
  for (int i = 0; i < tamanhoVetor; i++){
        vetorTeste[i] = vetorTeste[i] + vetorTeste[i-1];
  }
  
  printf("\n");
  
  pthread_t threads[tamanhoVetor];
  
  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);
  
 
  /* Cria as threads */
      for (int i = 0; i < tamanhoVetor; i++){
        int *id = (int*) malloc(sizeof(int));
        *id = i;
        if(pthread_create(&threads[i], NULL, tarefa, (void*) id)){
            puts("Erro em pthread_create()");
            return -2;
        }
    }

  /* Espera todas as threads completarem */
   for (int i = 0; i < tamanhoVetor; i++){
        pthread_join(threads[i], NULL);
    }
  
  for (int i = 0; i < tamanhoVetor; i++){
       printf("[%d]", vetor[i]);
   }
   
   printf("\n");
   
   for (int i = 0; i < tamanhoVetor; i++){
        if(vetorTeste[i] != vetor[i]){
            printf("Soma está errada.\n");
            return 1;
        }
   }
 printf("Soma está correta.\n");
   
        
  printf ("FIM.\n");

  /* libera a memoria */
  free(vetor);


  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
  
  pthread_exit(NULL);
  return 0;
}
