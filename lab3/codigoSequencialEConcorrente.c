//Soma todos os elementos de um vetor de inteiro
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>
#include "timer.h"

long long int nelementos; //dimensao do vetor de entrada
int nthreads; //numero de threads
double *vetor; //vetor de entrada com dimensao dim 
double denominador = 1;

//fluxo das threads
void * tarefa(void * arg) {
   long int id = (long int) arg; //identificador da thread
   double *somaLocal; //variavel local da soma de elementos
   somaLocal = (double*) malloc(sizeof(double));
   if(somaLocal==NULL) {exit(1);}
   long int tamBloco = nelementos/nthreads;  //tamanho do bloco de cada thread 
   long int ini = id * tamBloco; //elemento inicial do bloco da thread
   long int fim; //elemento final(nao processado) do bloco da thread
   if(id == nthreads-1) fim = nelementos;
   else fim = ini + tamBloco; //trata o resto se houver
   //soma os elementos do bloco da thread
   for(long int i=ini; i<fim; i++)
      *somaLocal += vetor[i];
   //retorna o resultado da soma local
   pthread_exit((void *) somaLocal); 
}

//fluxo principal
int main(int argc, char *argv[]) {
   double somaSeq= 0; //soma sequencial
   double somaConc= 0; //soma concorrente
   double ini, fim; //tomada de tempo
   bool sinal = true; //alterarnar sinais
   pthread_t *tid; //identificadores das threads no sistema
   double *retorno; //valor de retorno das threads

   //recebe e valida os parametros de entrada (dimensao do vetor, numero de threads)
   if(argc < 2) {
       fprintf(stderr, "Digite: %s <numero elementos> <numero threads>\n", argv[0]);
       return 1; 
   }
   nelementos = atoll(argv[1]);
   nthreads = atoi(argv[2]);
   //aloca o vetor de entrada
   vetor = (double*) malloc(sizeof(double)*nelementos);
   if(vetor == NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //preenche o vetor de entrada
   for(long int i=0; i<nelementos; i++){
     if(sinal){       
     	vetor[i] = 1/denominador;
     	denominador = denominador + 2;
     	sinal = false;
     	
     }
     else{
     	vetor[i] = -1/denominador;
	denominador = denominador + 2;
	sinal = true;
	}
}	
       
   //soma sequencial dos elementos
   GET_TIME(ini);
   for(long int i=0; i<nelementos; i++)
      somaSeq += vetor[i]; 
   somaSeq = somaSeq *4;	  
   GET_TIME(fim);
   printf("Tempo sequencial:  %.15lf\n", fim-ini);
   double tempoSeq = fim-ini;  

   //soma concorrente dos elementos
   GET_TIME(ini);
   tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
   if(tid==NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //criar as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   //aguardar o termino das threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), (void**) &retorno)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
      //soma global
      somaConc += *retorno;
   }
   somaConc = somaConc*4;
   GET_TIME(fim);
   printf("Tempo concorrente:  %.15lf\n", fim-ini);
   double tempoConc = fim-ini;
   double desempenho = tempoSeq/tempoConc;
   printf("Desempenho Obtido : %.15lf\n", desempenho);
   //exibir os resultados
   printf("SomaSeq : %.15lf\n", somaSeq);
   printf("Soma conc: %.15lf\n", somaConc);
   printf("Math_PI : %.15lf\n", M_PI);
  

   //libera as areas de memoria alocadas
   free(vetor);
   free(tid);

   return 0;
}
