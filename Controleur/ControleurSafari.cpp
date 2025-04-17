#include "ControleurSafari.hpp"



    ControleurSafari::ControleurSafari(RenderWindow& window,int nbJoueurs) : BaseControleur(window, vue,model,nbJoueurs),nbPionsPose{0}, nbCoups{0}{
        vue.initPlateau();
        vue.initPionsPlateau(model.getPlateau());
        for(int i = 0; i < nbJoueurs; i++){
            model.ajoutJoueur();
        }
        model.initialiserJoueursActifs(model.getListeJoueurs()); //initialise la liste des joueurs actifs
    }

    bool ControleurSafari::poserPion(int i,int j){ //retourne true si le pion a été posé
        if (model.peutPoserPion(i,j,model.getPlateau())){ //si le pion peut être posé
            return true;
        }
        return false;
    }

     bool ControleurSafari::placerBarriere(int i,int j){ //retourne true si la barriere a été posée
        if (model.placerBarriere(i,j)){ //si la barriere peut être posée
            return true;
        }
        return false;
    }

    bool ControleurSafari::premiereSelection(int i,int j){ //retourne true si la selection est valide
        if ((vue.getCouleurPiece(i,j,model.getPlateau()) == model.getJoueurActuel()-1)) { //si le pion appartient au joueur actuel
            BaseControleur::premiereSelection(i,j); //met à jour les coordonnées du pion sélectionné
            return true;
        }
        return false;
    }

    bool ControleurSafari::deuxiemeSelection(int i,int j){ //retourne true si le deplacement est valide
        bool reussi = false;
        vue.getPion(pionSelectionneX,pionSelectionneY).updateScale(1.0f); 
        if (pionSelectionneX != i || pionSelectionneY != j) { //si le pion n'est pas resté sur place
            if(model.peutSauter(pionSelectionneX,pionSelectionneY,i,j,model.getPlateau())){ //si le pion peut sauter
                model.deplacerPiece(pionSelectionneX,pionSelectionneY,i,j,model.getPlateau()); //met à jour le plateau
                vue.updatePionsVue(model.getPlateau()); //met à jour la vue
                reussi = true;
            }
            else{
                reussi = false;
            } 
        }
        return reussi;
    }

    void ControleurSafari::gestionTourUn(int i,int j){ //gère le premier tour
        if(poserPion(i,j)){ //si le pion peut être posé
                nbPionsPose++;
        }
        if(nbPionsPose==3){ //si le joueur a posé un pion
            nbPionsPose = 0;
            hasPlayed++;
            model.passerAuProchainJoueur();
        }
        vue.updatePionsVue(model.getPlateau());
    }

    void ControleurSafari::handleGame(Event event, RenderWindow& window, VueSafari& vue){ //gère la partie
        if(model.estPerdant(model.getJoueurActuel()-1)) {model.passerAuProchainJoueur();hasPlayed++;} //si le joueur actuel est perdant, on passe au joueur suivant
        BaseControleur::handleTour(); //gère le tour
        updateScoreboard();

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){ //si le joueur clique
            Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
            for (int i = 0; i < 15; ++i) {
                for (int j = 0; j < 15; ++j){
                    if(vue.getCase(i,j).getGlobalBounds().contains(mousePos)){ //si une case est cliquée
                        if(tour==1) gestionTourUn(i,j); //si c'est le premier tour
                        else{
                            if(nbCoups==0){ //si c'est le premier coup du joueur
                                if(!isSelected){ //si aucun pion n'est sélectionné
                                    premiereSelection(i,j); //gère la première sélection
                                }
                                else{
                                    if(deuxiemeSelection(i,j)){ //gère la deuxième sélection
                                            vue.updatePionsVue(model.getPlateau()); //met à jour la vue
                                            reset(i,j); //réinitialise la sélection
                                            nbCoups++; //incrémente le nombre de coups joués
                                    } 
                                    else{
                                        reset(i,j);
                                    }
                                }
                            }  
                            else{ //si c'est le deuxième coup du joueur
                                if(placerBarriere(i,j)){  //si la barriere peut être posée
                                    nbCoups = 0; //réinitialise le nombre de coups joués
                                    hasPlayed++; //incrémente le nombre de joueurs ayant joué
                                    lastPlayer = model.getJoueurActuel(); //met à jour le dernier joueur
                                    model.passerAuProchainJoueur(); //passe au prochain joueur
                                    vue.updatePionsVue(model.getPlateau()); //met à jour la vue
                                }
                            }                 
                        }
                    }
                }
            }
        }
            
    }

    void ControleurSafari::handleEndGame(){ //gère la fin de partie
        model.setJoueurActuel(lastPlayer);
        ostringstream oss;
        for (int i = 1; i <= model.getListeJoueurs().size(); ++i) { //met à jour le scoreboard
            Joueur& joueur = model.getJoueur(i);
            if(i == model.getListeJoueurs().size()){
                oss << "Joueur " << i << " : " << joueur.getScore() << endl;
            }
            else{
            oss << "Joueur " << i << " : " << joueur.getScore() << " | ";
            }
        }
        oss << "VICTOIRE DU JOUEUR  " << model.getJoueursActifs()[0].getId()+1  << endl;
        oss << " FIN DE JEU " << endl;
        vue.setScoreboard(oss.str());
    }

    void ControleurSafari::run() {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) { //boucle principale
                if(event.type == Event::Closed) window.close(); //ferme la fenêtre
                if(!endgame) handleGame(event, window, vue); //gère la partie
            }
            if(tour > 1 && model.estFinJeu(model.getPlateau())){ //si la partie est terminée
                handleEndGame(); //gère la fin de partie
            }
            window.clear();
            vue.draw(window);
            window.display();
    }
}