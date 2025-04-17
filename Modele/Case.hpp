#ifndef _CASE
#define _CASE

#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include "Piece.hpp"
using namespace std;


class Case {
public:
    Case(Piece p); // Constructeur par défaut avec une case vide
    virtual ~Case() = default; // Utilisez le destructeur par défaut
    Case(const Case& autre) = default; // Utilisez le constructeur de copie par défaut
    void setPiece(Piece nouvellePiece);
    Piece& getPiece();
    const Piece getPiece() const;

private:
    Piece piece;
};

#endif
