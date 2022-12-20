#include <stdio.h>
#include <pthread.h>
#define N 8
#define M 16

//Declaramos las constantes que utilizaremos
const char *msg[2] = {"Hola Mundo", "Mundo Hola"};
const int cant[2] = {N,M};

void printMsg(void *ptr) {
  int i;
  int id;

  //Asignamos la direccion a nuestra variable
  id = *(int *) ptr;

  //Imprimimos la cantidad de mensajes segun el arreglo que definimos
  for(i=0; i<cant[id]; i++){
    printf("%s\n",msg[id]);
  }
  return;
}

int main(int argc, char *argv[]){
  //Declaramos los hilos y las variables para main
  pthread_t h1,h2;
  int id1=0,id2=1;

  //Creamos los hilos con los mensajes
  pthread_create(&h1,NULL,(void *) &printMsg,(void *) &id1);
  pthread_create(&h2,NULL,(void *) &printMsg,(void *) &id2);

  //Dormimos a los hilos hasta que terminen 
  pthread_join(h1,NULL);
  pthread_join(h2,NULL);

  return 0;
}
