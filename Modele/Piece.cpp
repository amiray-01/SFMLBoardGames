#include "Piece.hpp"

Piece::Piece(string type, CouleurPiece couleur) : type(type), couleur(couleur) {}

string Piece::getType() const {
    return type;
}

CouleurPiece Piece::getCouleurPiece() const {
    return couleur;
}

CouleurPiece Piece::getCouleurPiece(int c){
    switch(c){
        case 0:
            return JAUNE;
        case 1:
            return ROUGE;
        case 2:
            return NOIR;
        default:
            return VIDE;
    }
}

void Piece::setCouleurPiece(CouleurPiece couleur) {
    this->couleur = couleur;
}