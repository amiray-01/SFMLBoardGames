#ifndef CONTROLEUR_BUTIN_HPP
#define CONTROLEUR_BUTIN_HPP

#include "BaseControleur.hpp"
#include "../Vue/VueButin.hpp" 
#include "../Modele/Butin.hpp"   
#include <sstream>
#include <string>

class ControleurButin : public BaseControleur {
public:
    ControleurButin(sf::RenderWindow& window,int nbJoueurs);

    void run() override;

    bool premiereSelection(int i, int j); //retourne true si la selection est valide
    bool deuxiemeSelection(int i, int j); //retourne true si le deplacement est valide
    bool removePion(int i, int j); //retourne true si le pion a bien été supprimé
    void handleBoutonPasser(); //gère le bouton passer
    void updateBouton(); //met à jour le bouton
    void handleGame(sf::Event event, sf::RenderWindow& window, VueButin& vue); //gère la partie
    void handleEndGame(); //gère la fin de partie

private:
    VueButin vue; 
    Butin model;
    Clock clock;
};

#endif // CONTROLEUR_BUTIN_HPP
