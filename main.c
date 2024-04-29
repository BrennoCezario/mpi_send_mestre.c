/* Inclusao de bibliotecas */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/* Definicao de variaveis */
#define MASTER 0

int main(int argc,char *argv[])
{
   int numtasks, rank, source, outmsg=0, tag=1;  
   MPI_Status Stat;  
   FILE * pt_a;

   MPI_Init(&argc,&argv); // inicia prog paralelo
   MPI_Comm_size(MPI_COMM_WORLD, &numtasks); // numtasks = quantidade de processos disparados
   MPI_Comm_rank(MPI_COMM_WORLD, &rank); // rank = identificacao do processo

 
   if (rank == MASTER) {  

   // abrir arquivo de saida
   if ((pt_a = fopen(argv[1], "w")) == NULL) {
       printf("Nao conseguiu abrir arquivo para escrita  \n");
       exit(1);    
   }
   
   // recebe outmsg
   for (int i=0;i<((numtasks-1)*100);i++){
    MPI_Recv(&outmsg, 1, MPI_INTEGER, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Stat);
    //imprime no arquivo	
    fprintf (pt_a, "Rank = %d mensagem = %d \n", Stat.MPI_SOURCE, outmsg);
   }
   }
   
   else{
   // envia outmsg
    for(int i=0; i<100; i++){
    	MPI_Send(&outmsg, 1, MPI_INTEGER, MASTER, tag, MPI_COMM_WORLD);
    	outmsg++;
    }	
   }
   

   MPI_Finalize(); //termina prog paralelo
} 


/*Como executar na linha de comando:
	mpicc -o arqexec arqfonte.c
	mpirun -n 4 ./arqexec arq.dat
*/

