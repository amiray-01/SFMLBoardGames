#ifndef VUEDAMES_HPP
#define VUEDAMES_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "VueGenerale.hpp"
using namespace std;

class VueDames : public VueGenerale { //classe qui représente la vue du jeu Dames
    Texture pionNoirTexture; // texture du pion noir
    Texture pionRougeTexture; // texture du pion rouge
    Texture pionVideTexture; // texture du pion vide
    Texture pionRougeDameTexture; // texture du pion rouge dame
    Texture pionNoirDameTexture; // texture du pion noir dame
    Bouton boutonFF; // bouton pour abandonner


public:
    VueDames();
    VueDames(const VueDames& autre) = delete;
    VueDames& operator=(const VueDames& autre) = delete;

    void initPionsPlateau(Plateau p) override; //initialise les pions du plateau
    void draw(RenderWindow &window) override; //dessine les pions du plateau
    void setTexturePion(PionModel& pion, CouleurPiece couleur) override; //change la texture du pion
    RectangleShape getBoutonFF(); //retourne le bouton abandonner
    void setColorBoutonFF(Color); //change la couleur du bouton abandonner
    void updatePionsVue(Plateau plateau) override; //met à jour les pions du plateau
    void setTextureDame(PionModel& pion, CouleurPiece couleur); //change la texture de la dame
};

#endif 