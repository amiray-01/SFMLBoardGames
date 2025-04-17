#ifndef _PLATEAU
#define _PLATEAU

#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <random>
#include <iostream>
using namespace std;

#include "Case.hpp"
#include <vector>

class Plateau{
    public:
        Plateau(int taille = 8, string jeu = "Butin"); // Constructeur avec taille par défaut de 8x8
        virtual ~Plateau() = default; // Utilisez le destructeur par défaut
        Plateau(const Plateau& autre) = default; // Utilisez le constructeur de copie par défaut
        Case& getCase(int x, int y); // Retourne la case à la position (x, y)
        const Case& getCase(int x, int y) const;
        vector<vector<Case>> getGrille() const;
        void deplacerPion(int x1, int y1, int x2, int y2);
        Plateau clone(Plateau plateau);

    private:
        int taille;
        vector<vector<Case>> grille; // Grille du plateau
        int nombrePionsJaunes;
        int nombrePionsRouges;
        int nombrePionsNoirs;

        void initPlateauButin();
        void initPlateauDames();
        void initPlateauSafari();
        void mettreAJourPlateau();
};

#endif