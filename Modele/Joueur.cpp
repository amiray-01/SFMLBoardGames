#include "Joueur.hpp"

int Joueur::nbJoueurs = 0;

Joueur::Joueur() : id{nbJoueurs}, score{0} {
    nbJoueurs++;
}

Joueur::Joueur(const Joueur& j) : id{j.id}, score{j.score} {}

void Joueur::ajouterScore(int points) {
    score += points;
    if(score < 0) score = 0;
}

int Joueur::getId() const {
    return id;
}

int Joueur::getScore() const {
    return score;
}