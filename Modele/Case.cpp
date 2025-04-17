#include "Case.hpp"

Case::Case(Piece p) : piece(p) {}

void Case::setPiece(Piece nouvellePiece) {
    piece = nouvellePiece;
}

Piece& Case::getPiece() { return piece; }

const Piece Case::getPiece() const { return piece; }