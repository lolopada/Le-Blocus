#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#include <stdbool.h>
#include <unistd.h>

#include "affichage.h"
#include "partie.h"

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

void PlacerElement(int Decale_x, int Decale_y, int Ecart_pixel, int Taille_grille, int Taille_images, int Tour_j, int *prev_case_x, int *prev_case_y, int **Tableau, int Joueur_mur) {
  struct Images_jeux Images_elements[] = {
    {150}, {84}, {65} /* Tailles possibles pour les images des joueurs/murs */
  };

  int img_width = Images_elements[Taille_images - 1].Taille;
  int img_height = Images_elements[Taille_images - 1].Taille;
  char img[500];

  int case_x,case_y;

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

  /* Mettre à jour les nouvelles positions */
  case_x = pos_x(Decale_x, Ecart_pixel);
  case_y = pos_y(Decale_y, Ecart_pixel);

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

    printf("PlacerElement : joueur %d à nouvelle position : case_x = %d, case_y = %d\n", Tour_j, case_x, case_y);
  }
}


void Initalisation_joueurs(int Decale_x, int Decale_y, int Ecart_pixel, int Taille_grille, int **Tableau, int Taille_images, int *Tour_j, int prev_case_x[2], int prev_case_y[2]) {
  bool Init_j1 = false, Init_j2 = false;
  *Tour_j = 1;

  while (!Init_j1) {
    if (SourisCliquee()) {
      int case_x = pos_x(Decale_x, Ecart_pixel);
      int case_y = pos_y(Decale_y, Ecart_pixel);

      if (case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && Tableau[case_y][case_x] == 0) {
	prev_case_x[0] = case_x;
	prev_case_y[0] = case_y;
	PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, *Tour_j, &prev_case_x[0], &prev_case_y[0], Tableau, 1);
	Init_j1 = true;
      }
    }
    /*mettre en pause pendant 0,5 pour eviter de surcharger inutilement le processeur*/
    sleep(0.5);
  }

  *Tour_j = 2;

  while (!Init_j2) {
    if (SourisCliquee()) {
      int case_x = pos_x(Decale_x, Ecart_pixel);
      int case_y = pos_y(Decale_y, Ecart_pixel);

      if (case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && Tableau[case_y][case_x] == 0) {
	prev_case_x[1] = case_x;
	prev_case_y[1] = case_y;
	PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, *Tour_j, &prev_case_x[1], &prev_case_y[1], Tableau, 1);
	Init_j2 = true;
      }
    }
    /*mettre en pause pendant 0,5 pour eviter de surcharger inutilement le processeur*/
    sleep(0.5);
  }
  /*joueur 1 commence a jouer*/
  *Tour_j = 1;
}


bool Peut_bouger(int prev_case_x, int prev_case_y, int **Tableau, int Taille_grille) {
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
	return true;
      }
    }
  }

  /* Si toutes les cases autour sont hors limites ou occupées, le pion ne peut pas bouger */
  return false;
}

bool Deplacement_valide(int x_depart, int y_depart, int x_arrivee, int y_arrivee) {
  int dx = x_arrivee - x_depart;
  int dy = y_arrivee - y_depart;

  /* Vérifie si le déplacement est d'une seule case en diagonale, horizontalement ou verticalement */
  if ((abs(dx) == 1 && dy == 0) ||       /* Déplacement d'une case horizontalement */
      (dx == 0 && abs(dy) == 1) ||       /* Déplacement d'une case verticalement */
      (abs(dx) == 1 && abs(dy) == 1)) {  /* Déplacement d'une case en diagonale */
    return true;
  }
  return false;
}


int Joueur_vs_Joueur(int Decale_x, int Decale_y, int Ecart_pixel, int Taille_grille, int Taille_images, int **Tableau) {
  bool Partie_en_cours = true;
  int Tour_j,Nbr_tours = 0;
    
  int prev_case_x[2] = {-1, -1}; /*Initialiser positions joueurs en dehors */
  int prev_case_y[2] = {-1, -1};
  
  Initalisation_joueurs(Decale_x,Decale_y,Ecart_pixel,Taille_grille,Tableau,Taille_images,&Tour_j,prev_case_x,prev_case_y);
  
  
  while (Partie_en_cours == true) {
    AfficherGrille(Tableau,Taille_grille);
    printf("j%d\n",Tour_j);
    
    if (Peut_bouger(prev_case_x[Tour_j-1],prev_case_y[Tour_j-1],Tableau,Taille_grille)){
      bool Joueur_qui_joue=false;
      int Joueurpuismur=0;
      while(Joueur_qui_joue==false){
	
	if(SourisCliquee()){
	  int case_x = pos_x(Decale_x, Ecart_pixel);
	  int case_y = pos_y(Decale_y, Ecart_pixel);

	  /*on verifie que le clique se situe bien dans la grille, et que la case correspondante est innocupé, puis on place le joueur*/
	  if(case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && Tableau[case_y][case_x] == 0
	     /*on verifie egalement que le joueur se deplace dune case seulement*/
	     && Deplacement_valide(prev_case_x[Tour_j-1], prev_case_y[Tour_j-1], case_x, case_y)==true && Joueurpuismur==0){
	    
	    PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, Tour_j, &prev_case_x[Tour_j-1], &prev_case_y[Tour_j-1], Tableau, 1);
	    AfficherGrille(Tableau,Taille_grille);
	    Joueurpuismur+=1;
	    
	    /*on verifie que le clique se situe bien dans la grille, et que la case correspondante est innocupé, puis on place le mur*/
	  } else if (case_x >= 0 && case_x < Taille_grille && case_y >= 0 && case_y < Taille_grille && Tableau[case_y][case_x] == 0 && Joueurpuismur==1){
	    
	    PlacerElement(Decale_x, Decale_y, Ecart_pixel, Taille_grille, Taille_images, Tour_j,&prev_case_x[Tour_j-1], &prev_case_y[Tour_j-1], Tableau, 2);
	    AfficherGrille(Tableau,Taille_grille);
	    Joueur_qui_joue=true;
	    
	  }
	}
	/*mettre en pause pendant 0,5 pour eviter de surcharger inutilement le processeur*/
	sleep(0.5);
      }
    } else {
      printf("%d a perdu.",Tour_j);
      Partie_en_cours=false;
      
    }
    /* Alterner le tour entre les joueurs */
    Tour_j = (Tour_j == 1) ? 2 : 1;
    
    Nbr_tours+=1;
  }
  return Tour_j;
}

char Partie(int *Background_nb, int Taille_choix){

  /* Paramètres de la grille */
  int Largeur_carre_blanc=600;/*600x600pixel*/
  int Decale_x=100, Decale_y=100;
  int Ecart_pixel;
  
  int Taille_grille, Choix_partie;
  int **Tableau;
  int Taille_images;

  bool Choix_fin_jeu=false;
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
    Joueur_win = Joueur_vs_Joueur(Decale_x,Decale_y,Ecart_pixel,Taille_grille,Taille_images,Tableau);

  /* Libérer la mémoire */
  Liberer_tableau(Tableau, Taille_grille);
  
  Affichage_fin_jeu(Joueur_win);

  while(Choix_fin_jeu==false){
    if (SourisCliquee()) {

      /*code pour le bouton Leave*/
      if (_X >= 294 && _X <= 493 && _Y >= 854 &&  _Y<= 905) {
        printf("Clic sur le bouton Leave\n");
	Choix_fin_jeu=true;
	return 'L';
	
      }
      /*code pour le bouton menu*/
      else if (_X >= 90 && _X <= 289 && _Y >= 754 && _Y <= 805) {
        printf("Clic sur le bouton Menu\n");
	Choix_fin_jeu=true;
	return 'M';
      }
      /*code pour le bouton play again*/
      else if (_X >= 507 && _X <= 706 && _Y >= 754 && _Y <= 805) {
        printf("Clic sur le bouton Play Again\n");
	Choix_fin_jeu=true;
	return 'A';
      }
      /*mettre en pause pendant 0,5 pour eviter de surcharger inutilement le processeur*/
      sleep(0.5);
    }
  }
  /*Valeur par défaut pour quitter si jamais le choix de fin de jeu n'est pas capturé*/
  return 'L';
}
