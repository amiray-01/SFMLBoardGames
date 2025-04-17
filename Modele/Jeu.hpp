#ifndef _JEU
#define _JEU

#include<stdio.h>
#include<stdlib.h>
#include <iostream>
using namespace std;

#include "Plateau.hpp"
#include "Joueur.hpp"

class Jeu {
public:
    Jeu(); // Constructeur
    virtual ~Jeu() = default;
    Jeu(const Jeu& autre) = delete; // Supprimer le constructeur de copie
    Plateau& getPlateau();
    const Plateau& getPlateau() const;
    int getJoueurActuel() const;
    const void setJoueurActuel(int id);
    const vector<Joueur>& getListeJoueurs() const;
    void ajoutJoueur();
    Joueur& getJoueur(int id);
    void passerAuProchainJoueur();
    vector<pair<int, int>>& getPiecesPrises();
    const vector<pair<int, int>> getPiecesPrises() const;
    void ajouterPiecePrise(int x, int y);
    
    virtual bool estFinJeu(Plateau &plateau) const = 0; // Vérifier si le jeu est terminé
    virtual bool peutSauter(int x1, int y1, int x2, int y2,const Plateau& plateau) const = 0;
    virtual bool deplacerPiece(int x1, int y1, int x2, int y2,Plateau& plateau) = 0;

protected:
    Plateau plateau; // Plateau de jeu
    int joueurActuel; // ID du joueur actuel
    vector<Joueur> joueurs; // Liste des joueurs
    vector<pair<int, int>> piecesPrises; // Liste des coordonnées pièces prises
};

#endif