#ifndef BASE_CONTROLEUR_HPP
#define BASE_CONTROLEUR_HPP

#include <SFML/Graphics.hpp>
#include "../Modele/Jeu.hpp"
#include "../Vue/VueGenerale.hpp"

using namespace sf;
using namespace std;

class BaseControleur { // classe abstraite
private: 
    VueGenerale& vue; // référence vers la vue
    Jeu& model; // référence vers le modèle
protected:
    RenderWindow& window; // référence vers la fenêtre
    bool isSelected; // booléen qui indique si un pion est sélectionné
    bool boutonActive; // booléen qui indique si le bouton est actif
    CouleurPiece couleur; // couleur de la piece selectionnée
    int nbSauts; // nombre de sauts effectués
    int pionSelectionneX, pionSelectionneY; // coordonnées du pion sélectionné
    int tour; // numéro du tour
    int nbJoueurs; // nombre de joueurs
    bool endgame; // booléen qui indique si la partie est terminée
    int lastPlayer; // dernier joueur à avoir joué
    int hasPlayed; // nombre de joueurs ayant joué
    Clock clock; // gestion du bouton avec un clock (pour le rafraichissement lors du clic)

    void premiereSelection(int i,int j); // gère la première sélection d'un pion
    void prise(int i,int j, int xMilieu, int yMilieu); // gère la prise d'un pion
    void reset(int i, int j); // réinitialise toutes les variables lorsqu'un pion est désélectionné
    void updateScoreboard(); // met à jour le scoreboard
    void handleTour(); // gère le tour

public:

    BaseControleur(RenderWindow& window, VueGenerale& vue, Jeu& jeu,int nb);
    virtual void run() = 0;
};

#endif // BASE_CONTROLEUR_HPP
