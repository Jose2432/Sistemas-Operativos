#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc,char *argv[]){

  if (argc != 2) {
    printf("Parámetros incorrectos. Uso: %s [int]\n",argv[0]);
    exit(EXIT_FAILURE);
  }
  
  int valor = atoi(argv[1]);
  printf("El tamaño del valor %s es: %d\n",argv[1],strlen(argv[1]));
  for (int i=0; i<strlen(argv[1]); i++) {
    char c = argv[1][i];
    if (isdigit(c) == 0) {
      perror("No se puede insertar, debe ser un número.\n");
      exit(EXIT_FAILURE);
    }
  }

  int dev = fork();
  if (dev == -1) {
    perror("Fallo al fork().");
    exit(EXIT_FAILURE);
  }else if (dev > 0 ) {
    valor += 2;
    printf("El valor del padre es: %d\n",valor);
    wait(NULL);
  }else if (dev == 0) {
    valor -= 4;
    printf("El valor del hijo es: %d\n",valor);
    exit(EXIT_SUCCESS);
  }
}
