#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


struct msg{
  int pid;
  char texto[50];
};

int main(){
  int pid;
  int pipe; // Pipe con nombre
  struct msg mensaje;

  // Abro la pipe de escritura sin bloquearme si el proceso demonio
  // no está activo
  pipe = open("pdemonio.pipe",O_WRONLY | O_NONBLOCK);
  if(-1 == pipe){
	   perror("open -> pdemonio.pipe");
	   exit(1);
	}

  printf("Ingresa el texto a enviar:");
  fgets(mensaje.texto,50,stdin);
  mensaje.pid = getpid();
  write(pipe,&mensaje,sizeof(mensaje));
  puts("Mensaje enviado.");
  close(pipe);
}
