#include <stdio.h>

void intercambia(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void seleccionar(int array[], int tamano) {
  for (int i=0; i<tamano-1; i++) {
    for (int j=i+1; j<tamano; j++) {
      if (array[i] > array[j]) {
        intercambia(&array[i], &array[j]);
      }
    }
  }
}

int main(void) {
  int array[] = {23,65,87,234,76,-32,645,-764,-132,32,0,23,65,98};
  int tamano = sizeof array / sizeof array[0];

  printf("Arreglo sin ordenar.\n");
  for (int x=0; x<tamano; x++) {
    printf("[%d]",array[x]);
  }

	seleccionar(array, tamano);
  printf("\n\nArreglo ordenado.\n");
  for (int x=0; x<tamano; x++)
    printf("[%d]",array[x]);
  return 0;
}
