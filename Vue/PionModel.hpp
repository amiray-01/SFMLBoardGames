#ifndef PIONMODEL_HPP
#define PIONMODEL_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

 
class PionModel { //classe qui représente un pion
public:
    RectangleShape shape; //rectangle qui représente le pion
    Sprite sprite; //sprite qui représente le pion
    bool isActive; //booléen qui indique si le pion est actif ou non
    float originalScaleX, originalScaleY; // Taille originale du pion
    float centerX, centerY; // Centre de la cellule
    float maxScaleFactor; // Facteur d'échelle maximal

    PionModel();
    void init(float x, float y, float width, float height, Texture& texture);
    ~PionModel() = default;
    PionModel(const PionModel& autre) = default;

    void updateScale(float scaleFactor); // Met à jour le facteur d'échelle
    void draw(RenderWindow &window); // Dessine le pion
    void clear(); // Efface le pion
    void setActive(bool active); // Active ou désactive le pion
    bool getActive(); // Renvoie si le pion est actif ou non
};

#endif
