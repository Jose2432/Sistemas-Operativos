#include <stdio.h>
#include <signal.h>

void senal(int siguiente){
  static int cont = 0;
  cont++;
  puts(" <- Senal recibida.");
  if(cont == 3){
    puts("Ya son tres veces, me canse");
    //Matar al padre
    kill(getppid(),SIGKILL);
    exit(0);
  }
}

int main(){
  int proc;
  proc = fork();

  //Por si no se crea el hijo
  if(proc == -1){
    perror("fork:");
    exit(1);
  }

  if(proc == 0){
    //Proceso hijo
    signal(SIGUSR1,senal);
    puts("El proceso hijo esta en espera de senales.");
    while(1){
      pause();
    }
  }else{
    //Proceso padre
    puts("El proceso padre esta enviando senales cada 5 segs.");
    while(1){
      sleep(5);
      puts("Enviando señal.->");
      kill(proc,SIGUSR1);
    }
  }
}
