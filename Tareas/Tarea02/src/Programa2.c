#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main (void){

  pid_t pidHijo;
  int estado = 0;
  int resultado;

  if((pidHijo = fork()) == -1){
    perror("Error al llamar a fork\n");
    exit(1);
  }else if(pidHijo == 0){
    resultado = getpid() < getppid();
    fprintf(stdout, "Soy el proceso hijo(%ld) y devolveré a mi padre(%ld) el valor %d después de 2 segundos.\n",(long)getpid(),(long)getppid(),resultado);
    sleep(2);
    exit(resultado);
  }else{
    while(pidHijo != wait(&estado));
    fprintf(stdout, "Soy el proceso padre(%ld) y el proceso hijo(%ld) me devolvió %d.\n",(long)getpid(),(long)pidHijo,estado);
  }
  return (0);
}
