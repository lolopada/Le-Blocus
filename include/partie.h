#ifndef PARTIE_H
#define PARTIE_H








struct Images_jeux{
  int Taille;
};
int **Creer_tableau(int);
void AfficherGrille(int **Tableau, int Taille_grille);

int pos_x(int,int);
int pos_y(int,int);

void Initialisation_joueur(int, int, int, int, int **, int, int *, int, int);
bool Peut_bouger(int,int,int **,int);
bool Deplacement_valide(int,int,int,int);
int Joueur_vs_Joueur(int,int,int,int,int,int **);

char Partie(int *, int);

#endif /* PARTIE_H */
