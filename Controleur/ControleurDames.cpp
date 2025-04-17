#include "ControleurDames.hpp"

ControleurDames::ControleurDames(RenderWindow& window,int nbJoueurs) : BaseControleur(window, vue, model,nbJoueurs) {
    vue.initPlateau();
    vue.initPionsPlateau(model.getPlateau());
    for(int i = 0; i < nbJoueurs; i++){
            model.ajoutJoueur();
    }
    lastPlayer = 2;
    tour = 1;
}

bool ControleurDames::premiereSelection(int i,int j){ //retourne true si la selection est valide
    if ((vue.getCouleurPiece(i,j,model.getPlateau()) == model.getJoueurActuel())) { //si la piece selectionnée est de la couleur du joueur actuel
        if(model.peutFaireUnePrise(vue.getCouleurPiece(i,j,model.getPlateau()),model.getPlateau())){ //si le joueur peut faire une prise
            if(model.prisePossible(i,j, model.getPlateau())){ //si le pion selectionné peut faire une prise
                BaseControleur::premiereSelection(i,j);
                return true;
            }
            else{
                return false;
            }
        }
        else{
            BaseControleur::premiereSelection(i,j);
            return true;
        }
    }
    return false;
}

bool ControleurDames::deuxiemeSelection(int i,int j){ //retourne true si le deplacement est valide
    bool reussi = false;
    vue.getPion(pionSelectionneX,pionSelectionneY).updateScale(1.0f);
    if (pionSelectionneX != i || pionSelectionneY != j) { //si le pion n'est pas selectionné sur lui même
        if(model.prisePossible(pionSelectionneX,pionSelectionneY,model.getPlateau())){ //si une prise est possible depuis la position du pion selectionné
            if(model.estPriseValide(pionSelectionneX,pionSelectionneY,i,j,model.getPlateau())){ //si la prise est valide
                if(model.getPlateau().getCase(pionSelectionneX,pionSelectionneY).getPiece().getType() == "Dame"){ //si le pion est une dame
                    reussi = model.effectuerPrise(pionSelectionneX,pionSelectionneY,i,j,model.getPlateau()); //met à jour le plateau
                    model.getJoueur(model.getJoueurActuel()).ajouterScore(1); //met à jour le score
                    nbSauts++;
                }
                else{
                if(cheminsOptimaux.size()>1){ //si il y a plusieurs chemins optimaux
                    pair<int,int> p = {i,j}; //on vérifie si la prise est dans un chemin optimal
                    for (const vector<pair<int, int>>& chemin : cheminsOptimaux) {
                        if (find(chemin.begin(), chemin.end(), p) != chemin.end()) {
                            reussi = model.effectuerPrise(pionSelectionneX,pionSelectionneY,i,j,model.getPlateau());
                            model.getJoueur(model.getJoueurActuel()).ajouterScore(1);
                            prise(i,j,(i+pionSelectionneX)/2,(j+pionSelectionneY)/2);
                            break;
                        }
                    }
                }
                else{
                    if(cheminChoisi == -1){ 
                    for(int k=0;k<cheminsOptimaux.size();k++){ //on défini quel chemin est choisi
                        if(cheminsOptimaux[k][0].first == i && cheminsOptimaux[k][0].second == j){
                            cheminChoisi = k;
                            break;
                        }
                    }
                    if(cheminChoisi == -1){ //si la prise n'est pas dans un chemin optimal
                        reussi = false;
                    }
                    else{
                        prise(i,j,(i+pionSelectionneX)/2,(j+pionSelectionneY)/2); //met à jour la vue
                        reussi = model.effectuerPrise(pionSelectionneX,pionSelectionneY,i,j,model.getPlateau()); //met à jour le plateau
                        model.getJoueur(model.getJoueurActuel()).ajouterScore(1); //met à jour le score
                        cheminsOptimaux[cheminChoisi].erase(cheminsOptimaux[cheminChoisi].begin()); //on supprime le chemin choisi
                    }
                }
                else{
                    if(cheminsOptimaux[cheminChoisi][0].first != i || cheminsOptimaux[cheminChoisi][0].second != j){ //si la prise n'est pas dans un chemin optimal
                        reussi = false;
                    }
                    else{
                        prise(i,j,(i+pionSelectionneX)/2,(j+pionSelectionneY)/2); //met à jour la vue
                        reussi = model.effectuerPrise(pionSelectionneX,pionSelectionneY,i,j,model.getPlateau()); //met à jour le plateau
                        model.getJoueur(model.getJoueurActuel()).ajouterScore(1); //met à jour le score
                        cheminsOptimaux[cheminChoisi].erase(cheminsOptimaux[cheminChoisi].begin()); //on supprime le chemin choisi
                    }
                }
                }
                }
            }
            else reussi = false;
        }
        else if(!model.prisePossible(pionSelectionneX,pionSelectionneY,model.getPlateau()) && model.peutSauter(pionSelectionneX,pionSelectionneY,i,j,model.getPlateau())){ //si une prise n'est pas possible depuis la position du pion selectionné mais qu'il peut sauter
            reussi = model.deplacerPiece(pionSelectionneX,pionSelectionneY,i,j,model.getPlateau()); //met à jour le plateau
        }
        else{
            reussi = false;
        }
    }
    else{
        reussi = false;
    }
    vue.updatePionsVue(model.getPlateau()); //met à jour la vue
    return reussi;
}

void ControleurDames::resetChemin(){ //réinitialise le chemin choisi
    cheminsOptimaux.clear();
    prises.clear();
    cheminChoisi = -1;
}

void ControleurDames::handleBoutonFF(){ //gère le bouton d'abandon
    endgame = true;
    vue.setColorBoutonFF(Color(200, 200, 200));
    boutonActive = true;
    clock.restart();
}

void ControleurDames::updateBouton() { //animation du bouton d'abandon
    if (boutonActive) {
        if (clock.getElapsedTime().asSeconds() > 0.05) { // Un délai de 0.1 seconde
            vue.setColorBoutonFF(Color::White); // Couleur originale
            boutonActive = false;
            }
        }
    }

void ControleurDames::handleGame(Event event, RenderWindow& window, VueDames& vue){ //gère la partie
    BaseControleur::handleTour(); //gère le tour

    updateScoreboard(); //met à jour le scoreboard
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){
        Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
        if (vue.getBoutonFF().getGlobalBounds().contains(mousePos)) { //si le bouton d'abandon est cliqué
            handleBoutonFF(); //gère le bouton d'abandon
        }
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (vue.getPion(i, j).shape.getGlobalBounds().contains(mousePos)){ //si un pion est cliqué
                    if(!isSelected){ //si aucun pion n'est selectionné
                        if(premiereSelection(i,j)){ //si la première sélection est valide
                            if(model.prisePossible(i,j, model.getPlateau())){ //si le pion selectionné peut faire une prise
                                int max = 0;
                                if(model.getPlateau().getCase(i,j).getPiece().getType() == "Pion"){
                                    model.maxSautsDepuisPosition(i,j,model.getPlateau(),prises,cheminsOptimaux,max,false);
                                }
                                model.getPiecesPrises().clear(); //vide la liste des pions pris
                            }
                        }
                    }
                    else{
                       if(deuxiemeSelection(i,j)){ //si la deuxième sélection est valide
                            if(nbSauts > 0 && model.prisePossible(i,j,model.getPlateau())){ //si le pion peut encore effectuer une prise
                                premiereSelection(i,j); //gère la première sélection
                            }
                            else{
                                model.couronnerPion(i,j,model.getPlateau()); //on test si le pion peut devenir une dame
                                vue.clearOpacity(model.getPiecesPrises()); //on réinitialise l'opacité des pions pris
                                model.updateModel(); //met à jour le modèle
                                vue.updatePionsVue(model.getPlateau()); //met à jour la vue
                                reset(i,j); //réinitialise la sélection
                                resetChemin(); //réinitialise le chemin choisi
                                lastPlayer = model.getJoueurActuel(); //met à jour le dernier joueur
                                model.getPiecesPrises().clear(); //vide la liste des pions pris
                                hasPlayed++; //incrémente le nombre de joueurs ayant joué
                                model.passerAuProchainJoueur(); //passe au prochain joueur
                            }
                        }
                        else if(nbSauts > 0){ //si le pion peut encore effectuer une prise
                            premiereSelection(pionSelectionneX,pionSelectionneY); //gère la première sélection
                        }
                        else{
                            reset(i,j); //réinitialise la sélection
                        }
                    }
                }
            }
        }
    }
    updateBouton(); //met à jour le bouton d'abandon
}

    void ControleurDames::handleEndGame(){ //gère la fin de partie
        model.setJoueurActuel(lastPlayer); //met à jour le dernier joueur
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
        oss << "VICTOIRE DU JOUEUR  " << lastPlayer  << endl;
        oss << " FIN DE JEU " << endl;
        vue.setScoreboard(oss.str());
    }

void ControleurDames::run() {
    while (window.isOpen()) { //boucle principale
        Event event;
        while (window.pollEvent(event)) { 
            if(event.type == Event::Closed) window.close(); //ferme la fenêtre
            if(!endgame) handleGame(event, window, vue); //gère la partie
            else handleEndGame(); //gère la fin de partie
        }
        if(!endgame && model.estFinJeu(model.getPlateau())){ //si la partie est terminée
            endgame = true; 
            handleEndGame(); //gère la fin de partie
        }
        window.clear();
        vue.draw(window);
        window.display();
    }
}
