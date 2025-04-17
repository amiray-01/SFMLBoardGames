#ifndef _PIECE
#define _PIECE

#include <string>
using namespace std;

enum CouleurPiece { JAUNE, ROUGE, NOIR, VIDE };

class Piece {

public:
    Piece(string type, CouleurPiece couleur);
    virtual ~Piece() = default;
    string getType() const;
    CouleurPiece getCouleurPiece() const; // Retourne la couleur du pion dans la case
    CouleurPiece getCouleurPiece(int c);
    void setCouleurPiece(CouleurPiece couleur); // Définit la couleur du pion dans la case

private:
    string type;
    CouleurPiece couleur;
};

#endif