#include "Safari.hpp"


Safari::Safari() : Jeu() {
    plateau = Plateau(15,"Safari");
    joueurActuel = 1;
    initialiserJoueursActifs(joueurs);
}

void Safari::initialiserJoueursActifs(const vector<Joueur>& joueursDepart) {
    joueursActifs.clear(); // Effacer d'abord les joueurs actifs existants

    for (const Joueur& joueur : joueursDepart) {
        Joueur joueurCopie{joueur}; // Utiliser le constructeur de copie pour une copie profonde
        joueursActifs.push_back(joueurCopie);
    }
}

const vector<Joueur>& Safari::getJoueursActifs() const {
    return joueursActifs;
}

bool Safari::peutPoserPion(int i,int j,Plateau& plateau) const{
    if ( i%2== 0 && j%2 == 0 && plateau.getCase(i,j).getPiece().getType() == "vide"){
        plateau.getCase(i,j).setPiece(Piece("Animal",plateau.getCase(i,j).getPiece().getCouleurPiece(joueurActuel-1)));
        return true;
    }
    return false;
}

bool Safari::peutSauter(int x1, int y1, int x2, int y2,const Plateau& plateau) const{
    // Vérifie si les coordonnées de départ et d'arrivée sont valides
    if (x2 < 0 || x2 >= plateau.getGrille().size() || y2 < 0 || y2 >= plateau.getGrille().size()) {
        return false;
    }

    if (!caseValidePourAnimal(x2, y2)) {
        return false;
    }

    const Piece& pieceDepart = plateau.getCase(x1, y1).getPiece();
    
    // Vérifie si la case de départ contient un animal
    if (pieceDepart.getType() != "Animal") {
        return false;
    }

    // Vérifie si la case d'arrivée est vide
    if (plateau.getCase(x2, y2).getPiece().getType() != "vide") {
        return false;
    }

    // Vérifie si le déplacement est horizontal ou vertical
    if (x1 != x2 && y1 != y2) {
        return false; // Pas un déplacement valide (doit être en ligne droite)
    }

    // Vérifie s'il y a des barrières sur le chemin
    if (cheminBloqueParBarriere(x1, y1, x2, y2)) {
        return false;
    }

    return true;
}

bool Safari::caseValidePourAnimal(int x, int y) const {
    // Vérifie si la case est une case valide pour un animal
    return (x % 2 == 0 && y % 2 == 0);
}

bool Safari::cheminBloqueParBarriere(int x1, int y1, int x2, int y2) const {
    int dx = (x2 > x1) ? 1 : (x2 < x1) ? -1 : 0;
    int dy = (y2 > y1) ? 1 : (y2 < y1) ? -1 : 0;

    int x = x1 + dx;
    int y = y1 + dy;

    while (x != x2 || y != y2) {
        if (plateau.getCase(x, y).getPiece().getType() == "Barriere") {
            return true; // Barrière trouvée sur le chemin
        }
        x += dx;
        y += dy;
    }

    return false; // Aucune barrière trouvée sur le chemin
}

bool Safari::deplacerPiece(int x1, int y1, int x2, int y2,Plateau& plateau) {
    if (peutSauter(x1, y1, x2, y2,plateau)) {
        Piece pieceADeplacer = plateau.getCase(x1, y1).getPiece();

        // Définir la case de départ à vide
        plateau.getCase(x1, y1).setPiece(Piece("vide", VIDE));

        // Placer la pièce à la case d'arrivée
        plateau.getCase(x2, y2).setPiece(pieceADeplacer);
    }
    return false;
}


bool Safari::caseValidePourBarriere(int x, int y) {
    // Vérifie si la case est une case impaire ou mixte pour la barrière
    if ((x % 2 == 0 && y % 2 == 0) || (x % 2 != 0 && y % 2 != 0)) {
        return false;
    }

    // Vérifie si la case est déjà occupée par une barrière ou un animal
    Piece piece = plateau.getCase(x, y).getPiece();
    if (piece.getType() != "vide") {
        return false;  // La case est déjà occupée
    }

    return true;  // La case est valide pour une barrière
}

// parcours en largeur en utilisant BFS
bool Safari::zoneDeMoinsDeHuitCases(int x, int y) {
    set<pair<int, int>> visited;  // Pour enregistrer les cases visitées
    queue<pair<int, int>> toExplore;  // File d'attente pour la recherche en largeur

    toExplore.push(make_pair(x, y));
    visited.insert(make_pair(x, y));

    while (!toExplore.empty()) {
        auto current = toExplore.front();
        toExplore.pop();

        vector<pair<int, int>> directions = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};
        // Vérifiez toutes les directions (haut, bas, gauche, droite)
        for (const auto& dir : directions) {
            int newX = current.first + dir.first;
            int newY = current.second + dir.second;

            // Vérifiez si la nouvelle position est valide et pas encore visitée
            if (positionValide(newX, newY) && !barriereEntre(current.first, current.second, newX, newY) && visited.find(make_pair(newX, newY)) == visited.end()) {
                toExplore.push(make_pair(newX, newY));
                visited.insert(make_pair(newX, newY));
            }
        }

        // Si plus de 7 cases sont accessibles, l'animal n'est pas capturé
        if (visited.size() > 7) {
            return false;
        }
    }

    // L'animal est capturé si moins de 8 cases sont accessibles
    return true;
}



bool Safari::barriereEntre(int x1, int y1, int x2, int y2) const {
    // Calcule la position de la barrière potentielle
    int xBarriere = (x1 + x2) / 2;
    int yBarriere = (y1 + y2) / 2;

    // Vérifie si la position de la barrière est valide
    if (!positionValide(xBarriere, yBarriere)) {
        return false;
    }

    // Vérifiez si une barrière est présente
    return plateau.getCase(xBarriere, yBarriere).getPiece().getType() == "Barriere";
}

bool Safari::positionValide(int x, int y) const {
    return x >= 0 && x < plateau.getGrille().size() && y >= 0 && y < plateau.getGrille().size();
}


bool Safari::placerBarriere(int x, int y) {
    // Vérifie si la case est valide pour placer une barrière
    if (!caseValidePourBarriere(x, y)) {
        return false;
    }

    // Place temporairement la barrière pour vérifier les captures
    plateau.getCase(x, y).setPiece(Piece("Barriere", VIDE));

    // Vérifie si un animal est capturé
    bool capture = false;
    for (int i = 0; i < plateau.getGrille().size(); i++) {
        for (int j = 0; j < plateau.getGrille().size(); j++) {
            Piece piece = plateau.getCase(i, j).getPiece();
            if (piece.getType() == "Animal") {
                if (zoneDeMoinsDeHuitCases(i, j)) { // si l'animal se trouve dans une zone de moins de huit cases
                    // Capturer l'animal
                    plateau.getCase(i, j).setPiece(Piece("vide", VIDE));
                    capture = true;
                }
            }
        }
    }

    return true;
}

bool Safari::estFinJeu(Plateau &plateau) const{
    vector<int> joueursASupprimer;

    // Parcourez chaque joueur
    for (int i = 0; i < joueurs.size(); ++i) {
        bool aDesAnimaux = false;

        // Parcourir chaque case du plateau pour trouver les animaux du joueur
        for (int x = 0; x < plateau.getGrille().size(); ++x) {
            for (int y = 0; y < plateau.getGrille()[x].size(); ++y) {
                Piece piece = plateau.getCase(x, y).getPiece();
                if (piece.getType() == "Animal" && piece.getCouleurPiece() == joueurs[i].getId()) {
                    aDesAnimaux = true;
                    break; // Trouvé un animal, pas besoin de chercher plus loin pour ce joueur
                }
            }
            if (aDesAnimaux) {
                break; // Si on a trouvé un animal pour ce joueur, passer au joueur suivant
            }
        }

        if (!aDesAnimaux) {
            // Ce joueur n'a plus d'animaux, il faut le supprimer
            joueursASupprimer.push_back(i);
        }
    }
    // Supprimer les joueurs qui n'ont plus d'animaux
    vector<Joueur> joueursRestants;
    for (const Joueur& joueur : joueursActifs) {
        if (find(joueursASupprimer.begin(), joueursASupprimer.end(), joueur.getId()) == joueursASupprimer.end()) {
            // Le joueur n'est pas dans la liste des joueurs à supprimer
            joueursRestants.push_back(joueur);
        }
    }
    joueursActifs = joueursRestants;

    // Le jeu se termine si seulement un joueur reste
    return joueursActifs.size() == 1;
}

bool Safari::estPerdant(int idJoueur) const{
    for(int i=0; i< joueursActifs.size();i++){
        if(joueursActifs[i].getId() == idJoueur){
            return false;
        }
    }
    return true;
}