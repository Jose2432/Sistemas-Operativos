#include <stdio.h>
#define MAXAVISOS  10

typedef struct{
  int tiempo;
	int pid;
	int senal;
}

Aviso;
Aviso tabla[MAXAVISOS];

int cargarT(){
  FILE *pf;
  char linea[100];
  int i = 0;
  Aviso a;

  pf = fopen("avisos.conf","r");
  if(pf == NULL){
    perror("avisos.conf");
    return 0;
  }

  while(NULL != fgets(linea,100,pf)){
    if(linea[0] != '#'){
	     sscanf(linea,"%d %d %d", & a.tiempo, & a.pid, & a.senal);
	     if(i < MAXAVISOS){
	        tabla[i] = a;
	        i++;
	     }else{
	        return 0;
	     }
	  }
  }
  fclose(pf);
  return i;
}


int main( int argc, char *argv[]){
  int pid;
  int espera;
  FILE *plog;
  int numavisos;
  int avisoactual;
  int i;

  numavisos = cargarT();

  if(numavisos== 0){
    fprintf(stderr,"Error en el fichero de configuracion.\n");
    exit(1);
  }

  printf(" Avisos = %d \n", numavisos);
  for(i=0; i<numavisos; i++){
    printf(" %5d %5d %5d\n ",tabla[i].tiempo,tabla[i].pid,tabla[i].senal);
  }

  puts("Iniciando demonio.");

  pid = fork();

  if(pid > 0){
    puts ("Fin del Padre");
    exit(0);
  }

  if(-1 == setsid()){
    perror("setsid()");
    exit(1);
  }

  close(1);
  close(2);
  plog = fopen("avisosd.log","w");
  dup(1);
  close(0);

  avisoactual = 0;
  while(avisoactual < numavisos){
    espera = tabla[avisoactual].tiempo;
    sleep(espera);
    printf(" Plan %5d: Señal %6d Proceso %6d \n",avisoactual,tabla[avisoactual].senal,tabla[avisoactual].pid );

    if (-1 == kill( tabla[avisoactual].pid, tabla[avisoactual].senal)){
	     perror("kill");
	  }
    avisoactual++;
  }
  puts(" Fin de planificaciones.");
}
