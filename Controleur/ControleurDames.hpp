#ifndef CONTROLEUR_DAMES_HPP
#define CONTROLEUR_DAMES_HPP

#include "BaseControleur.hpp"
#include "../Vue/VueDames.hpp" 
#include "../Modele/Dames.hpp"   
#include <sstream>
#include <string>

class ControleurDames : public BaseControleur {
public:
    ControleurDames(sf::RenderWindow& window,int nbJoueurs); 

    void run() override;

    bool premiereSelection(int i, int j); //retourne true si la selection est valide
    bool deuxiemeSelection(int i, int j); //retourne true si le deplacement est valide
    void updateBouton(); //met à jour le bouton
    void handleGame(sf::Event event, sf::RenderWindow& window, VueDames& vue); //gère la partie
    void handleEndGame(); //gère la fin de partie
    void resetChemin(); //réinitialise le chemin choisi
    void handleBoutonFF(); //gère le bouton d'abandon

private:
    VueDames vue;
    Dames model;
    vector<vector<pair<int,int>>> cheminsOptimaux; //chemins optimaux pour chaque pion
    vector<pair<int,int>> prises; //prises possibles pour chaque pion
    int cheminChoisi = -1; //chemin choisi par le joueur
};

#endif // CONTROLEUR_BUTIN_HPP
