#ifndef CONTROLEUR_SAFARI_HPP
#define CONTROLEUR_SAFARI_HPP

#include "BaseControleur.hpp"
#include "../Vue/VueSafari.hpp" 
#include "../Modele/Safari.hpp"
#include <sstream>
#include <string>

class ControleurSafari : public BaseControleur {
public:
    ControleurSafari(sf::RenderWindow& window,int nbJoueurs); 

    void run() override;

    bool premiereSelection(int i, int j); //retourne true si la selection est valide
    bool deuxiemeSelection(int i, int j); //retourne true si le deplacement est valide
    bool removePion(int i, int j); //retourne true si le pion a été supprimé
    bool poserPion(int i, int j); //retourne true si le pion a été posé
    bool placerBarriere (int i,int j); //retourne true si la barriere a été posée
    void handleGame(sf::Event event, sf::RenderWindow& window, VueSafari& vue); //gère la partie
    void handleEndGame(); //gère la fin de partie
    void gestionTourUn(int i,int j); //gère le premier tour

private:
    VueSafari vue;
    Safari model;
    Clock clock;
    int nbPionsPose; //nombre de pions posés lors du premier tour
    int nbCoups; //nombre de coups joués (2 pour chaque joueur à chaque tour)
};

#endif // CONTROLEUR_Safari_HPP
