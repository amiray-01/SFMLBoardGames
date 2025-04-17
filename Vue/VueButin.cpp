#include "VueButin.hpp"

        VueButin::VueButin() : VueGenerale(8,75) { 
            Pions.resize(SIZE, vector<PionModel>(SIZE)); // On redimensionne le tableau à 2 dimensions
            vector<vector<PionModel>> Pions(SIZE, vector<PionModel>(SIZE)); 
            if (!pionNoirTexture.loadFromFile("Vue/ressources/pion_noir.png")) { // Remplacez par le chemin d'accès de votre image
                cout << "Erreur lors du chargement de l'image" << endl;
            }
            if (!pionJauneTexture.loadFromFile("Vue/ressources/pion_jaune.png")) { // Remplacez par le chemin d'accès de votre image
                cout << "Erreur lors du chargement de l'image" << endl;
            }
            if(!pionRougeTexture.loadFromFile("Vue/ressources/pion_rouge.png")){
                cout << "Erreur lors du chargement de l'image" << endl;
            }
            if(!pionBlancTexture.loadFromFile("Vue/ressources/trans.png")){
                cout << "Erreur lors du chargement de l'image" << endl;           
            }
            boutonPasser.initBouton(100, 50, 500, 650,"Passer");

        }


    
        void VueButin::setColorBoutonPasser(Color c){ //change la couleur du bouton passer
            boutonPasser.setColorBouton(c);
        }

        void VueButin::initPionsPlateau(Plateau p){ //initialise les pions du plateau
            Pions.resize(SIZE, std::vector<PionModel>(SIZE));
                for (int i = 0; i < SIZE; ++i) {
                    for (int j = 0; j < SIZE; ++j) {
                        if(p.getGrille()[i][j].getPiece().getCouleurPiece() == NOIR){ //si la case est noire
                            Pions[i][j].init(j * cellSize, i * cellSize, cellSize, cellSize, pionNoirTexture);
                        }
                        else if(p.getGrille()[i][j].getPiece().getCouleurPiece() == ROUGE){ //si la case est rouge
                            Pions[i][j].init(j * cellSize, i * cellSize, cellSize, cellSize, pionRougeTexture);
                        }
                        else if(p.getGrille()[i][j].getPiece().getCouleurPiece() == JAUNE){ //si la case est jaune
                            Pions[i][j].init(j * cellSize, i * cellSize, cellSize, cellSize, pionJauneTexture);
                        }
                        else{ //si la case est vide
                            Pions[i][j].init(j * cellSize, i * cellSize, cellSize, cellSize, pionBlancTexture);
                        }
                    }
                }
            }
        
        void VueButin::updatePionsVue(Plateau p) { //met à jour les pions du plateau
             for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    CouleurPiece couleur = p.getGrille()[i][j].getPiece().getCouleurPiece();
                    setTexturePion(Pions[i][j], couleur);
                }
            }
        }   

 
        void VueButin::draw(RenderWindow &window) { //dessine les pions du plateau
            VueGenerale::draw(window);
            window.draw(scoreboardBackground);
            window.draw(scoreText);
            window.draw(boutonPasser.bouton);
            window.draw(boutonPasser.textBouton);
        }

        void VueButin::setTexturePion(PionModel& pion, CouleurPiece couleur){ //change la texture du pion
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
                pion.sprite.setTexture(pionBlancTexture);
            }
        }

        RectangleShape VueButin::getBoutonPasser(){
            return boutonPasser.bouton;
        }

