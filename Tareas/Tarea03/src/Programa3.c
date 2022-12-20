#include <stdio.h>
#include <pthread.h>
#include<semaphore.h>

//Semaforo vacio y lleno
sem_t vacio,lleno;

//Variable mutex para las funciones
pthread_mutex_t mutex;

//Cuenta el número de productos
int contBuf=0;

void *productor(void *arg);
void *consumidor(void *arg);

int main(int argc,char *argv[]){
  pthread_t hiloProductor,hiloConsumidor;

  //Inicializamos las variables
  pthread_mutex_init(&mutex,NULL);
  sem_init(&vacio,0,5);
  sem_init(&lleno,0,0);

  //Creamos los hilos del productor
  if(pthread_create(&hiloProductor,NULL,productor,NULL) != 0){
    printf("Creación de hilo fallida.");
  }

  //Creamos los hilos del consumidor
  if(pthread_create(&hiloConsumidor,NULL,consumidor,NULL) != 0){
    printf("Creación de hilo fallida.");
  }

  //Esperamos al final del hilo
  if(pthread_join(hiloProductor,NULL) != 0){
      printf("Espera de hilo fallida.");
  }

  //Esperamos al final del hilo
  if(pthread_join(hiloConsumidor,NULL) != 0){
      printf("Espera de hilo fallida.");
  }

  //Destruimos los semaforos lleno y vacio y cerramos el mutex
  sem_destroy(&lleno);
  sem_destroy(&vacio);
  pthread_mutex_destroy(&mutex);
  return 0;
}

void *productor(void *arg){
  while(1){
    sem_wait(&vacio);

    //Bloqueamos mutex
    pthread_mutex_lock(&mutex);

    //Entonces se ocupa el mutex y podemos agregar productos al búfer
    printf("El productor puso un producto en el búfer. ");
    contBuf++;
    printf("El contador del búfer es %d.\n",contBuf) ;

    //Desbloqueamos mutex y aumentamos en 1 la variable lleno
    pthread_mutex_unlock(&mutex);
    sem_post(&lleno);
  }
}

void *consumidor(void *arg){
  while(1){
    sem_wait(&lleno);

    //Bloqueamos mutex
    pthread_mutex_lock(&mutex);

    //Entonces se ocupa el mutex y podemos tomar productos al búfer
    printf("El consumidor tomó un producto del búfer. ");
    contBuf--;
    printf("El contador del búfer es %d.\n",contBuf) ;

    //Desbloqueamos mutex y decrementamos en 1 la variable vacio
    pthread_mutex_unlock(&mutex);
    sem_post(&vacio);
  }
}
