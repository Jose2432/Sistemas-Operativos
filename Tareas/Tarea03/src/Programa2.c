#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX_CLIENTES 25

//declaramos las variables y métodos que utilizaremos
void *cliente (void *num);
void *barbero (void *num);
sem_t sillaEsp;
sem_t sillaBarb;
sem_t duermeBarb;
sem_t cortarCabello;
int atendidos = 0;

int main(int argc, char *argv[]){
  //Variables e hilos para usar en main
  pthread_t btid;
  pthread_t tid [MAX_CLIENTES];
  int i,clientes,sillas;
  int numero [MAX_CLIENTES];
  //Si se ingresan mal los valores en la terminal, imprimirá esto
  if(argc != 3) {
    printf("Usa: Programa2 <clientes> <sillas>\n");
    exit (-1);
  }

  //Le asignamos los valores ingresados en la terminal a las variables de clientes y sillas
  clientes = atoi (argv[1]);
  sillas = atoi (argv[2]);

  //Si se ingresan demasiados clientes, lanzamos un mensaje
  if (clientes > MAX_CLIENTES){
    printf("El número máximo de clientes es %d.\n", MAX_CLIENTES);
    exit (-1);
  }

  //Asignamos el número de los clientes para inicializar el arreglo
  for (i=0; i<MAX_CLIENTES; i++){
    numero[i] = i;
  }

  //Valores iniciales de los semaforos
  sem_init(&sillaEsp,0,sillas);
  sem_init(&sillaBarb,0,1);
  sem_init(&duermeBarb,0,0);
  sem_init(&cortarCabello,0, 0);

  //Hilo del barbero
  pthread_create(&btid,NULL,barbero,NULL);

  //Creamos el hilo de cada cliente
  for (i=0; i<clientes; i++){
    pthread_create(&tid[i],NULL,cliente,(void *)&numero[i]);
  }

  //Al finalizar, unimos los hilos
  for (i=0; i<clientes; i++){
    pthread_join(tid[i],NULL);
  }

  //Cuando terminemos todos los clientes, finalizamos
  atendidos = 1;
  //Hacemos que el barbero cierre la barbería
  sem_post(&duermeBarb);
  pthread_join(btid,NULL);
}

void *cliente (void *numero){
  int num = *(int *)numero;

  //Imprimimos el mensaje cuando un cliente llega
  printf("El cliente %d llegó a la barbería.\n", num+1);

  //Espera para sentarse
  sem_wait (&sillaEsp);
  printf("El cliente %d se sienta en la sala de espera.\n", num+1);

  //Espera a que el barbero se levante de la silla
  sem_wait (&sillaBarb);
  //El cliente deja la silla en la que estaba esperando
  sem_post(&sillaEsp);

  //Imprimimos un mensaje cuando el barbero se despierta
  printf("El cliente %d despierta al barbero.\n", num+1);
  sem_post(&duermeBarb);

  //Espera a que el barbero corte el cabello
  sem_wait (&cortarCabello);
  //El cliente deja la silla del barbero
  sem_post(&sillaBarb);
  printf("El cliente %d se fué.\n", num+1);
  return 0;
}

void *barbero(void *num){
  //Si hay clientes por atender, entonces los atiende
  while(!atendidos){
    printf("El barbero está durmiendo.\n");
    sem_wait (&duermeBarb);
    //Si hay clientes por atender, entonces los atiende
    if (!atendidos){
      printf("El barbero está cortando cabello.\n");

      //El barbero termina de cortar el cabello
      sem_post(&cortarCabello);
      printf("El barbero ya terminó.\n");
    }
  }
  //Imprimimos un mensaje cuando el barbero se vaya
  printf("El barbero salió de la barbería.\n");
  return 0;
}
