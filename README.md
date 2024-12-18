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

![Ecran d'accueil du jeu](/images/Menublocus.png)            ![Ecran d'accueil du jeu](/images/jeublocus.png) 