# Le-Blocus

## Explication du fonctionnement du jeu Blocus

Blocus est un jeu de stratégie pour deux joueurs, basé sur une grille carrée de taille variable.
Le but du jeu est de bloquer l'adversaire en condamnant des cases, jusqu'à ce qu'il ne puisse
plus déplacer son pion. Voici les étapes principales pour comprendre comment le jeu
fonctionne :

1. **Configuration initiale**

    Choix de la taille de la grille : Avant de commencer, les joueurs choisissent une taille pour la grille, entre 3×3 et 9×9. <br>
    Placement des pions : <br>
    - Chaque joueur place son pion sur une case de départ (aucune case ne peut être partagée par deux pions).<br>
    - La sélection des cases se fait à tour de rôle.<br>

2. **Déroulement de la partie**

    La partie se déroule en plusieurs tours alternés entre les deux joueurs :

    <ins>A. Tour d’un joueur </ins><br>
    Déplacement du pion : Le joueur doit déplacer son pion d’une case vers une case
    adjacente libre. <br>
    > Adjacente : Cela inclut les cases directement en haut, en bas, à gauche, à droite, et en
    diagonale. <br>
    <br>
    <ins>B. Condamnation d’une case :</ins><br>
    Après avoir déplacé son pion, le joueur choisit une case libre (autre que celle de son
    propre pion ou du pion adverse) pour la condamner. Une case condamnée est marquée
    et ne peut plus être utilisée pour se déplacer ou être condamnée à nouveau. <br>
    <br>
    <ins>C. Règles importantes :</ins><br>
    - Les joueurs ne peuvent pas passer leur tour. <br>
    - Si un joueur n’a aucune case adjacente libre pour déplacer son pion, il perd la partie.<br>

3. **Fin de la partie** <br>

    La partie se termine lorsque l’un des joueurs ne peut plus déplacer son pion parce qu’il est
    entièrement bloqué par des cases condamnées ou occupées. L’autre joueur est déclaré
    vainqueur. <br>

4. **Modes de jeu** <br>

    Deux joueurs : Les deux joueurs jouent en alternance, chacun contrôlant un pion.
    Un joueur contre l'ordinateur : Le joueur affronte une intelligence artificielle.
    L’ordinateur respecte les mêmes règles que le joueur humain.

## Installation de la bibliotèque graphique 

1. Récupérez l'archive bibliotheque-graphique-main.tar.gz, à la racine du main. Après avoir désarchiver, lancer le script configure pour préparer la compilation et l'installation : <br>

```
./configure --prefix=/usr --disable-exemples
```

`--prefix` permet de choisir le repertoire d'installation. `--enable/--disable-exemples` permet de construire ou non la librairie avec des exemples. (ExempleMandelbrot,ExempleSouris, ExempleGraphique, ExempleSprite). `--enable/--disable-xpm` permet ou non le support des images de format xpm. <br>

Faire `configure --help` pour avoir la liste de toutes les options. <br>

> Important!! La librairie dépend de la librairie X11 qui doit être installée préalablement et optionnellement de la librairie XPM. 

2. Lancez la commande `make` pour la compilation et `make install` pour l'installation.<br>

3. Lancez `make uninstall` pour la désinstallation.


![Ecran d'accueil du jeu](/images/Menublocus.png)            ![Ecran d'accueil du jeu](/images/jeublocus.png) 