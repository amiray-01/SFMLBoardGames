#include "VueGenerale.hpp"

VueGenerale::VueGenerale(int taille,int cellSize) : SIZE(taille), cellSize(cellSize){
    if (!font.loadFromFile("Vue/ressources/police.ttf")) {
        cout << "Erreur lors du chargement de la police" << endl;
    }
    initScoreboard();
}

VueGenerale::~VueGenerale() {
}

void VueGenerale::initPlateau(){ //initialise le plateau
    cases.resize(SIZE, vector<RectangleShape>(SIZE));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) { 
            if ((i + j) % 2 == 0) {
                cases[i][j].setFillColor(Color(255, 248, 220));
            } else { 
                cases[i][j].setFillColor(Color(130, 180, 163));
            }
                cases[i][j].setSize({cellSize, cellSize});
                cases[i][j].setPosition(i * cellSize, j * cellSize);
        }
    }
}

void VueGenerale::initScoreboard(){
    scoreText.setFont(font);
    scoreText.setCharacterSize(20); // Taille de la police
    scoreText.setFillColor(Color::White);
    scoreText.setString("Le joueur 1 commence"); 
    scoreboardBackground.setSize(Vector2f(600, 200)); // Ajuster la taille
    scoreboardBackground.setPosition(0, 600); // Position en bas de l'écran
    scoreboardBackground.setFillColor(Color(128, 128, 128)); // Couleur du fond
    scoreText.setPosition(10,600); // Position du texte
}

void VueGenerale::draw(RenderWindow &window) { //dessine le plateau
    for (int i = 0; i < SIZE; i++) { 
        for (int j = 0; j < SIZE; j++) { 
            window.draw(cases[i][j]); // Dessine la case
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) { 
                Pions[i][j].draw(window); // Dessine le pion
        }
    }
}


void VueGenerale::setScoreboard(string s){ //change le texte du scoreboard
            scoreText.setString(s);
}

PionModel& VueGenerale::getPion(int x, int y) { //retourne le pion
    return Pions[x][y];
}

CouleurPiece VueGenerale::getCouleurPiece(int x, int y,Plateau p){ //retourne la couleur du pion    
    return p.getGrille()[x][y].getPiece().getCouleurPiece();
}

RectangleShape& VueGenerale::getCase(int x, int y) { //retourne la case
    return cases[x][y];
}


void VueGenerale::clearOpacity(vector<pair<int, int>> piecesPrises){ //enlève l'opacité des pions
    for (int i = 0; i < piecesPrises.size(); i++) {
        Pions[piecesPrises[i].first][piecesPrises[i].second].sprite.setColor(Color(255, 255, 255, 255));
    }
}
