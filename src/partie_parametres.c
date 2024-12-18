#include<stdio.h>
#include<stdlib.h>
#include<graph.h>

#include "affichage.h"
#include "partie_parametres.h"
#include "Joueur_vs_Joueur.h"
#include "Joueur_vs_Pc.h"

void AfficherGrille(int **Tableau, int Taille_grille) {
  int i, j;

  printf("\nÉtat actuel de la grille :\n");
  for (i = 0; i < Taille_grille; i++) {
    for (j = 0; j < Taille_grille; j++) {
      printf("%d ",Tableau[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int **Creer_tableau(int Taille) {
  int i, j;
  int **Tableau = (int **)malloc(Taille * sizeof(int *));
    
  for (i = 0; i < Taille; i+=1) {
    Tableau[i] = (int *)malloc(Taille * sizeof(int));
  }
    
  for (i = 0; i < Taille; i+=1) {
    for (j = 0; j < Taille; j+=1) {
      Tableau[i][j] = 0;
    }
  }
  return Tableau;
}

void Liberer_tableau(int **Tableau, int Taille) {
  int i;
  for (i=0; i < Taille; i++) {
    free(Tableau[i]);
  }
  free(Tableau);
}

int pos_x(int Decale_x, int Ecart_pixel){
  if (_X < Decale_x) {
    return -1; 
  }
  return (_X - Decale_x) / Ecart_pixel;
}

int pos_y(int Decale_y, int Ecart_pixel){
  if (_Y < Decale_y) {
    return -1; 
  }
  return (_Y - Decale_y) / Ecart_pixel;
}



void sleep_for_microseconds(int microseconds) {
  unsigned long start_time = Microsecondes();
  unsigned long end_time = start_time + microseconds;

  while (Microsecondes() < end_time) {
    /*  Attente active jusqu'à ce que le temps souhaité soit atteint*/
  }
}


void PlacerElement(int Decale_x, int Decale_y, int Ecart_pixel, int Taille_grille, int Taille_images, int Tour_j, int *prev_case_x, int *prev_case_y, int case_x, int case_y, int **Tableau, int Joueur_mur) {
  struct Images_jeux Images_elements[] = {
    {150}, {84}, {65} /* Tailles possibles pour les images des joueurs/murs */
  };

  int img_width = Images_elements[Taille_images - 1].Taille;
  int img_height = Images_elements[Taille_images - 1].Taille;
  char img[500];

  /* Effacer l'ancienne position si elle existe */
  if (*prev_case_x != -1 && *prev_case_y != -1 && Joueur_mur == 1) {
    int old_pos_x = Decale_x + *prev_case_x * Ecart_pixel;
    int old_pos_y = Decale_y + *prev_case_y * Ecart_pixel;

    int erase_img_pos_x = old_pos_x + (Ecart_pixel - img_width) / 2;
    int erase_img_pos_y = old_pos_y + (Ecart_pixel - img_height) / 2;

    sprintf(img, "images/images_jeux/Effacer_v%d.png", Taille_images);
    ChargerImage(img, erase_img_pos_x, erase_img_pos_y, 0, 0, img_width, img_height);

    /* Réinitialiser l'ancienne position dans le tableau */
    Tableau[*prev_case_y][*prev_case_x] = 0;
  }

  /* Vérifier si la nouvelle position est dans les limites */
  if (case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille) {
    int img_pos_x = Decale_x + case_x * Ecart_pixel + (Ecart_pixel - img_width) / 2;
    int img_pos_y = Decale_y + case_y * Ecart_pixel + (Ecart_pixel - img_height) / 2;

    /* Affichage du joueur ou du mur */
    if (Joueur_mur == 1) {
      sprintf(img, "images/images_jeux/Joueur%d_v%d.png", Tour_j, Taille_images);
      Tableau[case_y][case_x] = Tour_j; 
	
      /* Mise à jour des variables pour la position actuelle */
      *prev_case_x = case_x;
      *prev_case_y = case_y;
	    
    } else if (Joueur_mur == 2) {
      sprintf(img, "images/images_jeux/Mur%d_v%d.png", Tour_j, Taille_images);
      Tableau[case_y][case_x] = 3; 
    }

    ChargerImage(img, img_pos_x, img_pos_y, 0, 0, img_width, img_height);
  }
}


int Peut_bouger(int prev_case_x, int prev_case_y, int **Tableau, int Taille_grille) {
  /* Coordonnées des déplacements pour les cases (haut, bas, gauche, droite, et diagonales) */
  int Verif_x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int Verif_y[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int i;

  /* Vérifie s’il existe au moins une case vide autour du pion */
  for (i = 0; i < 8; i++) { /* 8 : nombre de cases à vérifier */
    int new_x = prev_case_x + Verif_x[i];
    int new_y = prev_case_y + Verif_y[i];

    /* Vérifie si la nouvelle position est dans les limites de la grille */
    if (new_x >= 0 && new_x < Taille_grille && new_y >= 0 && new_y < Taille_grille) {
      /* Si la case est vide (non occupée), le pion peut bouger */
      if (Tableau[new_y][new_x] == 0) {
	return 1;
      }
    }
  }

  /* Si toutes les cases autour sont hors limites ou occupées, le pion ne peut pas bouger */
  return 0;
}

int Deplacement_valide(int x_depart, int y_depart, int x_arrivee, int y_arrivee) {
  int dx = x_arrivee - x_depart;
  int dy = y_arrivee - y_depart;

  /* Vérifie si le déplacement est d'une seule case en diagonale, horizontalement ou verticalement */
  if ((abs(dx) == 1 && dy == 0) ||       /* Déplacement d'une case horizontalement */
      (dx == 0 && abs(dy) == 1) ||       /* Déplacement d'une case verticalement */
      (abs(dx) == 1 && abs(dy) == 1)) {  /* Déplacement d'une case en diagonale */
    return 1;
  }
  return 0;
}



char Partie(int *Background_nb, int Taille_choix){

  /* Paramètres de la grille */
  int Largeur_carre_blanc=600;/*600x600pixel*/
  int Decale_x=100, Decale_y=100;
  int Ecart_pixel;
  
  int Taille_grille, Choix_partie;
  int **Tableau;
  int Taille_images;

  int Choix_fin_jeu=0;
  int Joueur_win;

  /* Initialiser les paramètres de la partie */

  Taille_grille=Taille_choix%10;
  Choix_partie=Taille_choix/10;
  Ecart_pixel=Largeur_carre_blanc/Taille_grille;

  /* Afficher le fond et la grille */
  Affichage_fond(Background_nb);
  Affichage_fond_du_jeu(Taille_grille,Decale_x,Decale_y,Ecart_pixel,Largeur_carre_blanc);

  /* Création et initialisation du tableau */
  Tableau = Creer_tableau(Taille_grille); /* création et initialisation du tableau*/


  /*definir la taille des images pour le jeux suivants la taille de la grille*/
  if(Taille_grille<=4)
    Taille_images=1;
  else if (Taille_grille<=7)
    Taille_images=2;
  else
    Taille_images=3;

  /* Démarrer la partie */
  if(Choix_partie==0)
    Joueur_win = Joueur_vs_Joueur(Decale_x,Decale_y,Ecart_pixel,Taille_grille,Taille_images,Tableau);
  else if(Choix_partie==1)
    Joueur_win = Joueur_vs_Pc(Decale_x,Decale_y,Ecart_pixel,Taille_grille,Taille_images,Tableau);

  /* Libérer la mémoire */
  Liberer_tableau(Tableau, Taille_grille);
  
  Affichage_fin_jeu(Joueur_win);

  while(Choix_fin_jeu==0){
    if (SourisCliquee()) {

      /*code pour le bouton Leave*/
      if (_X >= 294 && _X <= 493 && _Y >= 854 &&  _Y<= 905) {
	Choix_fin_jeu=1;
	return 'L';
	
      }
      /*code pour le bouton menu*/
      else if (_X >= 90 && _X <= 289 && _Y >= 754 && _Y <= 805) {
	Choix_fin_jeu=1;
	return 'M';
      }
      /*code pour le bouton play again*/
      else if (_X >= 507 && _X <= 706 && _Y >= 754 && _Y <= 805) {
	Choix_fin_jeu=1;
	return 'A';
      }
    }
  }
  /*Valeur par défaut pour quitter si jamais le choix de fin de jeu n'est pas capturé*/
  return 'L';
}
