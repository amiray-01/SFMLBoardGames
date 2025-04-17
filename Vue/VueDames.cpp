#include "VueDames.hpp"


        VueDames::VueDames() : VueGenerale(10,60) { 
            Pions.resize(SIZE, vector<PionModel>(SIZE));
            vector<vector<PionModel>> Pions(SIZE, vector<PionModel>(SIZE));
            if (!pionNoirTexture.loadFromFile("Vue/ressources/pion_noir.png")) { // Remplacez par le chemin d'accès de votre image
                cout << "Erreur lors du chargement de l'image" << endl;
            }
            if( !pionRougeTexture.loadFromFile("Vue/ressources/pion_rouge.png")){
                cout << "Erreur lors du chargement de l'image" << endl;
            }
            if(!pionVideTexture.loadFromFile("Vue/ressources/trans.png")){
                cout << "Erreur lors du chargement de l'image" << endl;           
            }
            if(!pionRougeDameTexture.loadFromFile("Vue/ressources/pion_r_dame.png")){
                cout << "Erreur lors du chargement de l'image" << endl;           
            }
            if(!pionNoirDameTexture.loadFromFile("Vue/ressources/pion_n_dame.png")){
                cout << "Erreur lors du chargement de l'image" << endl;           
            }

            boutonFF.initBouton(200, 50, 480, 650,"Abandonner"); //initialise le bouton abandonner

        }

    
        void VueDames::setColorBoutonFF(Color c){ //change la couleur du bouton abandonner
            boutonFF.setColorBouton(c);
        }

        void VueDames::initPionsPlateau(Plateau p) { //initialise les pions du plateau
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if (p.getGrille()[i][j].getPiece().getCouleurPiece() == NOIR) { //si la case est noire
                        Pions[i][j].init(j * cellSize, i * cellSize, cellSize, cellSize, pionNoirTexture);
                    }
                    else if (p.getGrille()[i][j].getPiece().getCouleurPiece() == ROUGE) { //si la case est rouge
                        Pions[i][j].init(j * cellSize, i * cellSize, cellSize, cellSize, pionRougeTexture);
                    }
                    else { //si la case est vide
                        Pions[i][j].init(j * cellSize, i * cellSize, cellSize, cellSize, pionVideTexture);
                    }
                }   
            }
        }

        void VueDames::updatePionsVue(Plateau p) { //met à jour les pions du plateau
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    CouleurPiece couleur = p.getGrille()[i][j].getPiece().getCouleurPiece();
                    if(p.getGrille()[i][j].getPiece().getType() == "Dame"){
                        setTextureDame(Pions[i][j], couleur);
                    }
                    else{
                        setTexturePion(Pions[i][j], couleur);
                    }
                }
            }
        }   


        void VueDames::draw(RenderWindow &window) { //dessine les pions du plateau
            VueGenerale::draw(window);
            window.draw(scoreboardBackground);
            window.draw(scoreText);
            window.draw(boutonFF.bouton);
            window.draw(boutonFF.textBouton);
        }

        void VueDames::setTexturePion(PionModel& pion, CouleurPiece couleur){ //change la texture du pion
            if(couleur == NOIR){
                pion.sprite.setTexture(pionNoirTexture);
            }
            else if(couleur == ROUGE){
                pion.sprite.setTexture(pionRougeTexture);
            }
            else{
                pion.sprite.setTexture(pionVideTexture);
            }
        }
        
        void VueDames::setTextureDame(PionModel& pion, CouleurPiece couleur){ //change la texture de la dame
            if(couleur == NOIR){
                pion.sprite.setTexture(pionNoirDameTexture);
            }
            else if(couleur == ROUGE){
                pion.sprite.setTexture(pionRougeDameTexture);
            }
        }

        RectangleShape VueDames::getBoutonFF(){
            return boutonFF.bouton;
        }
