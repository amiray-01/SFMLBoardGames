#ifndef _JOUEUR
#define _JOUEUR

#include <string>
#include <vector>
using namespace std;

class Joueur {
private:
    static int nbJoueurs;
    int id;
    int score;

public:
    Joueur();
    Joueur(const Joueur& j);
    void ajouterScore(int points);
    int getId() const;
    int getScore() const;
};

#endif
