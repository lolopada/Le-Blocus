# Cible 
but : blocus clean

# VARIABLES
CFLAGS = -Wall -Wextra -ansi -pedantic -g
SRC_DIR = src
INCLUDE_DIR = include
OFILES = $(SRC_DIR)/main.o $(SRC_DIR)/menu.o $(SRC_DIR)/affichage.o $(SRC_DIR)/partie_parametres.o $(SRC_DIR)/Joueur_vs_Joueur.o $(SRC_DIR)/Joueur_vs_Pc.o

# DÉPENDANCES 
$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/menu.h $(INCLUDE_DIR)/partie_parametres.h
	gcc $(CFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/menu.o: $(SRC_DIR)/menu.c $(INCLUDE_DIR)/menu.h $(INCLUDE_DIR)/affichage.h $(INCLUDE_DIR)/partie_parametres.h 
	gcc $(CFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/menu.c -o $(SRC_DIR)/menu.o

$(SRC_DIR)/affichage.o: $(SRC_DIR)/affichage.c $(INCLUDE_DIR)/affichage.h 
	gcc $(CFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/affichage.c -o $(SRC_DIR)/affichage.o

$(SRC_DIR)/partie_parametres.o: $(SRC_DIR)/partie_parametres.c $(INCLUDE_DIR)/partie_parametres.h $(INCLUDE_DIR)/affichage.h $(INCLUDE_DIR)/Joueur_vs_Joueur.h $(INCLUDE_DIR)/Joueur_vs_Pc.h
	gcc $(CFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/partie_parametres.c -o $(SRC_DIR)/partie_parametres.o

$(SRC_DIR)/Joueur_vs_Joueur.o: $(SRC_DIR)/Joueur_vs_Joueur.c $(INCLUDE_DIR)/partie_parametres.h $(INCLUDE_DIR)/affichage.h $(INCLUDE_DIR)/Joueur_vs_Joueur.h
	gcc $(CFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/Joueur_vs_Joueur.c -o $(SRC_DIR)/Joueur_vs_Joueur.o

$(SRC_DIR)/Joueur_vs_Pc.o: $(SRC_DIR)/Joueur_vs_Pc.c $(INCLUDE_DIR)/partie_parametres.h $(INCLUDE_DIR)/affichage.h $(INCLUDE_DIR)/Joueur_vs_Pc.h
	gcc $(CFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/Joueur_vs_Pc.c -o $(SRC_DIR)/Joueur_vs_Pc.o

blocus: $(OFILES)
	gcc -o blocus $(OFILES) -lgraph

run:
	./blocus

clean:
	-rm -f $(OFILES) 

# BUTS FACTICES
.PHONY: but clean
