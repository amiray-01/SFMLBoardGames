#include "BaseControleur.hpp"

BaseControleur::BaseControleur(RenderWindow& window, VueGenerale& vue, Jeu& jeu,int nb) : vue{vue}, model{jeu},window{window},
isSelected{false}, boutonActive{false},couleur{VIDE},nbSauts{0},pionSelectionneX{-1}, pionSelectionneY{-1}, tour{1}, nbJoueurs{nb},endgame{false}, lastPlayer{-1},
hasPlayed{0}
{
    window.setFramerateLimit(60);
}

void BaseControleur::premiereSelection(int i,int j){ // gère la première sélection d'un pion
    isSelected = true; 
    pionSelectionneX = i;
    pionSelectionneY = j;
    couleur = vue.getCouleurPiece(i, j, model.getPlateau()); // récupère la couleur du pion sélectionné
    vue.getPion(i,j).updateScale(1.3f); // met à jour l'échelle du pion
}

void BaseControleur::prise(int i,int j, int xMilieu, int yMilieu){
    vue.getPion(xMilieu,yMilieu).sprite.setColor(Color(255, 255, 255, 128)); // met à jour la couleur du pion pris
    vue.getPion(i,j).updateScale(1.0f); // met à jour l'échelle du pion
    vue.getPion(xMilieu,yMilieu).updateScale(1.0f); // met à jour l'échelle du pion
    nbSauts++; // incrémente le nombre de sauts effectuées
}

void BaseControleur::reset(int i, int j){
    vue.getPion(i,j).setActive(false); // désactive le pion
    vue.getPion(i,j).updateScale(1.0f); // met à jour l'échelle du pion
    isSelected = false;
    nbSauts = 0;
    pionSelectionneX = -1;
    pionSelectionneY = -1;
    couleur = VIDE;
}

void BaseControleur::updateScoreboard(){ // met à jour le scoreboard
    std::ostringstream oss;
    for (int i = 1; i <= model.getListeJoueurs().size(); ++i) {
    Joueur& joueur = model.getJoueur(i);
    if(i == model.getListeJoueurs().size()){
        oss << "Joueur " << i << " : " << joueur.getScore() << endl;
    }
    else{
        oss << "Joueur " << i << " : " << joueur.getScore() << " | ";
    }
    }
    oss << "Tour : " << tour << std::endl;
    oss << "Au tour du joueur " << model.getJoueurActuel() << " !" << std::endl;
    vue.setScoreboard(oss.str());
}

void BaseControleur::handleTour(){ // gère le tour
    if(hasPlayed >= model.getListeJoueurs().size()){
        tour++;
        hasPlayed = 0;
    }
}


