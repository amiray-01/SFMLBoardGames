#include "Bouton.hpp"

Bouton::Bouton(){ 
    if (!font.loadFromFile("Vue/ressources/police.ttf")) {
        std::cout << "Erreur lors du chargement de la police" << std::endl;
    } 
    initBouton(sizeX, sizeY, posX, posY,""); //initialise le bouton
}

void Bouton::initBouton(float sizeX, float sizeY, int posX, int posY, std::string texte) { //initialise le bouton
    bouton.setSize(Vector2f(sizeX, sizeY)); // Taille du bouton
    bouton.setPosition(posX, posY); // Position du bouton
    bouton.setFillColor(Color::White); // Couleur du bouton

    textBouton.setFont(font); // Police du texte
    textBouton.setString(texte);
    textBouton.setCharacterSize(20);
    textBouton.setFillColor(Color::Black);
    textBouton.setPosition(posX + 20, posY+10); // Position du texte
}



void Bouton::setColorBouton(Color c) {
    bouton.setFillColor(c);
}


