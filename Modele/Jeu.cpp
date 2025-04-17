#include "Jeu.hpp"

Jeu::Jeu() : plateau(Plateau()) {}

Plateau& Jeu::getPlateau() {
    return plateau;
}

const Plateau& Jeu::getPlateau() const {
    return plateau;
}

void Jeu::passerAuProchainJoueur() {
    joueurActuel++;
    if(joueurActuel >= joueurs.size()+1){
        joueurActuel = 1;
    }
}

int Jeu::getJoueurActuel() const{
    return joueurActuel;
}

const void Jeu::setJoueurActuel(int id){
    joueurActuel = id;
}

const vector<Joueur>& Jeu::getListeJoueurs() const{
    return joueurs;
}

void Jeu::ajoutJoueur(){
    Joueur j {};
    joueurs.push_back(j);
}

Joueur& Jeu::getJoueur(int id) {
    if (id <= 0 || id > joueurs.size()) { // Ajustement pour la numérotation à partir de 1
        cout << "id joueur = " << id << endl;
        throw out_of_range("ID de joueur invalide");
    }
    return joueurs[id - 1]; // Soustraire 1 de l'ID pour obtenir l'indice correct
}

vector<pair<int, int>>& Jeu::getPiecesPrises() {
    return piecesPrises;
}

const vector<pair<int, int>> Jeu::getPiecesPrises() const {
    return piecesPrises;
}

void Jeu::ajouterPiecePrise(int x, int y) {
    piecesPrises.push_back(make_pair(x, y));
}