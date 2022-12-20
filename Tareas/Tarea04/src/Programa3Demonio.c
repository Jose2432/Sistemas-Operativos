#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct msg{
  int pid;
  char texto[50];
};

int main(){
  int pid;
  time_t tiempo;
  FILE *pf; 
  int pipe;
  struct msg mensaje;

  pid = fork();

  if(pid > 0){
    puts ("Fin del Padre.");
    exit(0);
  }

  if(-1 == setsid()){
    perror("setsid()");
    exit(1);
  }
  
  pipe = open("pdemonio.pipe",O_RDWR);
  if(-1 == pipe){
	   perror("open -> pdemonio.pipe");
	   exit(1);
	}

  pf = fopen("demonio.txt","a");
  if(pf == NULL){
	   perror("fopen -> demonio.txt ");
	   exit(2);
	}

  puts("Demonio iniciado.");
  close(0);
  close(1);
  close(2); 

  while(1){
    read(pipe,& mensaje, sizeof(mensaje));
    tiempo = time(NULL);
    fprintf(pf,"PID(%6d) MSG:%-30s FECHA:%s \n",mensaje.pid,mensaje.texto,ctime(&tiempo));
    fflush(pf);
  }
  fclose(pf);
}
