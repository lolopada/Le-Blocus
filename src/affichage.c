#include<stdio.h>
#include<stdlib.h>
#include<graph.h>


void Affichage_fond(int *Background_nb){

  /*Creation des variables pour l affichage du background*/
  char Image_background[500];

  /*affichage de l image du bakcground*/
  sprintf(Image_background,"%s%d.png","images/Backgrounds/background", *Background_nb);
  ChargerImageFond(Image_background);

}

void Affichage_titre(void){
  
  /*Creation des variables pour l affichage de l image du titre*/
  int Taille_image_titre_largeur=800, Taille_image_titre_hauteur=1000;
  int x_titre=0, y_titre=0;
  char Image_titre[500];
  
  /*affichage de l image du titre*/
  sprintf(Image_titre,"%s","images/images_menu/LeBlocus.png");
  ChargerImage(Image_titre, x_titre, y_titre, 0, 0, Taille_image_titre_largeur,Taille_image_titre_hauteur);
}

void Affichage_bouton_menu(void){
  /*Creation des variables pour l affichage de l image des boutons*/
  char Image_bouton_menu[500];
  int x_bouton_menu=0, y_bouton_menu=0;

  /*affichage de l image des boutons*/
  sprintf(Image_bouton_menu,"%s","images/images_menu/Bouton_menu.png");
  ChargerImage(Image_bouton_menu, x_bouton_menu, y_bouton_menu, 0, 0, 800, 1000);
}

void Affichage_credits(void){

  /*Creation des variables pour l affichage de l image du titre*/
  int Taille_image_credits_largeur=800, Taille_image_credits_hauteur=1000;
  int x_credits=0, y_credits=0;
  char Image_credits[500];

  /*affichage de l image du titre*/
  sprintf(Image_credits,"%s","images/images_menu/Credits.png");
  ChargerImage(Image_credits, x_credits, y_credits, 0, 0, Taille_image_credits_largeur,Taille_image_credits_hauteur);
}


void Affichage_choix_grille(void){

  /*Creation des variables pour l affichage de l image du choix de la grille*/
  char Image_choix_grille[500];
  int x_choix_grille_bouton=0, y_choix_grille_bouton=0;
  int Taille_image_choix_grille_largeur=800, Taille_image_choix_grille_hauteur=1000;

    
  /*affichage de l image du choix de la grille*/
  sprintf(Image_choix_grille,"%s","images/images_menu/bouton_choix_grille.png");
  ChargerImage(Image_choix_grille,x_choix_grille_bouton, y_choix_grille_bouton, 0, 0,  Taille_image_choix_grille_largeur,Taille_image_choix_grille_hauteur);
}

void Affichage_settings(void){
  /*Creation des variables pour l affichage de l image des settings*/
  int Taille_image_settings_largeur=800, Taille_image_settings_hauteur=1000;
  int x_settings=0, y_settings=0;
  char Image_settings[500];

  /*affichage de l image des settings*/
  sprintf(Image_settings,"%s","images/images_menu/Settings.png");
  ChargerImage(Image_settings,x_settings, y_settings, 0, 0,  Taille_image_settings_largeur,Taille_image_settings_hauteur);
}

void Affichage_sous_settings(void){
  /*Creation des variables pour l affichage de l image des sous settings*/
  int Taille_image_sous_settings_largeur=800, Taille_image_sous_settings_hauteur=1000;
  int x_sous_settings=0, y_sous_settings=0;
  char Image_sous_settings[500];

  /*affichage de l image des sous settings*/
  sprintf(Image_sous_settings,"%s","images/images_menu/Settings_couleurs.png");
  ChargerImage(Image_sous_settings,x_sous_settings, y_sous_settings, 0, 0,  Taille_image_sous_settings_largeur,Taille_image_sous_settings_hauteur);
}



void Affichage_grille(int Decale_x, int Decale_y,
		      int Largeur_carre_blanc,couleur Noir, int Taille_grille, int Ecart_pixel){
  int i;
  
  ChoisirCouleurDessin(Noir);
  
  for(i=1;i<Taille_grille;i+=1){
    DessinerSegment(Decale_x+Ecart_pixel*i, Decale_y,
		    Decale_x+Ecart_pixel*i, Decale_y+Largeur_carre_blanc);
    
    DessinerSegment(Decale_x,Decale_y+Ecart_pixel*i,
		    Decale_x+Largeur_carre_blanc,Decale_y+Ecart_pixel*i);
  } 
}

void Affichage_fond_grille(int Decale_x, int Decale_y, int Largeur_carre_coin,
			   int Largeur_carre_blanc,int Longueur_sans_coin, couleur Blanc){

  /*Dessiner le fond blanc de l'interface du jeu*/
  ChoisirCouleurDessin(Blanc);
  RemplirRectangle((Decale_x+Largeur_carre_coin/2),Decale_y,
		   Largeur_carre_blanc-Largeur_carre_coin,Largeur_carre_blanc);
  
  RemplirRectangle(Decale_y,(Decale_x+Largeur_carre_coin/2),
		   Largeur_carre_blanc,Largeur_carre_blanc-Largeur_carre_coin);

  RemplirArc(Decale_x,Decale_y,
	     Largeur_carre_coin,Largeur_carre_coin,90,90);/*angle en haut a droite*/
  
  RemplirArc((Decale_x+Longueur_sans_coin),Decale_y,
	     Largeur_carre_coin,Largeur_carre_coin,0,90);/*angle en haut a gauche*/
  
  RemplirArc(Decale_x,(Decale_y+Longueur_sans_coin),
	     Largeur_carre_coin,Largeur_carre_coin,180,90);/*angle en bas a droite*/
  
  RemplirArc((Decale_x+Longueur_sans_coin),(Decale_y+Longueur_sans_coin),
	     Largeur_carre_coin,Largeur_carre_coin,270,90);/*angle en bas a gauche*/
  
}

void Affichage_contour_grille(int Decale_x, int Decale_y, int Largeur_carre_coin,
			      int Largeur_carre_blanc,int Longueur_sans_coin, int epaisseur_contour, couleur Noir){
  
  int idx; /*indice pour dessiner lepaisseur des coins*/
  
  /*Dessiner le contour de la gille*/
  ChoisirCouleurDessin(Noir);

  /*Dessiner chaque coin*/

  
  for(idx=0;idx<=epaisseur_contour;idx+=1 ){
    /*angle en haut a droite*/
    DessinerArc(Decale_x+idx,Decale_y,
		Largeur_carre_coin,Largeur_carre_coin,90,90);
    DessinerArc(Decale_x,Decale_y+idx,
		Largeur_carre_coin,Largeur_carre_coin,90,90);

    /*angle en haut a gauche*/
    DessinerArc((Decale_x+Longueur_sans_coin),Decale_y+idx,
		Largeur_carre_coin,Largeur_carre_coin,0,90);
    DessinerArc((Decale_x+Longueur_sans_coin)-idx,Decale_y,
		Largeur_carre_coin,Largeur_carre_coin,0,90);

    /*angle en bas a droite*/
    DessinerArc(Decale_x,(Decale_y+Longueur_sans_coin)-idx,
		Largeur_carre_coin,Largeur_carre_coin,180,90);
    DessinerArc(Decale_x+idx,(Decale_y+Longueur_sans_coin),
		Largeur_carre_coin,Largeur_carre_coin,180,90);

    /*angle en bas a gauche*/ 
    DessinerArc((Decale_x+Longueur_sans_coin),(Decale_y+Longueur_sans_coin)-idx,
		Largeur_carre_coin,Largeur_carre_coin,270,90);
    DessinerArc((Decale_x+Longueur_sans_coin)-idx,(Decale_y+Longueur_sans_coin),
		Largeur_carre_coin,Largeur_carre_coin,270,90); 
  }

  /*Dessiner les traits lateraux et honrizontaux*/
  RemplirRectangle(Decale_x,(Decale_y+Largeur_carre_coin/2),
		   epaisseur_contour,Longueur_sans_coin);

  RemplirRectangle((Decale_x+Largeur_carre_coin/2),Decale_y,
		   Longueur_sans_coin,epaisseur_contour);
  

  RemplirRectangle((Decale_x-epaisseur_contour+Largeur_carre_blanc),(Decale_y+Largeur_carre_coin/2),
		   epaisseur_contour,Longueur_sans_coin);

  RemplirRectangle((Decale_x+Largeur_carre_coin/2),(Decale_y-epaisseur_contour+Largeur_carre_blanc),
		   Longueur_sans_coin,epaisseur_contour);
}




void Affichage_fond_du_jeu(int Taille_grille, int Decale_x, int Decale_y, int Ecart_pixel, int Largeur_carre_blanc){

  /*600x600*/
  int Largeur_carre_coin=80;
  int Longueur_sans_coin=520;
  int epaisseur_contour=4;
  
  couleur Blanc, Noir;
  Blanc=CouleurParComposante(255,255,255);
  Noir=CouleurParComposante(0,0,0);
  
  Affichage_fond_grille(Decale_x,Decale_y,Largeur_carre_coin,
			Largeur_carre_blanc,Longueur_sans_coin,Blanc);

  Affichage_contour_grille(Decale_x,Decale_y,Largeur_carre_coin,
			   Largeur_carre_blanc,Longueur_sans_coin,epaisseur_contour,Noir);

  Affichage_grille(Decale_x,Decale_y,Largeur_carre_blanc,Noir,Taille_grille,Ecart_pixel);

  ChoisirCouleurDessin(Blanc);
}

void Affichage_tour_joueur(int Tour_j){
  /*Creation des variables pour l affichage du tour du joueur en cours */
  int Taille_tourjoueur_largeur=800, Taille_tourjoueur_hauteur=1000;
  int x_tourjoueur=0, y_tourjoueur=0;
  char Image_tourjoueur[500];

  /*affichage de l image*/
  sprintf(Image_tourjoueur,"%s%d.png","images/images_jeux/Affiche_joueur", Tour_j);
  ChargerImage(Image_tourjoueur,x_tourjoueur, y_tourjoueur, 0, 0,  Taille_tourjoueur_largeur,Taille_tourjoueur_hauteur);
}



void Affichage_fin_jeu(int Tour_j){
  /*Creation des variables pour l affichage de l image de fin de jeu */
  int Taille_fin_largeur=800, Taille_fin_hauteur=1000;
  int x_fin=0, y_fin=0;
  char Image_fin[500];

  /*affichage de l image*/
  sprintf(Image_fin,"%s%d.png","images/images_jeux/Ecran_fin_jeu", Tour_j);
  ChargerImage(Image_fin,x_fin, y_fin, 0, 0,  Taille_fin_largeur,Taille_fin_hauteur);
}
