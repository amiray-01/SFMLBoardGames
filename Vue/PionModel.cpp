#include "PionModel.hpp"    

    

    PionModel::PionModel() : isActive(false) {
        shape.setFillColor(Color::Transparent);
    }

    void PionModel::init(float x, float y, float width, float height, Texture& texture){ //initialise le pion
        shape.setPosition(x, y);
        shape.setSize({width, height});
        shape.setFillColor(Color::Transparent);

        sprite.setTexture(texture);
        originalScaleX = width / sprite.getLocalBounds().width - 0.3f;
        originalScaleY = height / sprite.getLocalBounds().height - 0.3f;
        sprite.setScale(originalScaleX, originalScaleY);

        // Calculer le centre de la cellule
        centerX = x + width / 2.0f;
        centerY = y + height / 2.0f;

        // Positionner le sprite au centre
        sprite.setPosition(centerX - sprite.getGlobalBounds().width / 2.0f, 
                           centerY - sprite.getGlobalBounds().height / 2.0f);

        maxScaleFactor = std::min(width / sprite.getGlobalBounds().width, 
                                  height / sprite.getGlobalBounds().height);
    }
    
    void PionModel::updateScale(float scaleFactor) { // Met à jour le facteur d'échelle
        // Appliquer le facteur d'échelle
        sprite.setScale(originalScaleX * scaleFactor, originalScaleY * scaleFactor);

        // Recalculer la position pour garder le sprite centré
        sprite.setPosition(centerX - sprite.getGlobalBounds().width / 2.0f, 
                           centerY - sprite.getGlobalBounds().height / 2.0f);
    }

    void PionModel::draw(RenderWindow &window) { // Dessine le pion
        window.draw(sprite);
    }
    void PionModel::clear(){ // Efface le pion
        sprite.setColor(Color::Transparent);
    }
    void PionModel::setActive(bool active) { // Active ou désactive le pion
        isActive = active;
    }
    bool PionModel::getActive() { // Renvoie si le pion est actif ou non
        return isActive;
    }
