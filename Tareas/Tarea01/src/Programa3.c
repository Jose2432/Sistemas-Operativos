#include <stdio.h>
int array[] = {8,9,6,4,6,6,5,10,9,10,7};
int tamano = sizeof array / sizeof array[0];
int *ptr;

int main (){
  int i = 0;
  ptr = &array[0];

  for (i=0; i<tamano; i++){
    printf("ptr+%d = %d\n", i, *(ptr +i));
  }
}
