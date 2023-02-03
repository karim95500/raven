#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>
#include "labyrinthAPI.h"

/*Structure player*/
typedef struct
{
 
  int posx;
  int posy;
  int nbritem;
  
} t_player;


/*Structure tuile*/
typedef struct
{
 
  int N,E,W,S;
  int nbritem;
  
} t_tuile;

void initplay( t_player* kar,t_move* move){
 
    kar->posx = move->x;
    kar->posy = move->y;
    kar->nbritem = move->nextItem;
}


/*fonction jouer mise à jour des information du joueur
*paramètres:
*structure t move correspondant aux informations du joueur*/

void jouer(t_move *move){
	int val;	
printf("A moi de jouer ! Type d'insertion haut : ");
scanf("%d",&val);
move->insert =val;
printf("Le numéro de la ligne/ou de la colonne : ");
scanf("%d",&move->number);
printf("La rotation (de 0 à 3) : ");
scanf("%d",&move->rotation);
printf("Déplacement -> coordonée en x : ");
scanf("%d",&move->x);
printf("Déplacement -> coordonée en y : ");
scanf("%d",&move->y);
}



/*fonction coutauto: Début d'une fonction qui réalise un cout automatique
*paramètres:
t_move correspondant au coordonnée du joueur a déplacé */
int coutauto(t_move * move){

int val=0;	
move->insert =val+1;
val++;
if (val==3) val=0;
move->insert =0;
move->rotation =0;
move->x=val;
move->y=val;
}





/*fonction expaaansion: recherche des chemins allan d' une case d' une départ à une case d' arrivée (phase d' expansion)
*paramètres:
*position de départ(x_depart et y_depart)
*position d' arrivée(x_arrivée et y_arrivée)
*tableau de t_tuile(tableau de tuile))

*dimensions du tableau (sizeX-sizeY) */



int expaaansion(int y, int x, t_tuile test[y][x], int depart[2], int arrivee[2], int cpt) {
  if (test[arrivee[0]][arrivee[1]].nbritem != 0) {
    return cpt;
  }

  int fin = 0;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      if (i == depart[0] && j == depart[1]) {
        continue;
      }

      if (i == 0 && test[i-1][j].nbritem == cpt && test[i][j].nbritem == 0 && test[i-1][j].S== 0 && test[i][j].N == 0) {
        test[i][j].nbritem = cpt + 1;
        fin = 1;
      }
      if (j == 0 && test[i][j-1].nbritem == cpt && test[i][j].nbritem == 0 && test[i][j-1].E == 0 && test[i][j].W == 0) {
        test[i][j].nbritem = cpt + 1;
        fin = 1;
      }
      if (j == y-1 && test[i][j+1].nbritem == cpt && test[i][j].nbritem == 0 && test[i][j+1].W == 0 && test[i][j].E == 0) {
        test[i][j].nbritem = cpt + 1;
        fin = 1;
      }
      if (i == x-1 && test[i+1][j].nbritem == cpt && test[i][j].nbritem == 0 && test[i+1][j].N == 0 && test[i][j].S == 0) {
        test[i][j].nbritem = cpt+ 1;
        fin = 1;
      }
    }
  }

  if (fin==1) {
      return 1;
  } 
   return 0;
}










int main (){


/*Déclaration et inialisation des variables*/
  int labplay[14][55];
  int sizeX;
  int sizeY;
  int etat= 4545 ;
  int play = 1414;
  char game[50];
  int tileS,tileN,tileItem,tileW,tileE;
  int depart[2];
  int cpt =0;
  
  
/*Déclaration  des structures*/
   t_move move1;
   t_move move2;
   t_player player1;
   t_player player2;
   
   
   connectToServer("172.105.76.204",1234,"kar2");
   waitForLabyrinth( "TRAINING BASIC timeout=1000 start=0 display=debug", game, &sizeX, &sizeY );
   
   /*Récupération du tableau*/
   int *lab =malloc(sizeX*sizeY*sizeof(int)*5) ;
   
   etat = getLabyrinth(lab, &tileN,&tileE, &tileS, &tileW, &tileItem);
   printf("%d",etat);
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY * 5; j++) {
        labplay[i][j]=lab[j] ;              
      }
    }
    
    
    
    /*Déclaration d'un tableau de tuile*/  
    t_tuile test[sizeY][sizeX];
    
  
    /*Boucle de jeu*/
    while(play!=1){
    
    
        
    printLabyrinth() ;        
    jouer(&move1);   
    initplay(&player1,&move1);      
    sendMove(&move1);
    getMove(&move2); 
    /*initialisation des  structures de jeu*/
    initplay(&player2,&move2);
      
    /*affichage du labyrinth*/     
    printLabyrinth() ;
    
    depart[0]=player1.posx;
    depart[1]=player1.posx;
              
     /*Création d'u tableau ligne-colonne*/
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY * 5; j++) {
        labplay[i][j]=lab[j] ;              
      }
    }
    

    
    /*transformer notre tableau en tuile*/
   for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY ; j=j+5) {
        
        
        test[j][i].N = lab[i*5];
        test[j][i].E =lab[i*5 +1 ];   
        test[j][i].S = lab[i*5 +2 ]; 
        test[j][i].W =lab[i*5 +3]; 
        test[j][i].nbritem = lab[i*5 +4 ];
                                       
      }
    
    }
    
   
     /*Recherche d'un chemin vers trésor*/
    cpt =expaaansion(sizeY, sizeX,test,depart[2],depart[2],cpt);
    printf("HELLO %d",cpt);
    
    }
     
        closeConnection();
        return EXIT_SUCCESS;
}


