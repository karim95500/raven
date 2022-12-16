#include <stdlib.h>
#include <stdio.h>
#include "labyrinthAPI.h"




int main (){
  int sizeX;
  int sizeY;
  int etat= 4545 ;
  char game[50];
  int tileS,tileN,tileItem,tileW,tileE;


  

    connectToServer("172.105.76.204",1234,"karim");
    waitForLabyrinth( "TRAINING RANDOM", game, &sizeX, &sizeY );
    int *lab =malloc(sizeX*sizeY*sizeof(int)*5) ;
    etat = getLabyrinth(lab, &tileN,&tileE, &tileS, &tileW, &tileItem);
    printf("%d",etat);
    closeConnection();
 



        return EXIT_SUCCESS;
}
