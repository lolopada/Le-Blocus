#include<stdio.h>
#include<stdlib.h>
#include<graph.h>

#include "affichage.h"
#include "partie_parametres.h"

void Initalisation_joueurs(int Decale_x, int Decale_y, int Ecart_pixel, int Taille_grille, int **Tableau, int Taille_images, int *Tour_j, int prev_case_x[2], int prev_case_y[2]) {
  
  int Init_j1 = 0, Init_j2 = 0;
  
  /*le joueur 1 commence a placer son pion*/
  *Tour_j = 1;

  Affichage_tour_joueur(*Tour_j);
  
  while (Init_j1==0) {
    if (SourisCliquee()) {
      int case_x = pos_x(Decale_x, Ecart_pixel);
      int case_y = pos_y(Decale_y, Ecart_pixel);

      if (case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && Tableau[case_y][case_x] == 0) {
	PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, *Tour_j,
		      &prev_case_x[0], &prev_case_y[0],case_x,case_y, Tableau, 1);
	Init_j1 = 1;
      }
    }  }

  *Tour_j = 2;
  Affichage_tour_joueur(*Tour_j);
 
  while (Init_j2==0) {
    if (SourisCliquee()) {
      int case_x = pos_x(Decale_x, Ecart_pixel);
      int case_y = pos_y(Decale_y, Ecart_pixel);

      if (case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && Tableau[case_y][case_x] == 0) {
	PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, *Tour_j,
		      &prev_case_x[1], &prev_case_y[1],case_x,case_y, Tableau, 1);
	Init_j2 = 1;
      }
    }
  }

}

int Joueur_vs_Joueur(int Decale_x, int Decale_y, int Ecart_pixel, int Taille_grille, int Taille_images, int **Tableau) {
  int Partie_en_cours = 1;
  int Tour_j;
    
  int prev_case_x[2] = {-1, -1}; /*Initialiser positions joueurs en dehors */
  int prev_case_y[2] = {-1, -1};
  
  Initalisation_joueurs(Decale_x,Decale_y,Ecart_pixel,Taille_grille,Tableau,Taille_images,&Tour_j,prev_case_x,prev_case_y);

  /*joueur 1 commence a jouer*/
  Tour_j = 1;

  while (Partie_en_cours == 1) {
    /*AfficherGrille(Tableau,Taille_grille);*/
    /*printf("j%d\n",Tour_j);*/
    
    if (Peut_bouger(prev_case_x[Tour_j-1],prev_case_y[Tour_j-1],Tableau,Taille_grille)){
      
      int Joueur_qui_joue=0;
      int Joueurpuismur=0;

      Affichage_tour_joueur(Tour_j);
 
      while(Joueur_qui_joue==0){
	
	if(SourisCliquee()){
	  int case_x = pos_x(Decale_x, Ecart_pixel);
	  int case_y = pos_y(Decale_y, Ecart_pixel);

	  /*on verifie que le clique se situe bien dans la grille, et que la case correspondante est innocupé, puis on place le joueur*/
	  if(case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && Tableau[case_y][case_x] == 0
	     /*on verifie egalement que le joueur se deplace dune case seulement*/
	     && Deplacement_valide(prev_case_x[Tour_j-1], prev_case_y[Tour_j-1], case_x, case_y)==1 && Joueurpuismur==0){
	    
	    PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, Tour_j,
			  &prev_case_x[Tour_j-1], &prev_case_y[Tour_j-1],case_x,case_y, Tableau, 1);
	    /*AfficherGrille(Tableau,Taille_grille);*/
	    Joueurpuismur+=1;
	    
	    /*on verifie que le clique se situe bien dans la grille, et que la case correspondante est innocupé, puis on place le mur*/
	  } else if (case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && Tableau[case_y][case_x] == 0 && Joueurpuismur==1){
	    
	    PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, Tour_j,
			  &prev_case_x[Tour_j-1], &prev_case_y[Tour_j-1],case_x,case_y, Tableau, 2);
	    /*AfficherGrille(Tableau,Taille_grille);*/
	    Joueur_qui_joue=1;
	    
	  }
	}
	/*mettre en pause pendant 0,1 pour eviter de surcharger inutilement le processeur*/
	sleep_for_microseconds(100000);
      }
    } else {
      /*printf("%d a perdu.",Tour_j);*/
      Partie_en_cours=0;
    }
    
    /* Alterner le tour entre les joueurs */
    Tour_j = (Tour_j == 1) ? 2 : 1;
    
  }
  return Tour_j;
}
