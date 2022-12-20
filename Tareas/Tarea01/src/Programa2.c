#include <stdio.h>
#include <stdlib.h>
#define CANTIDAD 3

int main(int argc, char *argv[]){
    int Matriz[CANTIDAD][CANTIDAD];
    int contador,x,y,vx,vy = 0;
    int lim = CANTIDAD*CANTIDAD;
    int limX = CANTIDAD-1;
    int limY = CANTIDAD-1;

    for(x=0; x<CANTIDAD; x++){
      for(y=0; y<CANTIDAD; y++){
        Matriz[x][y] = 0;
      }
    }

    x = CANTIDAD/2;
    y = 0;

    for(contador=1; contador<=lim; contador++){
        Matriz[y][x] = contador;
        vx = x;
        vy = y;
        x++;

        if(x>limX){
          x = 0;
        }

        y--;

        if(y<0){
          y = limY;
        }

        if(Matriz[y][x] > 0){
            x = vx;
            y = vy+1;
        }
    }

    printf("\nCuadrado Mágico\n");
    for(x=0; x<CANTIDAD; x++){
      for(y=0; y<CANTIDAD; y++){
        printf("|%3d|",Matriz[x][y]);
      }
      printf("\n");
    }
    printf("\n");
    return 0;
}
