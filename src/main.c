 /*
  * nome: Anderson Santos Silva
  * RA: 166191
  * Laboratório 4 - EA876
  * Objetivo: implementar um reconhecedor de números primos em que 
  * o reconhecimento de cada número recebido será feito por um processo
  * diferente, podendo haver até 4 processos ao mesmo tempo.
  */

/*inclusão das bibliotecas*/
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
  /*definindo o vetor de pid*/
  pid_t pid[3];
	
	/* c identificará o \n no final da mensagem*/
	/* numeros é o vetor que armazenará cada número recebido*/
  char c = 'c';
  unsigned long long int  numeros[1000];
  int i = 0, k = 0;
	
  /*parâmetros a serem utilizados pela mmp*/
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

  /* *primos e *n_processos são dois endereços de memórias que serão compartilhados por todos os processos, podendo ser modificados em cada um deles*/
  int *primos, *n_processos;
  primos = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  n_processos = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  /*n_processos contará quantos processos estão funcionando atualmente para que não excedão o número 4*/
  (*n_processos) = 0;
  /*primos registrará quantos primos forma encontrados.*/
  (*primos)=0;
	
	/*while que faz a leitura das entradas*/
  while(c!='\n'){
    scanf("%lld", &numeros[i]);
    scanf("%c", &c);
    i++;
  }
  /*i armazena a quantidade de números que recebemos e k quantos numeros avaliamos*/
	while(k<i){
   /*caso tenhamos um número de 3 processos filhos, aguardamos nesse if até que todos sejam fechados.*/
   if((*n_processos)==3){
      //printf("aguardando processos serem encerrados\n");     
      for(int w=k-3;w<k;w++){
        waitpid(pid[w], NULL, 0);/*estamos aguardando que no w pids que ainda estão abertos sejam encerrados*/
        (*n_processos)--;
      }
     }else{
        /*caso tenhamos menos 3 processos filhos, iniciamos o próximo para avaliar se o próximo número é primo*/
        pid[k] = fork();
        (*n_processos)++;/*a cada processo iniciado contamos +1*/
       
        /*dentro do processo filho K avaliaremos se o numeros[k] é primo ou não e retornaremos +1 em primos caso seja.*/
        if(pid[k] == 0){
            if(numeros[k]!=2 && numeros[k]!=3 && numeros[k]!=5 && numeros[k]!=7){
              
              if(numeros[k]<=1);
              else if(numeros[k]%2==0);
              else if(numeros[k]%3==0);
              else if(numeros[k]%5==0);
              else if(numeros[k]%7==0);
              else(*primos)++;
           
            }
            else (*primos)++;
          exit(0);/*saindo do processo filho*/
        }
        k+=1;/*contador de números avaliados*/
    }
	}
  
  /*após avaliar todos os números, esperamos que todos os processos sejam encerrados*/
  for(int j = 0; j<i;j++){
    waitpid(pid[j], NULL, 0);
  }
  
  /*printamos os números primos encontrados*/
  printf("%d\n", *primos);

  return 0;
}
