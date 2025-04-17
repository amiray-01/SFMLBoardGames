CC = g++ -Wall -std=c++11 # Compilateur et options
CCO = $(CC) -c # Commande pour la compilation des fichiers sources
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system # Flags SFML

# Liste des fichiers objets
OBJECTS = main.o \
          BaseControleur.o \
          ControleurSafari.o \
          ControleurButin.o \
          ControleurDames.o \
          Plateau.o \
          Case.o \
          PionModel.o \
          Jeu.o \
          Safari.o \
          Butin.o \
          Dames.o \
          Joueur.o \
          Bouton.o \
          VueGenerale.o \
          VueSafari.o \
          VueButin.o \
          VueDames.o \
          Piece.o

# Nom du fichier exécutable
EXECUTABLE = jeu

all: $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS) $(SFMLFLAGS)

main.o: main.cpp
	$(CCO) main.cpp

BaseControleur.o: Controleur/BaseControleur.cpp Controleur/BaseControleur.hpp
	$(CCO) Controleur/BaseControleur.cpp

ControleurSafari.o: Controleur/ControleurSafari.cpp Controleur/ControleurSafari.hpp
	$(CCO) Controleur/ControleurSafari.cpp

ControleurButin.o: Controleur/ControleurButin.cpp Controleur/ControleurButin.hpp
	$(CCO) Controleur/ControleurButin.cpp

ControleurDames.o: Controleur/ControleurDames.cpp Controleur/ControleurDames.hpp
	$(CCO) Controleur/ControleurDames.cpp

Plateau.o: Modele/Plateau.cpp Modele/Plateau.hpp
	$(CCO) Modele/Plateau.cpp

Case.o: Modele/Case.cpp Modele/Case.hpp
	$(CCO) Modele/Case.cpp

PionModel.o: Vue/PionModel.cpp Vue/PionModel.hpp
	$(CCO) Vue/PionModel.cpp

Jeu.o: Modele/Jeu.cpp Modele/Jeu.hpp
	$(CCO) Modele/Jeu.cpp

Safari.o: Modele/Safari.cpp Modele/Safari.hpp
	$(CCO) Modele/Safari.cpp

Butin.o: Modele/Butin.cpp Modele/Butin.hpp
	$(CCO) Modele/Butin.cpp

Dames.o: Modele/Dames.cpp Modele/Dames.hpp
	$(CCO) Modele/Dames.cpp

Joueur.o: Modele/Joueur.cpp Modele/Joueur.hpp
	$(CCO) Modele/Joueur.cpp

Bouton.o: Vue/Bouton.cpp Vue/Bouton.hpp
	$(CCO) Vue/Bouton.cpp

VueGenerale.o: Vue/VueGenerale.cpp Vue/VueGenerale.hpp
	$(CCO) Vue/VueGenerale.cpp

VueSafari.o: Vue/VueSafari.cpp Vue/VueSafari.hpp
	$(CCO) Vue/VueSafari.cpp

VueButin.o: Vue/VueButin.cpp Vue/VueButin.hpp
	$(CCO) Vue/VueButin.cpp

VueDames.o: Vue/VueDames.cpp Vue/VueDames.hpp
	$(CCO) Vue/VueDames.cpp

Piece.o: Modele/Piece.cpp Modele/Piece.hpp
	$(CCO) Modele/Piece.cpp

clean:
	rm -f *.o $(EXECUTABLE)