#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void esperar(int,char *,int);

int main(int argc,char *argv[]){

   int pid,ret,ret2=0;
   if(argc != 1){
      fprintf(stderr,"Uso: %s\n\n",argv[0]);
      return 1;
   }

   switch(fork()){
      case -1: perror("programa1:fork");
              return 2;

      case 0: esperar(0,"Primer hijo",0);
   }

    switch(fork()){
      case -1: perror("programa1:fork");
               return 3;

      case 0:
      switch(fork()){
        case -1: perror("programa1:fork");
          return 4;

          case 0: esperar(0,"Primer nieto",0);
      }

      switch(fork()){
        case -1:perror("programa1:fork");
          return 5;

        case 0:
        switch(fork()){
          case -1:perror("programa1:fork");
            return 6;

          case 0: esperar(0,"Bisnieto",0);
        }
        esperar(1,"Segundo nieto",1);
      }
      esperar(2,"Segundo hijo",1);
    }
   esperar(2,"Padre",1);
}


void esperar (int i,char *vinculo,int durmiendo){
   int pid,ret,ret2;
   if(durmiendo){
     sleep(5);
   }

   pid = getpid();
   if(pid == -1){
     perror("programa1:getpid");
     exit(1);
   }

   ret = pid%10;
   for(int j=0;j<i;j++){
      if(wait(&ret2) == -1){
         perror("programa1:wait");
         exit(1);
      }

      if(WIFEXITED(ret2)){
         ret += WEXITSTATUS(ret2);
      }else{
         perror("programa1:WIFEXITED");
         exit(0);
      }
   }
   printf("Soy el %s(PID=%d). Mi suma es: %d \n",vinculo,pid,ret);
   exit(ret);
}
