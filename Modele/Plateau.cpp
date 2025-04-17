#include "Plateau.hpp"

Plateau::Plateau(int taille, string jeu)
    : taille(taille), grille(taille, vector<Case>(taille, Case(Piece("Pion", CouleurPiece::VIDE)))) {
    if(jeu == "Butin"){
        initPlateauButin();
    }else if(jeu == "Dames"){
        initPlateauDames();
    }
    else{
        initPlateauSafari();
    }
}

Plateau Plateau::clone(Plateau plateau){
    Plateau plateauClone{10, "Dames"};
    for(int i=0;i<taille;i++){
        for(int j=0; j<taille;j++){
            plateauClone.getCase(i,j).setPiece(plateau.grille[i][j].getPiece());
        }
    }
    return plateauClone;
}

Case& Plateau::getCase(int x, int y) {
    return grille[x][y];
}

const Case& Plateau::getCase(int x, int y) const {
    return grille[x][y];
}

vector<vector<Case>> Plateau::getGrille() const{
    return grille;
}

void Plateau::initPlateauButin() {
    vector<CouleurPiece> pions;
    
    // Ajoutez le nombre exact de pions de chaque couleur
    for (int i = 0; i < 34; ++i) pions.push_back(JAUNE);
    for (int i = 0; i < 20; ++i) pions.push_back(ROUGE);
    for (int i = 0; i < 10; ++i) pions.push_back(NOIR);
    
    // Mélangez les pions
    random_device rd;
    mt19937 g(rd());
    shuffle(pions.begin(), pions.end(), g);

    // Placez les pions mélangés sur le plateau
    for (int i = 0; i < taille; ++i) {
        for (int j = 0; j < taille; ++j) {
            grille[i][j].getPiece().setCouleurPiece(pions[i * taille + j]);
        }
    }
}

void Plateau::initPlateauDames() {

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < taille; ++x) {
            if ((x + y) % 2 == 1) { // Placer les pions seulement sur les cases foncées
                grille[y][x].setPiece(Piece("Pion", CouleurPiece::NOIR));
            }
        }
    }

    // Laisser deux lignes vides au milieu
    for (int y = 4; y < 6; ++y) {
        for (int x = 0; x < taille; ++x) {
            grille[y][x].setPiece(Piece("vide", CouleurPiece::VIDE));
        }
    }

    // Initialiser les pions rouges sur les 4 dernières lignes
    for (int y = 6; y < taille; ++y) {
        for (int x = 0; x < taille; ++x) {
            if ((x + y) % 2 == 1) {
                grille[y][x].setPiece(Piece("Pion", CouleurPiece::ROUGE));
            }
        }
    }
}

void Plateau::initPlateauSafari(){
    for(int i=0;i<taille;i++){
        for(int j=0; j<taille;j++){
            grille[i][j].setPiece(Piece("vide", CouleurPiece::VIDE));
        }
    }
}

void Plateau::deplacerPion(int x1, int y1, int x2, int y2) {
    // Obtenir la couleur du pion à déplacer.
    CouleurPiece pion = grille[x1][y1].getPiece().getCouleurPiece();

    // Mettre la case de départ à vide.
    grille[x1][y1].getPiece().setCouleurPiece(CouleurPiece::VIDE);

    // Placer le pion sur la case d'arrivée.
    grille[x2][y2].getPiece().setCouleurPiece(pion);
}