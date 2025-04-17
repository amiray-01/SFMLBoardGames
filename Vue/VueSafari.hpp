#ifndef VUESAFARI_HPP
#define VUESAFARI_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "VueGenerale.hpp"
using namespace std;

    const int tailleCase = 71;  // Taille des cases de jeu
    const int tailleBarriere = 5;  // Taille des barrières

class VueSafari : public VueGenerale { //classe qui représente la vue du jeu Safari
    Texture pionNoirTexture; // texture du pion noir
    Texture pionRougeTexture; // texture du pion rouge
    Texture pionJauneTexture; // texture du pion jaune
    Texture pionVideTexture; // texture du pion vide


public:
    VueSafari();
    VueSafari(const VueSafari& autre) = delete;
    VueSafari& operator=(const VueSafari& autre) = delete;
    void initPlateau(); //initialise le plateau
    void initPionsPlateau(Plateau p) override; //initialise les pions du plateau
    void draw(RenderWindow &window) override; //dessine les cases et les pions du plateau
    void setTexturePion(PionModel& pion, CouleurPiece couleur) override; //change la texture du pion
    RectangleShape getBoutonFF(); //retourne le bouton abandonner
    void setColorBoutonFF(Color); //change la couleur du bouton abandonner
    void updatePionsVue(Plateau plateau) override; //met à jour les pions du plateau
};

#endif 