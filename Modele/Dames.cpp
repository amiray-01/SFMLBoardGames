#include "Dames.hpp"

Dames::Dames() : Jeu() {
    plateau = Plateau(10,"Dames");
    joueurActuel = 1;
}

bool Dames::peutSauter(int x1, int y1, int x2, int y2,const Plateau& plateau) const {
    // Vérifie que les coordonnées sont dans les limites du plateau
    if (x2 < 0 || x2 >= plateau.getGrille().size() || y2 < 0 || y2 >= plateau.getGrille().size()) {
        return false;
    }

    const Case& depart = plateau.getCase(x1, y1);
    const Case& arrivee = plateau.getCase(x2, y2);

    // Vérifie que la case de départ contient une pièce
    if (depart.getPiece().getType() == "vide") {
        return false;
    }

    // Vérifie que la case d'arrivée est vide
    if (arrivee.getPiece().getType() != "vide") {
        return false;
    }

    // condition de deplacement d'un pion
    if (depart.getPiece().getType() == "Pion") {
        return peutSauterPion(x1, y1, x2, y2,plateau);
    } 
    // condition de deplacement d'une dame
    else if (depart.getPiece().getType() == "Dame") {
        return peutSauterDames(x1, y1, x2, y2,plateau);
    }
    return true;
}

bool Dames::peutSauterDames(int x1, int y1, int x2, int y2,const Plateau& plateau) const {
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dx) != abs(dy)) {
        return false;
    }

    int pasX = (dx > 0) ? 1 : -1;
    int pasY = (dy > 0) ? 1 : -1;
    int x = x1 + pasX;
    int y = y1 + pasY;

    while (x != x2 && y != y2) {
        if (plateau.getCase(x, y).getPiece().getType() != "vide") {
            return false;
        }
        x += pasX;
        y += pasY;
    }
    return true;
}

bool Dames::peutSauterPion(int x1, int y1, int x2, int y2,const Plateau& plateau) const {
    const Case& depart = plateau.getCase(x1, y1);
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) != 1 || abs(dy) != 1) {
        return false;
    }

    // Vérifie la direction du mouvement en fonction de la couleur du pion
    if (depart.getPiece().getCouleurPiece() == NOIR) {
        if (x2 <= x1) {
            return false;
        }
    } else if (depart.getPiece().getCouleurPiece() == ROUGE) {
        if ( x2 >= x1) {
            return false;
        }
    }

    return true;
}


bool Dames::estPriseValide(int x1, int y1, int x2, int y2,Plateau& plateau) const {
    // Vérifie que les coordonnées sont dans les limites du plateau
    if (x2 < 0 || x2 >= plateau.getGrille().size() || y2 < 0 || y2 >= plateau.getGrille().size()) {
        return false;
    }

    const Case& depart = plateau.getCase(x1, y1);
    const Case& arrivee = plateau.getCase(x2, y2);

    // Vérifie que la case de départ contient une pièce et celle d'arrivée est vide
    if (depart.getPiece().getType() == "vide" || arrivee.getPiece().getType() != "vide") {
        return false;
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    // Vérifie que le mouvement est diagonal
    if (abs(dx) != abs(dy)) {
        return false;
    }

    // Règles spécifiques pour les pions
    if (depart.getPiece().getType() == "Pion") {
        return estPriseValidePion(x1, y1, x2, y2,plateau);
    }
    
    // Règles spécifiques pour les dames
    else if (depart.getPiece().getType() == "Dame") {
        return estPriseValideDames(x1, y1, x2, y2,plateau);
    }

    return true;
}

bool Dames::estPriseValidePion(int x1, int y1, int x2, int y2,Plateau& plateau) const {
    const Case& depart = plateau.getCase(x1, y1);

    int dx = x2 - x1;
    int dy = y2 - y1;

    // Position de la pièce potentiellement prise pour un pion
    int xPrise = (x1 + x2) / 2;
    int yPrise = (y1 + y2) / 2;
    const Case& casePrise = plateau.getCase(xPrise, yPrise);

    // Vérifiez si la case contient une pièce adverse et qu'elle n'a pas été prise précédemment
    if (casePrise.getPiece().getType() == "vide" || 
        casePrise.getPiece().getCouleurPiece() == depart.getPiece().getCouleurPiece() ||
        find(piecesPrises.begin(), piecesPrises.end(), make_pair(xPrise, yPrise)) != piecesPrises.end()) {
        return false;
    }

    // Les pions peuvent prendre en sautant une case en avant ou en arrière
    if (abs(dx) != 2 || abs(dy) != 2) {
        return false;
    }
    return true;
}


bool Dames::estPriseValideDames(int x1, int y1, int x2, int y2,Plateau& plateau) const{
    const Case& depart = plateau.getCase(x1, y1);
    int dx = x2 - x1;
    int dy = y2 - y1;
    // Les dames peuvent prendre en sautant plusieurs cases vides
    // mais ne doivent pas sauter par-dessus plus d'une pièce
    int pasX = (dx > 0) ? 1 : -1; // Détermine la direction du saut en X
    int pasY = (dy > 0) ? 1 : -1; // Détermine la direction du saut en Y
    int compteurPieces = 0; // Compte le nombre de pièces rencontrées

    for (int x = x1 + pasX, y = y1 + pasY; x != x2 && y != y2; x += pasX, y += pasY) {
        const Case& caseCourante = plateau.getCase(x, y);
        if (caseCourante.getPiece().getType() != "vide") {
            // Si c'est une pièce adverse, augmentez le compteur
            if (caseCourante.getPiece().getCouleurPiece() != depart.getPiece().getCouleurPiece()) {
                compteurPieces++;
            } else {
                // Si c'est une pièce alliée, invalidez la prise
                return false;
            }
            if (find(piecesPrises.begin(), piecesPrises.end(), make_pair(x, y)) != piecesPrises.end()){
                return false;  // La pièce a déjà été prise dans cette séquence
            }
        }

        // Si plus d'une pièce est rencontrée, la prise n'est pas valide
        if (compteurPieces > 1) {
            return false;
        }
    }

    // Si aucune ou plus d'une pièce est sautée, la prise n'est pas valide
    if (compteurPieces != 1) {
        return false;
    }
    return true;
}

bool Dames::deplacerPiece(int x1, int y1, int x2, int y2,Plateau& plateau) {
    if (peutSauter(x1, y1, x2, y2,plateau)) {
        Piece pieceDeplacee = plateau.getCase(x1, y1).getPiece();
        plateau.getCase(x1, y1).setPiece(Piece("vide", VIDE));
        plateau.getCase(x2, y2).setPiece(pieceDeplacee);
        return true;
    }
    return false;
}

bool Dames::effectuerPrise(int x1, int y1, int x2, int y2,Plateau& plateau) {
    if (estPriseValide(x1, y1, x2, y2,plateau)) {
        const Case& depart = plateau.getCase(x1, y1);
        // Si la pièce qui prend est une dame, trouvez la position exacte de la pièce prise
        if (depart.getPiece().getType() == "Dame") {
            int pasX = (x2 - x1 > 0) ? 1 : -1;
            int pasY = (y2 - y1 > 0) ? 1 : -1;

            int x = x1 + pasX;
            int y = y1 + pasY;
            while (x != x2 && y != y2) {
                const Case& caseCourante = plateau.getCase(x, y);
                if (caseCourante.getPiece().getType() != "vide" &&
                    caseCourante.getPiece().getCouleurPiece() != depart.getPiece().getCouleurPiece()) {
                    ajouterPiecePrise(x, y);
                    break; // Sortez de la boucle une fois la pièce prise trouvée
                }
                x += pasX;
                y += pasY;
            }
        } else {
            // Pour un pion, la pièce prise est au milieu
            int xPrise = (x1 + x2) / 2;
            int yPrise = (y1 + y2) / 2;
            ajouterPiecePrise(xPrise, yPrise);
        }

        // Déplacer la pièce qui prend
        Piece piecePrenante = depart.getPiece();
        plateau.getCase(x1, y1).setPiece(Piece("vide", VIDE));
        plateau.getCase(x2, y2).setPiece(piecePrenante);
        return true;
    }
    return false;
}

void Dames::couronnerPion(int x, int y, Plateau& plateau) {
    Case& caseCourante = plateau.getCase(x, y);
    Piece& pieceCourante = caseCourante.getPiece();

    // Vérifie si la pièce est un pion
    if (pieceCourante.getType() == "Pion") {
        // Pour les pions noirs, couronner s'ils atteignent la première ligne (x == 0)
        if (pieceCourante.getCouleurPiece() == NOIR && x == plateau.getGrille().size() - 1) {
            caseCourante.setPiece(Piece("Dame", NOIR));
        }
        // Pour les pions rouges, couronner s'ils atteignent la dernière ligne (x == plateau.getGrille().size() - 1)
        else if (pieceCourante.getCouleurPiece() == ROUGE && x == 0) {
            caseCourante.setPiece(Piece("Dame", ROUGE));
        }
    }
}

void Dames::updateModel() {
    for (const auto& prise : piecesPrises) {
        plateau.getCase(prise.first, prise.second).setPiece(Piece("vide", VIDE));
    }
    piecesPrises.clear();
}

// Fin de jeu

bool Dames::aucunMouvementPossible(Plateau &plateau) const {
    // Parcoure toutes les cases du plateau
    for (int x = 0; x < plateau.getGrille().size(); ++x) {
        for (int y = 0; y < plateau.getGrille()[x].size(); ++y) {
            const Case& caseCourante = plateau.getCase(x, y);
            const Piece& pieceCourante = caseCourante.getPiece();

            // Vérifie si la pièce appartient au joueur
            if (pieceCourante.getCouleurPiece() == joueurActuel) {
                // Parcoure toutes les cases du plateau pour vérifier les mouvements et prises possibles
                for (int x2 = 0; x2 < plateau.getGrille().size(); ++x2) {
                    for (int y2 = 0; y2 < plateau.getGrille()[x2].size(); ++y2) {
                        if (peutSauter(x, y, x2, y2,plateau) || estPriseValide(x, y, x2, y2,plateau)) {
                            return false;  // Un mouvement ou une prise valide est trouvé
                        }
                    }
                }
            }
        }
    }
    return true; // Aucun mouvement ou prise possible pour toutes les pièces du joueur
}

bool Dames::plusDePieces() const {
    int nombreDePieces = 0;

    // Parcoure toutes les cases du plateau
    for (int x = 0; x < plateau.getGrille().size(); ++x) {
        for (int y = 0; y < plateau.getGrille()[x].size(); ++y) {
            const Case& caseCourante = plateau.getCase(x, y);
            const Piece& pieceCourante = caseCourante.getPiece();

            // Si la case contient une pièce appartenant au joueur, incrémentez le compteur
            if (pieceCourante.getCouleurPiece() == joueurActuel && pieceCourante.getType() != "vide") {
                nombreDePieces++;
            }
        }
    }

    // Si le joueur n'a plus de pièces, retournez true
    return nombreDePieces == 0;
}

// Test si le joueur a des pions ou des dames qui peuvent faire une prise
bool Dames::peutFaireUnePrise(CouleurPiece couleurJoueur,Plateau& plateau) const {
    for (int x = 0; x < plateau.getGrille().size(); ++x) {
        for (int y = 0; y < plateau.getGrille()[x].size(); ++y) {
            const Case& caseCourante = plateau.getCase(x, y);
            const Piece& piece = caseCourante.getPiece();

            if (piece.getCouleurPiece() == couleurJoueur) {
                if (piece.getType() == "Pion" && prisePionPossible(x, y, couleurJoueur,plateau)) {
                    return true;
                } else if (piece.getType() == "Dame" && priseDamePossible(x, y,plateau)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Dames::prisePossible(int x, int y,Plateau& plateau) const {
    const Piece& piece = plateau.getCase(x, y).getPiece();

    if (piece.getType() == "vide") {
        return false;
    }

    // Vérifiez les prises pour un pion
    if (piece.getType() == "Pion") {
        return prisePionPossible(x, y, piece.getCouleurPiece(),plateau);
    }
    // Vérifiez les prises pour une dame
    else if (piece.getType() == "Dame") {
        return priseDamePossible(x, y,plateau);
    }

    return false;
}

bool Dames::prisePionPossible(int x, int y, int couleur,Plateau& plateau) const {
    // Vérifie les prises diagonales possibles dans toutes les directions
    return (estPriseValide(x, y, x - 2, y - 2,plateau) ||  // Diagonale arrière gauche
            estPriseValide(x, y, x + 2, y - 2,plateau) ||  // Diagonale arrière droite
            estPriseValide(x, y, x - 2, y + 2,plateau) ||  // Diagonale avant gauche
            estPriseValide(x, y, x + 2, y + 2,plateau));    // Diagonale avant droite
}

bool Dames::priseDamePossible(int x, int y,Plateau& plateau) const {
    // Parcourir toutes les directions diagonales pour vérifier les prises
    for (int dx = -1; dx <= 1; dx += 1) {
        for (int dy = -1; dy <= 1; dy += 2) {
            int x2 = x + dx;  // Commencer à la case adjacente
            int y2 = y + dy;

            // Parcourir la diagonale case par case
            while (x2 >= 0 && x2 < plateau.getGrille().size() && y2 >= 0 && y2 < plateau.getGrille()[0].size()) {
                if (plateau.getCase(x2, y2).getPiece().getType() != "vide") {
                    // Vérifie la prise à partir de la case suivante si une pièce est trouvée
                    if (estPriseValide(x, y, x2 + dx, y2 + dy,plateau)) {
                        return true;
                    }
                    break; // Si une pièce est trouvée, il n'est pas nécessaire de continuer plus loin dans cette direction
                }
                x2 += dx;
                y2 += dy;
            }
        }
    }
    return false;
}

bool Dames::estFinJeu(Plateau &plateau) const{
    if(aucunMouvementPossible(plateau) || plusDePieces()){
        return true;
    }
    return false;
}


void Dames::maxSautsDepuisPosition(int x, int y, Plateau& plateau, std::vector<std::pair<int, int>>& cheminEnCours, std::vector<std::vector<std::pair<int, int>>>& cheminsOptimaux, int& maxPrises, bool isDame) {
    bool sautPossible = false;

    // Explorez chaque diagonale dans les 4 directions
    for (int dx = -1; dx <= 1; dx += 2) {
        for (int dy = -1; dy <= 1; dy += 2) {
            int x2 = x + dx;
            int y2 = y + dy;

            // Parcourez chaque case dans la direction diagonale jusqu'à trouver une pièce ou atteindre les limites du plateau
            while (x2 >= 0 && x2 < plateau.getGrille().size() && y2 >= 0 && y2 < plateau.getGrille().size()) {
                if (plateau.getCase(x2, y2).getPiece().getType() != "vide") {
                    // Si la prise est possible à partir de la case suivante, continuez
                    if (estPriseValide(x, y, x2 + dx, y2 + dy, plateau)) {
                        sautPossible = true;
                        Plateau nouveauPlateau = plateau.clone(plateau);
                        effectuerPrise(x, y, x2 + dx, y2 + dy, nouveauPlateau);

                        cheminEnCours.push_back({x2 + dx, y2 + dy});
                        maxSautsDepuisPosition(x2 + dx, y2 + dy, nouveauPlateau, cheminEnCours, cheminsOptimaux, maxPrises, isDame);

                        cheminEnCours.pop_back();
                    }
                    break;
                }

                // Si c'est une dame, il faut continuer à chercher des prises potentielles plus loin dans la diagonale
                if (isDame) {
                    x2 += dx;
                    y2 += dy;
                } else {
                    break; // Pour un pion, ne regarder que la première case diagonale
                }
            }
        }
    }

    // Si aucun saut supplémentaire n'est possible et que nous avons atteint ou dépassé le nombre maximal de prises
    if (!sautPossible && cheminEnCours.size() >= maxPrises) {
        if (cheminEnCours.size() > maxPrises) {
            cheminsOptimaux.clear();
            maxPrises = cheminEnCours.size();
        }
        cheminsOptimaux.push_back(cheminEnCours);
    }
}
