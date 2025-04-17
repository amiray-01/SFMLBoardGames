#ifndef VUE_GENERALE_HPP
#define VUE_GENERALE_HPP

#include <SFML/Graphics.hpp>
#include <sstream>
#include "PionModel.hpp"
#include "../Modele/Plateau.hpp"
#include "../Modele/Case.hpp"
#include "Bouton.hpp"
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

class VueGenerale { //classe qui représente la vue générale du jeu
protected:
    const int SIZE; //taille du plateau
    const float cellSize; //taille d'une case
    Font font; //police du texte
    RectangleShape scoreboardBackground; //rectangle qui représente le fond du scoreboard
    Text scoreText; //texte qui représente le scoreboard
    vector<vector<PionModel>> Pions; //vecteur de vecteur de pions
    vector<vector<RectangleShape>> cases; //vecteur de vecteur de cases

public:
    VueGenerale(int size, int cellSize);
    virtual ~VueGenerale();

    virtual void draw(sf::RenderWindow &window); //dessine le plateau
    void initPlateau(); //initialise le plateau
    void initScoreboard(); //initialise le scoreboard
    void setScoreboard(string s); //change le texte du scoreboard
    void clearOpacity(vector<pair<int, int>> piecesPrises); //enlève l'opacité des pions
    PionModel& getPion(int x, int y); //retourne le pion
    RectangleShape& getCase(int x, int y); //retourne la case
    void clearCase(int x, int y); //enlève le pion de la case
    CouleurPiece getCouleurPiece(int x, int y,Plateau p); //retourne la couleur du pion
    void updateCase(int x, int y, CouleurPiece couleur); //met à jour la case
    virtual void setTexturePion(PionModel& pion, CouleurPiece couleur) = 0; //change la texture du pion
    virtual void updatePionsVue(Plateau plateau) = 0; //met à jour les pions du plateau
    virtual void initPionsPlateau(Plateau p) = 0; //initialise les pions du plateau
};

#endif 
