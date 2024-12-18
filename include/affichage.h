#ifndef AFFICHAGE_H
#define AFFICHAGE_H


void Affichage_fond(int *);

/*fonction d affichage utilisee pour le menu*/
void Affichage_titre(void);
void Affichage_credits(void);
void Affichage_bouton_menu(void);
void Affichage_choix_grille(void);
void Affichage_settings(void);
void Affichage_sous_settings(void);

/*fonction d affichage pour le jeu*/
void Affichage_grille(int,int,int,couleur,int,int);
void Affichage_fond_grille(int,int,int,int,int,couleur);
void Affichage_contour_grille(int,int,int,int,int,int,couleur);
void Affichage_fond_du_jeu(int,int,int,int,int);
void Affichage_tour_joueur(int);
void Affichage_fin_jeu(int);


#endif /* AFFICHAGE_H */
