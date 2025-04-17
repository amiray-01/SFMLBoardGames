#include "ControleurButin.hpp"



    ControleurButin::ControleurButin(sf::RenderWindow& window,int nbJoueurs) : BaseControleur(window, vue, model,nbJoueurs){
        vue.initPlateau();
        vue.initPionsPlateau(model.getPlateau());
        for(int i = 0; i < nbJoueurs; i++){
            model.ajoutJoueur();
        }
        tour = 1;
    }

    bool ControleurButin::premiereSelection(int i,int j){ //retourne true si la selection est valide
        if (vue.getCouleurPiece(i,j,model.getPlateau()) == JAUNE) {
            BaseControleur::premiereSelection(i,j);
            return true;
        }
        return false;
    }

    bool ControleurButin::deuxiemeSelection(int i,int j){ //retourne true si le deplacement est valide
        bool reussi = false;
        vue.getPion(pionSelectionneX,pionSelectionneY).updateScale(1.0f); 
        if (pionSelectionneX != i || pionSelectionneY != j) {
            // Mise à jour des positions des pions dans le tableau
            if(model.peutSauter(pionSelectionneX,pionSelectionneY,i,j,model.getPlateau())){ //si le pion peut sauter
                int xMilieu = (i+pionSelectionneX)/2; //calcul des coordonnées du pion pris
                int yMilieu = (j+pionSelectionneY)/2;
                model.ajouterPiecePrise(xMilieu,yMilieu); //ajout du pion pris dans la liste des pions pris
                prise(i,j,xMilieu,yMilieu); //met à jour la vue
                model.deplacerPiece(pionSelectionneX,pionSelectionneY,i,j,model.getPlateau()); //met à jour le plateau
                vue.updatePionsVue(model.getPlateau()); //met à jour la vue
                model.mettreAJourScore(xMilieu,yMilieu); //met à jour le score
                reussi = true;
            }
            else{
                reussi = false;
            } 
        }
        return reussi;
    }
    
    
    bool ControleurButin::removePion(int i,int j){ //retourne true si le pion a bien été supprimé
        if (vue.getCouleurPiece(i,j,model.getPlateau()) == JAUNE) {
            model.deplacerPiece(i,j,-1,-1,model.getPlateau()); //met à jour le plateau
            vue.updatePionsVue(model.getPlateau()); //met à jour la vue
            return true;
            }
        return false;
    }

    void ControleurButin::handleBoutonPasser(){
        model.updateModel(); //met à jour le modèle
        vue.updatePionsVue(model.getPlateau()); //met à jour la vue
        vue.setColorBoutonPasser(sf::Color(200, 200, 200)); //met à jour la couleur du bouton
        boutonActive = true;
        clock.restart(); //redémarre le chrono
        reset(pionSelectionneX,pionSelectionneY); //réinitialise la sélection
        lastPlayer = model.getJoueurActuel(); //met à jour le dernier joueur
        model.getPiecesPrises().clear(); //vide la liste des pions pris
        model.passerAuProchainJoueur(); //passe au prochain joueur
    }

    void ControleurButin::updateBouton() {
    if (boutonActive) { // si le bouton est actif
        if (clock.getElapsedTime().asSeconds() > 0.05) { // Un délai de 0.1 seconde
            vue.setColorBoutonPasser(sf::Color::White); // Couleur originale
            boutonActive = false;
            }
        }
    }

    void ControleurButin::handleGame(Event event, RenderWindow &window, VueButin &vue){ //gère la partie

        BaseControleur::handleTour(); //gère le tour

        updateScoreboard(); //met à jour le scoreboard

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
            if (vue.getBoutonPasser().getGlobalBounds().contains(mousePos) && nbSauts > 0 && model.peutEncoreSauter(pionSelectionneX,pionSelectionneY)) { //si le bouton passer est cliqué
                handleBoutonPasser(); //gère le bouton passer
            }
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (vue.getPion(i, j).shape.getGlobalBounds().contains(mousePos)){ //si un pion est cliqué
                        if(tour==1){ //si c'est le premier tour
                            if(removePion(i,j)){  //si le pion a bien été supprimé
                                if(!isSelected){
                                    lastPlayer = model.getJoueurActuel(); //met à jour le dernier joueur
                                    model.passerAuProchainJoueur(); //passe au prochain joueur
                                    hasPlayed++;  //incrémente le nombre de joueurs ayant joué
                                }   
                            }
                        }
                        else{
                            if(!isSelected){ //si aucun pion n'est sélectionné
                                premiereSelection(i,j); //gère la première sélection
                            }
                            else{
                                if(deuxiemeSelection(i,j)){ //gère la deuxième sélection
                                    if(nbSauts > 0 && model.peutEncoreSauter(i,j)){ //si le pion peut encore sauter
                                        premiereSelection(i,j); //on le remet à la position du pion sélectionné
                                    }
                                    else{
                                        vue.clearOpacity(model.getPiecesPrises()); //met à jour la vue (enlenve l'opacité des pions pris)
                                        model.updateModel(); //met à jour le modèle
                                        vue.updatePionsVue(model.getPlateau()); //met à jour la vue
                                        reset(i,j); //réinitialise la sélection
                                        lastPlayer = model.getJoueurActuel(); //met à jour le dernier joueur
                                        model.getPiecesPrises().clear(); //vide la liste des pions pris
                                        model.passerAuProchainJoueur(); //passe au prochain joueur
                                        hasPlayed++; //incrémente le nombre de joueurs ayant joué
                                    }
                                }
                                else if(nbSauts > 0){ //si le pion peut encore sauter
                                    premiereSelection(pionSelectionneX,pionSelectionneY); //on le remet à la position du pion sélectionné
                                }
                                else{
                                    reset(i,j); //réinitialise la sélection
                                }
                            }
                        }
                    }
                }
            }
        }
        updateBouton(); //animation du bouton
    }

    void ControleurButin::handleEndGame(){ //gère la fin de partie
        model.setJoueurActuel(lastPlayer); //met à jour le dernier joueur
        model.calculerScoreFinal(); //calcule le score final
        ostringstream oss;
        for (int i = 1; i <= model.getListeJoueurs().size(); ++i) { //affiche le scoreboard
            Joueur& joueur = model.getJoueur(i);
            if(i == model.getListeJoueurs().size()){
                oss << "Joueur " << i << " : " << joueur.getScore() << endl;
            }
            else{
            oss << "Joueur " << i << " : " << joueur.getScore() << " | ";
            }
        }
        oss << "VICTOIRE DU JOUEUR  " << model.getIdWinner()  << endl;
        oss << " FIN DE JEU " << endl;
        vue.setScoreboard(oss.str());
    }

        void ControleurButin::run() {
            while (window.isOpen()) { //boucle principale
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) window.close(); //ferme la fenêtre
                    if(!endgame){ //si la partie n'est pas terminée
                        handleGame(event,window, vue); //gère la partie
                    }
                }
                if(model.estFinJeu(model.getPlateau()) && tour > 1){ //si la partie est terminée
                    endgame = true;
                    handleEndGame(); //gère la fin de partie
                    tour = 0;
                }
                window.clear();
                vue.draw(window);
                window.display();
            }
        }