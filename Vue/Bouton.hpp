#ifndef BOUTON_HPP
#define BOUTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Bouton { //classe qui représente un bouton
public:
    RectangleShape bouton; //rectangle qui représente le bouton
    Text textBouton; //texte du bouton
    Font font; //police du texte
    Clock clock; //clock pour le rafraichissement lors du clic
    float sizeX; //taille du bouton
    float sizeY; 
    int posX; //position du bouton
    int posY;


    Bouton();
    ~Bouton() = default;
    Bouton(const Bouton& autre) = default;

    void initBouton(float sizeX, float sizeY, int posX, int posY, std::string texte); //initialise le bouton
    void setColorBouton(Color c); //change la couleur du bouton

};

#endif // BOUTON_HPP
