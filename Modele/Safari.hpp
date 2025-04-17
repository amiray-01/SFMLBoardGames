#ifndef _SAFARI
#define _SAFARI

#include <set>
#include <queue>
#include "Jeu.hpp"
#include "Joueur.hpp"

class Safari : public Jeu {

public:
    Safari(); // Constructeur
    ~Safari() override = default; // Destructeur
    Safari(const Safari& autre) = delete; // Supprimer le constructeur de copie
    Safari& operator=(const Safari& autre) = delete; // Supprimer l'opérateur d'assignation

    bool estFinJeu(Plateau &plateau) const override; // Vérifier si la variante Safari est terminée

    bool peutPoserPion(int i,int j,Plateau& plateau) const;                 // Vérifier si un pion peut être posé
    bool peutSauter(int x1, int y1, int x2, int y2,const Plateau& plateau) const override; // Vérifier si un déplacement est possible
    bool deplacerPiece(int x1, int y1, int x2, int y2,Plateau& plateau) override; // Déplacer une pièce
    bool placerBarriere(int x, int y);                                     // Placer une barrière
    bool estPerdant(int idJoueur) const;                                    // Vérifier si un joueur est perdant
    void initialiserJoueursActifs(const vector<Joueur>& joueursDepart);     // Initialiser la liste des joueurs actifs
    const vector<Joueur>& getJoueursActifs() const; 

private:
    mutable vector<int> joueursDepart;                                          // Liste des joueurs de départ
    mutable vector <Joueur> joueursActifs;                                      // Liste des joueurs encore en jeu
    bool caseValidePourAnimal(int x, int y) const;                              // Vérifier si une case est valide pour un animal
    bool cheminBloqueParBarriere(int x1, int y1, int x2, int y2) const;         // Vérifier si un chemin est bloqué par une barrière
    bool caseValidePourBarriere(int x, int y);                                  // Vérifier si une case est valide pour une barrière
    bool zoneDeMoinsDeHuitCases(int x, int y);                                  // Vérifier si l'animal (x,y) est dans une zone de moins de huit cases
    bool barriereEntre(int x1, int y1, int x2, int y2) const;                   // Vérifier si une barrière est entre deux cases
    bool positionValide(int x, int y) const;                                    // Vérifier si une position est valide
};

#endif