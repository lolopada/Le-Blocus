#ifndef MENU_H
#define MENU_H

struct BoutonGrille {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    int taille;
};

struct Bouton {
    int x;
    int y;
    int largeur;
    int hauteur;
};



int  Menu_principal(int,int,int *);
int Choix_grille(int *,char,int *);
void Credits(int *,int *);
int Settings(int, int,int *,int *);
int Sous_settings(int, int,int *,int *);


#endif /* MENU_H */
