#include <stdio.h>

int array[]={23,76,9,3,7,-12,43,-765,23,76,34};
int tamano = sizeof array / sizeof array[0];
void ordenar (int *x, int y);
int comparar (int *x, int *y);

int main(){
  int i = 0;
  printf("Arreglo sin ordenar.\n");
  for(i=0; i<tamano; i++){
    printf("[%d]",array[i]);
  }
  ordenar(array,tamano);
  printf("\n\nArreglo ordenado.\n");
  for (i=0; i<tamano; i++){
    printf("[%d]",array[i]);
  }
  return 0;
}

void ordenar(int *x, int y){
  int i,j,t;
  for(i=y-1; i>=0; i--){
    for(j=1; j<=i; j++){
      if(comparar(&x[j-1],&x[j])){
        t = x[j-1];
        x[j-1] = x[j];
        x[j] = t;
      }
    }
  }
}

int comparar(int *x,int *y){
  return (*x>*y);
}
