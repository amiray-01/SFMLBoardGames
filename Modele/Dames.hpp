#ifndef _DAMES
#define _DAMES

#include "Jeu.hpp"
#include "Joueur.hpp"

class Dames : public Jeu {

public:
    Dames(); // Constructeur
    ~Dames() override = default; // Destructeur
    Dames(const Dames& autre) = delete; // Supprimer le constructeur de copie
    Dames& operator=(const Dames& autre) = delete; // Supprimer l'opérateur d'assignation
    
    bool estFinJeu(Plateau &plateau) const override; // Vérifier si la variante Dames est terminée

    void maxSautsDepuisPosition(int x, int y, Plateau& plateau, vector<pair<int,                // Nombre de prise maximale depuis une position
                                int>>& prises, vector<vector<pair<int, int>>>& cheminsOptimaux, 
                                int& maxPrises,bool isDame);    
    bool peutSauter(int x1, int y1, int x2, int y2,const Plateau& plateau) const override;  // Vérifier si un déplacement est possible
    bool estPriseValide(int x1, int y1, int x2, int y2,Plateau& plateau) const;             // Vérifier si une prise est valide
    bool deplacerPiece(int x1, int y1, int x2, int y2,Plateau& plateau) override;           // Déplacer une pièce
    bool effectuerPrise(int x1, int y1, int x2, int y2,Plateau& plateau);                   // Effectuer une prise
    void couronnerPion(int x, int y,Plateau& plateau);                                      // Couronner un pion
    void updateModel();                                                                     // Mettre à jour le modèle
    bool aucunMouvementPossible(Plateau &plateau) const;                                    // Vérifier si aucun mouvement n'est possible
    bool plusDePieces() const;                                                              // Vérifier si un joueur n'a plus de pièces
    bool prisePossible(int x, int y,Plateau &plateau) const;                                // Vérifier si une prise est possible
    bool peutFaireUnePrise(CouleurPiece couleurJoueur,Plateau& plateau) const;              // Vérifier si une prise est possible pour un joueur

private:
    bool peutSauterPion(int x1, int y1, int x2, int y2,const Plateau& plateau) const;       // Vérifier si un pion peut se déplacer
    bool peutSauterDames(int x1, int y1, int x2, int y2,const Plateau& plateau) const;      // Vérifier si une dame peut se déplacer
    bool estPriseValidePion(int x1, int y1, int x2, int y2,Plateau& plateau) const;         // Vérifier si une prise de pion est valide 
    bool estPriseValideDames(int x1, int y1, int x2, int y2,Plateau& plateau) const;        // Vérifier si une prise de dame est valide
    bool prisePionPossible(int x, int y, int couleur,Plateau& plateau) const;               // Vérifier si une prise de pion est possible à partir d'une position
    bool priseDamePossible(int x, int y,Plateau& plateau) const;                            // Vérifier si une prise de dame est possible à partir d'une position
};

#endif