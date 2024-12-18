#include<stdio.h>
#include<stdlib.h>
#include<graph.h>


#include "menu.h"
#include "partie_parametres.h"


int main(void) {

  /*parametres globaux de l'interface et du background*/
  int Fenetre_ouverte=1;
  int Taille_largeur=800, Taille_hauteur=1000;
  int Background_nb=0;

  /*utile pour la possibilité "play again"*/
  int Definition=0;

  /*parametres de partie*/
  int Taille_choix=0;
  char Choix_fin_jeu='L';

  /*initialisation de la fenetre graphique et ouverture*/
  InitialiserGraphique();
  CreerFenetre(400,10, Taille_largeur,Taille_hauteur);

  /*boucle principal du programme*/
  while(Fenetre_ouverte==1){

    if(Definition==0)
      /*choix de la taille*/
      Taille_choix=Menu_principal(Taille_largeur, Taille_hauteur, &Background_nb);

    /*defini sur -1 pour empecher de potentiel erreurs quand on veut quitter la fenetre, donc sans avoir défini de taille pour jouer*/
    if(Taille_choix!=-1)
      Choix_fin_jeu = Partie(&Background_nb, Taille_choix);

    /*fin du programme*/
    if(Choix_fin_jeu=='L' || Taille_choix==-1)
      Fenetre_ouverte=0;
    /*on laisse le programme boucler, en mettant sur 1 la variable définition pour directement relancer une partie*/
    else if(Choix_fin_jeu=='A')
      Definition=1;
    /*attribu la valeur 0 a la variable Definition pour retourner au menu et choisir une taille, ou quitter*/
    else if (Choix_fin_jeu=='M')
      Definition=0;
    
  }

  /*fermeture de la fenetre graphique, fin du programme*/
  FermerGraphique();
  return EXIT_SUCCESS;
}
