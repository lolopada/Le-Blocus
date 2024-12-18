#include<stdio.h>
#include<stdlib.h>
#include<graph.h>

#include "affichage.h"
#include "partie_parametres.h"
#include "Joueur_vs_Pc.h"


void Initalisation_joueur_pc(int Decale_x, int Decale_y, int Ecart_pixel, int Taille_grille, int **Tableau, int Taille_images, int *Tour_j, int prev_case_x[2], int prev_case_y[2]) {
  
  int Init_j1 = 0, Init_j2 = 0;
  
  *Tour_j = 1;
  Affichage_tour_joueur(*Tour_j);
  
  while (Init_j1==0) {
    if (SourisCliquee()) {
      int case_x = pos_x(Decale_x, Ecart_pixel);
      int case_y = pos_y(Decale_y, Ecart_pixel);
      
      if (case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && Tableau[case_y][case_x] == 0) {
	PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, *Tour_j, &prev_case_x[0], &prev_case_y[0], case_x, case_y, Tableau, 1);
	Init_j1 = 1;
      }
    }
  }

  *Tour_j = 2;
  Affichage_tour_joueur(*Tour_j);
  
  /*mettre une pause pour bien marquer le temps où le bot joue*/
  sleep_for_microseconds(500000);
    
  while (Init_j2==0) {
    
    int case_x = rand()%Taille_grille;
    int case_y = rand()%Taille_grille;
    
    
    if (case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && Tableau[case_y][case_x] == 0) {
      PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, *Tour_j, &prev_case_x[1], &prev_case_y[1], case_x, case_y, Tableau, 1);
      Init_j2 = 1;
    }
  }
  
  /*joueur 1 commence a jouer*/
  *Tour_j = 1;
}

int Joueur_vs_Pc(int Decale_x, int Decale_y, int Ecart_pixel, int Taille_grille, int Taille_images, int **Tableau) {
  int Partie_en_cours = 1;
  int Tour_j;
    
  int prev_case_x[2] = {-1, -1}; /*Initialiser positions joueurs en dehors */
  int prev_case_y[2] = {-1, -1};

  
  Initalisation_joueur_pc(Decale_x,Decale_y,Ecart_pixel,Taille_grille,Tableau,Taille_images,&Tour_j,prev_case_x,prev_case_y);
  Affichage_tour_joueur(Tour_j);
  
 
  while (Partie_en_cours == 1) {
    /*debug*/
    /*AfficherGrille(Tableau, Taille_grille);*/
    /*printf("j%d\n", Tour_j);*/

    if (Peut_bouger(prev_case_x[Tour_j-1], prev_case_y[Tour_j-1], Tableau, Taille_grille)) {
      int Joueur_qui_joue = 0;
      int Joueurpuismur = 0;

      Affichage_tour_joueur(Tour_j);

      if (Tour_j == 1) {  /* Tour du joueur humain*/
	while (Joueur_qui_joue == 0) {
	  if (SourisCliquee()) {
	    int case_x = pos_x(Decale_x, Ecart_pixel);
	    int case_y = pos_y(Decale_y, Ecart_pixel);

	    if (case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && 
		Tableau[case_y][case_x] == 0 &&
		Deplacement_valide(prev_case_x[Tour_j-1], prev_case_y[Tour_j-1], case_x, case_y) && Joueurpuismur == 0) {

	      PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, Tour_j,
			    &prev_case_x[Tour_j-1], &prev_case_y[Tour_j-1], case_x, case_y, Tableau, 1);
	      /*AfficherGrille(Tableau, Taille_grille);*/
	      Joueurpuismur += 1;

	    } else if (case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && 
		       Tableau[case_y][case_x] == 0 && Joueurpuismur == 1) {

	      PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, Tour_j,
			    &prev_case_x[Tour_j-1], &prev_case_y[Tour_j-1], case_x, case_y, Tableau, 2);
	      /*AfficherGrille(Tableau, Taille_grille);*/
	      Joueur_qui_joue = 1;
	    }
	  }
	  
	  sleep_for_microseconds(100000);
	}
      } else {  /* Tour du bot*/
	/* Génération aléatoire jusqu'à trouver une case valide*/
	int case_x, case_y;
	do {
	  case_x = prev_case_x[1] + (Microsecondes() % 3 - 1);  /* Mouvement autour de la position actuelle*/
	  case_y = prev_case_y[1] + (Microsecondes() % 3 - 1);
	} while (!(case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille &&
		   Tableau[case_y][case_x] == 0 &&
		   Deplacement_valide(prev_case_x[1], prev_case_y[1], case_x, case_y)));

	PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, Tour_j,
		      &prev_case_x[1], &prev_case_y[1], case_x, case_y, Tableau, 1);
	/*AfficherGrille(Tableau, Taille_grille);*/

	/* Pause pour visualiser le tour du bot*/
	sleep_for_microseconds(300000);
	
	/* Placer un mur autour de la position du bot*/
	do {
	  case_x = prev_case_x[1] + (Microsecondes() % 3 - 1);
	  case_y = prev_case_y[1] + (Microsecondes() % 3 - 1);
	} while (!(case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille &&
		   Tableau[case_y][case_x] == 0));

	PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, Tour_j,
		      &prev_case_x[1], &prev_case_y[1], case_x, case_y, Tableau, 2);
	Joueur_qui_joue = 1;
      }
    } else {
      /*printf("%d a perdu.", Tour_j);*/
      Partie_en_cours = 0;
    }
    
    /* Alterner le tour entre les joueurs*/
    Tour_j = (Tour_j == 1) ? 2 : 1;
  }

  
  return Tour_j;
}
