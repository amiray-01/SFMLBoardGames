#ifndef _BUTIN
#define _BUTIN

#include "Jeu.hpp"
#include "Joueur.hpp"

class Butin : public Jeu {

public:
    Butin(); // Constructeur
    ~Butin() override = default; // Destructeur
    Butin(const Butin& autre) = delete; // Supprimer le constructeur de copie
    Butin& operator=(const Butin& autre) = delete; // Supprimer l'opérateur d'assignation
   
    bool estFinJeu(Plateau &plateau) const override; // Vérifier si la variante Butin est terminée
    bool peutSauter(int x1, int y1, int x2, int y2,const Plateau& plateau) const override; // Vérifier si un pion peut sauter
    bool deplacerPiece(int x1, int y1, int x2, int y2,Plateau& plateau) override; // Déplacer un pion
    void updateModel(); // Mettre à jour le modèle
    bool peutEncoreSauter(int x, int y) const; // Vérifier si un pion peut encore sauter
    void mettreAJourScore(int x, int y); // Mettre à jour le score
    void calculerScoreFinal(); // Calculer le score final
    int getIdWinner(); // Obtenir l'ID du gagnant
};

#endif