#include "Butin.hpp"

Butin::Butin() : Jeu() {
    plateau = Plateau(8,"Butin");
    joueurActuel = 1;
}

int Butin::getIdWinner() {
    int idMaxScore = joueurs[0].getId();
    int maxScore = joueurs[0].getScore();

    for (const Joueur& joueur : joueurs) {
        if (joueur.getScore() > maxScore) {
            maxScore = joueur.getScore();
            idMaxScore = joueur.getId();
        }
    }

    return idMaxScore+1;
}

bool Butin::peutSauter(int x1, int y1, int x2, int y2,const Plateau& plateau) const {
    // On s'assure que les coordonnées sont dans les limites du plateau.
    if (x2 < 0 || x2 >= plateau.getGrille().size() || y2 < 0 || y2 >= plateau.getGrille().size()) {
        return false;
    }

    // Vérifie si la case de départ a un pion jaune.
    if (plateau.getCase(x1, y1).getPiece().getCouleurPiece() != CouleurPiece::JAUNE) {
        return false;
    }

    // Vérifie si la case d'arrivée est vide.
    if (!(plateau.getCase(x2, y2).getPiece().getCouleurPiece() == VIDE)) {
        return false;
    }

    // Vérifie la validité du déplacement
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);

    // Vérifier que le mouvement est soit deux cases en diagonale, soit deux cases horizontalement, soit deux cases verticalement.
    bool isDiagonalMove = dx == 2 && dy == 2;
    bool isHorizontalMove = dx == 2 && dy == 0;
    bool isVerticalMove = dx == 0 && dy == 2;

    if (!(isDiagonalMove || isHorizontalMove || isVerticalMove)) {
        return false;
    }

    // Calculer la position du pion potentiellement sauté.
    int xMilieu = (x1 + x2) / 2;
    int yMilieu = (y1 + y2) / 2;

    // Vérifie si le pion sauté n'a deja pas été pris
    for (const pair<int, int>& paire : getPiecesPrises()) {
        if (paire.first == xMilieu && paire.second == yMilieu) {
            return false;
        }
    }

    // Vérifie si la case intermédiaire a un pion (de n'importe quelle couleur autre que vide).
    if (plateau.getCase(xMilieu, yMilieu).getPiece().getCouleurPiece() == VIDE) {
        return false;
    }
    return true; // Le saut est possible.
}

void Butin::mettreAJourScore(int x,int y) {
    Joueur& j = getJoueur(joueurActuel);
    CouleurPiece pionCapturé = plateau.getCase(x,y).getPiece().getCouleurPiece();
    switch (pionCapturé) {
        case 2:
            j.ajouterScore(3);
            break;
        case 1:
            j.ajouterScore(2);
            break;
        case 0:
            j.ajouterScore(1);
            break;
        default:
            break;
    }
}

bool Butin::estFinJeu(Plateau &plateau) const {
    // Parcourir toutes les cases du plateau.
    for (int x = 0; x < plateau.getGrille().size(); ++x) {
        for (int y = 0; y < plateau.getGrille().size(); ++y) {
            // Vérifie si la case contient un pion jaune.
            if (plateau.getCase(x, y).getPiece().getCouleurPiece() == CouleurPiece::JAUNE) {
                // Vérifie tous les mouvements possibles pour ce pion.
                if (peutEncoreSauter(x, y)) {
                    return false; // Il reste encore des mouvements possibles.
                }
            }
        }
    }
    return true; // Aucun mouvement supplémentaire n'est possible, le jeu est terminé.
}

bool Butin::peutEncoreSauter(int x, int y) const {
    // Vérifie les sauts dans toutes les directions possibles.
    for (int dx = -2; dx <= 2; dx += 2) {
        for (int dy = -2; dy <= 2; dy += 2) {
            if (dx != 0 || dy != 0) {
                if (peutSauter(x, y, x + dx, y + dy,plateau)) {
                    return true; // Un saut est possible.
                }
            }
        }
    }
    return false; // Aucun saut possible pour ce pion.
}

bool Butin::deplacerPiece(int x1, int y1, int x2, int y2, Plateau& plateau) {
    // c'est un cas spécifique, celui du premuier tour où chaque joueur enleve un pion jeune
    if(x2==-1 && y2 == -1){
        plateau.getCase(x1,y1).getPiece().setCouleurPiece(VIDE);
    }
    else{
        CouleurPiece newCouleur = plateau.getCase(x1,y1).getPiece().getCouleurPiece();
        plateau.getCase(x1,y1).getPiece().setCouleurPiece(VIDE);
        plateau.getCase(x2,y2).getPiece().setCouleurPiece(newCouleur);
    }
    return true;
}

void Butin::updateModel(){
    for (const pair<int, int>& paire : getPiecesPrises()) {
        plateau.getCase(paire.first, paire.second).getPiece().setCouleurPiece(VIDE);
    }
    piecesPrises.clear();
}

void Butin::calculerScoreFinal() {
    int pointsDeduction = 0;
    for (int x = 0; x < plateau.getGrille().size(); ++x) {
        for (int y = 0; y < plateau.getGrille().size(); ++y) {
            switch (plateau.getCase(x, y).getPiece().getCouleurPiece()) {
                case 2:
                    pointsDeduction += 3;
                    break;
                case 1:
                    pointsDeduction += 2;
                    break;
                case 0:
                    pointsDeduction += 1;
                    break;
                default:
                    break; // Pas de déduction pour les cases vides.
            }
        }
    }
    Joueur& j = getJoueur(joueurActuel);
    j.ajouterScore(-pointsDeduction);
}