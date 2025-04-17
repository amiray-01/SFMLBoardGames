#ifndef VUEBUTIN_HPP
#define VUEBUTIN_HPP

#include "VueGenerale.hpp"
using namespace std;

class VueButin : public VueGenerale { //classe qui représente la vue du jeu Butin
    Texture pionNoirTexture; //texture du pion noir
    Texture pionRougeTexture; //texture du pion rouge
    Texture pionJauneTexture; //texture du pion jaune
    Texture pionBlancTexture; 
    Bouton boutonPasser; //bouton pour passer son tour


public:
    VueButin();
    VueButin(const VueButin& autre) = delete;
    VueButin& operator=(const VueButin& autre) = delete;

    void initPionsPlateau(Plateau p) override; //initialise les pions du plateau
    void draw(RenderWindow &window) override; //dessine les pions du plateau
    void setTexturePion(PionModel& pion, CouleurPiece couleur) override; //change la texture du pion
    RectangleShape getBoutonPasser(); //retourne le bouton passer
    void setColorBoutonPasser(Color); //change la couleur du bouton passer
    void updatePionsVue(Plateau plateau) override; //met à jour les pions du plateau
}; 

#endif 