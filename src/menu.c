#include<stdio.h>
#include<stdlib.h>
#include<graph.h>

#include "menu.h"
#include "affichage.h"
#include "partie_parametres.h"

int Menu_principal(int Taille_largeur, int Taille_hauteur, int *Background_nb){
  
  int Choix_en_attente_menu=0;
  int Bouton_back=0;
  
  /*initaliser par un indice/lettre inutiliser, pour éviter les erreurs avec les emplacements mémoires*/
  char Choix_choisi='a'; 
 
  /*defini sur -1 pour empecher de potentiel erreurs dans le main.c quand on quitte sans choisir de taille, car la fonction actuel return la taile*/
  int Taille_choisi=-1; 
  
  Affichage_fond(Background_nb);
  Affichage_titre();
  Affichage_bouton_menu();
  
  while(Choix_en_attente_menu==0){
    
    if (SourisCliquee()){
      if (_X >= 80 && _X <= 315 && _Y >= 456 && _Y <= 508) {
	/* Code pour le bouton J vs J*/
	Choix_choisi = 'J';
	Choix_en_attente_menu = 1;
      }
      else if (_X >= 492 && _X <= 727 && _Y >= 456 && _Y <= 508) {
	/* Code pour le bouton J vs Pc*/
	Choix_choisi = 'P';
	Choix_en_attente_menu = 1;
      }
      else if (_X >= 276 && _X <= 511 && _Y >= 735 && _Y <= 787) {
	/* Code pour le bouton Settings*/
	Choix_choisi = 'S';
	Choix_en_attente_menu = 1;
      }
      else if (_X >= 132 && _X <= 367 && _Y >= 840 && _Y <= 892) {
	/* Code pour le bouton Credits*/
	Choix_choisi = 'C';
	Choix_en_attente_menu = 1;
      }
      else if (_X >= 420 && _X <= 655 && _Y >= 840 && _Y <= 892) {
	/* Code pour le bouton Leave*/
	Choix_choisi = 'L';
	Choix_en_attente_menu = 1;
      }
    }
  }

  if (Choix_choisi=='J' || Choix_choisi=='P')
    Taille_choisi = Choix_grille(Background_nb, Choix_choisi, &Bouton_back);
  
  else if (Choix_choisi=='C')
    Credits(Background_nb, &Bouton_back);
  
  else if(Choix_choisi=='S')
    Settings(Taille_largeur, Taille_hauteur, Background_nb, &Bouton_back);
  
  if (Bouton_back==1)
    return Menu_principal(Taille_largeur, Taille_hauteur, Background_nb);
  
  
  return Taille_choisi;
}


int Choix_grille(int *Background_nb, char Choix_choisi, int *Bouton_back){
  
  int Choix_en_attente_grille=0;
  int Taille_grille_choisi, Diff, i;
  
  struct BoutonGrille boutons[] = {
    {138, 373, 352, 404, 3},
    {413, 648, 352, 404, 4},
    {138, 373, 431, 483, 5},
    {413, 648, 431, 483, 6},
    {138, 373, 510, 562, 7},
    {413, 648, 510, 562, 8},
    {269, 504, 588, 640, 9}
  };
  
  int nombre_boutons = sizeof(boutons) / sizeof(boutons[0]); 

  if (Choix_choisi=='J'){
    Diff=0;
  } else if (Choix_choisi=='P'){
    Diff=10;
  }

  
  Affichage_fond(Background_nb);
  
  Affichage_choix_grille();

  
  while(Choix_en_attente_grille==0){
    if (SourisCliquee()){
      for (i = 0; i < nombre_boutons; i++) {
        if (_X >= boutons[i].x_min && _X <= boutons[i].x_max && _Y >= boutons[i].y_min && _Y <= boutons[i].y_max) {
	  Taille_grille_choisi = boutons[i].taille;
	  Choix_en_attente_grille = 1;
        }
      }
      if (_X >= 282 && _X <= 517 && _Y >= 823 && _Y <= 875) {
	/* Code pour le bouton "back"*/
	Choix_en_attente_grille=1;
	Taille_grille_choisi=9;
	*Bouton_back=1;
      } 
    }
  }
  return Taille_grille_choisi+Diff;
}

void Credits(int *Background_nb, int *Bouton_back){

  int Choix_en_attente_credits=0;
  
  Affichage_fond(Background_nb);
  Affichage_credits();
    
  while(Choix_en_attente_credits==0){
    if (SourisCliquee()){
      if (_X >= 282 && _X <= 517 && _Y >= 823 && _Y <= 875){
	/* Code pour le bouton "back"*/
	Choix_en_attente_credits=1;
	*Bouton_back=1;
      }
    }
  }
}

int  Settings(int Taille_largeur, int Taille_hauteur, int *Background_nb, int *Bouton_back){

  int Choix_en_attente_settings=0;
  
  Affichage_fond(Background_nb);
  Affichage_settings();

  
  
  while(Choix_en_attente_settings==0){

    if (SourisCliquee()){
      if(_X >= 148 && _X <= 148 + 215 && _Y >= 396 && _Y <= 396 + 41){
	*Background_nb=0;
	Choix_en_attente_settings=1;
	return Settings(Taille_largeur, Taille_hauteur, Background_nb, Bouton_back);
      }
      else if(_X >= 410 && _X <= 410 + 215 && _Y >= 396 && _Y <= 396 + 41){
	*Background_nb=1;
	Choix_en_attente_settings=1;
	return Settings(Taille_largeur, Taille_hauteur, Background_nb, Bouton_back);
      }
      else if(_X >= 149 && _X <= 149 + 215 && _Y >= 690 && _Y <= 690 + 41){
	*Background_nb=2;
	Choix_en_attente_settings=1;
	return Settings(Taille_largeur, Taille_hauteur, Background_nb, Bouton_back);
      }
      else if (_X >= 410 && _X <= 410 + 215 && _Y >= 551 && _Y <= 551 + 78){
	Choix_en_attente_settings=1;
	Sous_settings(Taille_largeur, Taille_hauteur, Background_nb, Bouton_back);
	return Settings(Taille_largeur, Taille_hauteur, Background_nb, Bouton_back);
      }
      
      else if(_X >= 282 && _X <= 517 && _Y >= 823 && _Y <= 875){
	/* Code pour le bouton "back"*/
	Choix_en_attente_settings=1;
	*Bouton_back=1;
      }
    }
  }
  return 0;
}

int Sous_settings(int Taille_largeur, int Taille_hauteur, int *Background_nb, int *Bouton_back){

  int Choix_en_attente_sous_settings=0;
  int i;
  
  struct Bouton boutons[] = {
    {148, 237, 213, 40},   /* bg 3 */
    {416, 237, 213, 40},   /* bg 4 */
    {148, 324, 213, 40},   /* bg 5 */
    {416, 324, 213, 40},   /* bg 6 */
    {148, 411, 213, 40},   /* bg 7 */
    {416, 411, 213, 40},   /* bg 8 */
    {148, 498, 213, 40},   /* bg 9 */
    {416, 498, 213, 40},   /* bg 10 */
    {148, 585, 213, 40},   /* bg 11 */
    {416, 585, 213, 40}    /* bg 12 */
  };
  int nombre_boutons = sizeof(boutons) / sizeof(boutons[0]);
  
  Affichage_fond(Background_nb);
  Affichage_sous_settings();

  
  while(Choix_en_attente_sous_settings==0){

    if (SourisCliquee()){
      for (i = 0; i < nombre_boutons; i++) {
	if (_X >= boutons[i].x && _X <= boutons[i].x + boutons[i].largeur &&
	    _Y >= boutons[i].y && _Y <= boutons[i].y + boutons[i].hauteur) {
	  *Background_nb=i+3;
	  Sous_settings(Taille_largeur, Taille_hauteur, Background_nb, Bouton_back);
	}
      }
      if(_X >= 282 && _X <= 517 && _Y >= 823 && _Y <= 875){
	/* Code pour le bouton "back"*/
	Choix_en_attente_sous_settings=1;
      }
    }
  }
  return 0;
}
