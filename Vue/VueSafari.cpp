#include "VueSafari.hpp"


        VueSafari::VueSafari() : VueGenerale(15,70) {
            Pions.resize(SIZE, vector<PionModel>(SIZE));
            vector<vector<PionModel>> Pions(SIZE, vector<PionModel>(SIZE));
            if (!pionNoirTexture.loadFromFile("Vue/ressources/pion_noir.png")) { 
                cout << "Erreur lors du chargement de l'image" << endl;
            }
            if( !pionRougeTexture.loadFromFile("Vue/ressources/pion_rouge.png")){
                cout << "Erreur lors du chargement de l'image" << endl;
            }
            if(!pionVideTexture.loadFromFile("Vue/ressources/trans.png")){
                cout << "Erreur lors du chargement de l'image" << endl;           
            }
            if(!pionJauneTexture.loadFromFile("Vue/ressources/pion_jaune.png")){
                cout << "Erreur lors du chargement de l'image" << endl;           
            }
        }

void VueSafari::initPlateau() { //initialise le plateau avec les cases et les barrieres 
    const Color couleurCase1 = Color(255, 248, 220);  // Couleur de la première case
    const Color couleurCase2 = Color(130, 180, 163);  // Couleur de la seconde case
    const Color couleurBarriere = Color(100, 100, 100);  // Couleur des barrières

    cases.resize(15, vector<RectangleShape>(15));
    // On redimensionne le tableau à 2 dimensions
    for (int i = 0; i < 15; i++) { 
        for (int j = 0; j < 15; j++) {
            RectangleShape caseShape;
            int posX, posY;
            float largeur, hauteur;
            Color couleur;

            if (i % 2 == 0 && j % 2 == 0) { 
                // C'est une case de jeu
                largeur = tailleCase;
                hauteur = tailleCase;
                couleur = ((i + j) / 2 % 2 == 0) ? couleurCase1 : couleurCase2;
                posX = j / 2 * tailleCase + j / 2 * tailleBarriere;
                posY = i / 2 * tailleCase + i / 2 * tailleBarriere;
            } else if (i % 2 != j % 2) { 
                // C'est une barrière
                if (i % 2 == 0) {
                    // Barrière horizontale
                    largeur = tailleBarriere;
                    hauteur = tailleCase;
                    posX = (j / 2 + 1) * tailleCase + j / 2 * tailleBarriere;
                    posY = i / 2 * tailleCase + i / 2 * tailleBarriere;
                } else {
                    // Barrière verticale
                    largeur = tailleCase;
                    hauteur = tailleBarriere;
                    posX = j / 2 * tailleCase + j / 2 * tailleBarriere;
                    posY = (i / 2 + 1) * tailleCase + i / 2 * tailleBarriere;
                }
                couleur = couleurBarriere;
            } else {
                continue;  // Ignorer les cases où i et j sont impairs
            }

            caseShape.setSize({largeur, hauteur});
            caseShape.setPosition(posX, posY);
            caseShape.setFillColor(couleur);
            cases[i][j] = caseShape;
        }
    }
}




        void VueSafari::initPionsPlateau(Plateau p) { // initialise les pions du plateau
           for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                        int posX = (j / 2) * (tailleCase + tailleBarriere);
                        int posY = (i / 2) * (tailleCase + tailleBarriere);
                        if(i%2==0 && j%2==0) Pions[i][j].init(posX, posY, cellSize, cellSize, pionVideTexture);
                } 
            }
        }
        

        void VueSafari::updatePionsVue(Plateau p) { //met à jour les pions du plateau
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if(i%2==0 && j%2==0){
                        CouleurPiece couleur = p.getGrille()[i][j].getPiece().getCouleurPiece();
                        setTexturePion(Pions[i][j], couleur);
                    }
                    else{
                        if(p.getGrille()[i][j].getPiece().getType() == "Barriere"){
                            cases[i][j].setFillColor(Color::Red);
                        }
                    }
                }
            }
        }  


        void VueSafari::draw(RenderWindow &window) { //dessine les pions du plateau
            VueGenerale::draw(window);
            window.draw(scoreboardBackground);
            window.draw(scoreText);
        }

        void VueSafari::setTexturePion(PionModel& pion, CouleurPiece couleur){ //change la texture du pion
            if(couleur == NOIR){
                pion.sprite.setTexture(pionNoirTexture);
            }
            else if(couleur == ROUGE){
                pion.sprite.setTexture(pionRougeTexture);
            }
            else if(couleur == JAUNE){
                pion.sprite.setTexture(pionJauneTexture);
            }
            else{
                pion.sprite.setTexture(pionVideTexture);
            }
        }