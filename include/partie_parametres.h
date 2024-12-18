#ifndef PARTIE_H
#define PARTIE_H

struct Images_jeux{
  int Taille;
};

void AfficherGrille(int **Tableau, int Taille_grille);

int pos_x(int,int);
int pos_y(int,int);
void sleep_for_microseconds(int microseconds);

void PlacerElement(int,int,int,int,int,int,int *,int *,int,int,int **,int);
int Peut_bouger(int,int,int **,int);
int Deplacement_valide(int,int,int,int);

char Partie(int *, int);

#endif /* PARTIE_H */
