/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 6 */

/* -------------------------------------------------------------------*/

//classe que estende Thread e implementa a tarefa de cada thread do programa 
class T extends Thread {
   private int tid; //id da thread
   private int N; // numero de threads
   private int[] vetor; //vetor

   //construtor
   public T(int tid, int N, int[] vetor) { 
      this.tid = tid; 
      this.N = N;
      this.vetor = vetor;
   }

   //metodo main da thread
   public void run() {
      
      for (int i=tid; i< this.vetor.length; i+= this.N) { //cada threads leem 1 posicao a cada N(Numero de Threads) posicoes.
         this.vetor[i]++; //elemento do vetor soma 1
      }
      
   }
}

//classe da aplicacao
class Atividade5 {

   public static void main (String[] args) {

     
      int elementosVetor = Integer.parseInt(args[0]); //elementos do vetor
      int nthreads = Integer.parseInt(args[1]); //numero de threads
      //reserva espaço para um vetor de threads
      Thread[] threads = new Thread[nthreads];

      if(nthreads > elementosVetor){
         nthreads = elementosVetor;
     }

     int[] vetor = new int[elementosVetor];

     //inicializa o vetor
     for(int i = 0; i < vetor.length; i++){
      vetor[i] = 1;
      System.out.print(vetor[i] + " ");
      }
      System.out.println("\nVETOR PREENCHIDO\n");
      

      //cria as threads da aplicacao
      for (int i=0; i<threads.length; i++) {
         threads[i] = new T(i, nthreads, vetor);
      }

      //inicia as threads
      for (int i=0; i<threads.length; i++) {
         threads[i].start();
      }

      //espera pelo termino de todas as threads
      for (int i=0; i<threads.length; i++) {
         try { threads[i].join(); } catch (InterruptedException e) { return; }
      }
      
      System.out.println("SOMADO 1 AOS ELEMENTOS DOS VETORES :"); 

      for(int i = 0; i < vetor.length; i++){
         System.out.print(vetor[i] + " ");
      }
      System.out.println("\n");
      System.out.println("\nFIM\n"); 
   }
}
