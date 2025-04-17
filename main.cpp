#include <iostream>
#include "Controleur/ControleurDames.hpp"
#include "Controleur/ControleurButin.hpp"
#include "Controleur/ControleurSafari.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {
    int choixJeu, nombreJoueurs;
    bool continuer = true;
    RenderWindow window(sf::VideoMode(600, 700), "Jeu de dames et Variantes", sf::Style::Titlebar | sf::Style::Close);

    while (continuer) {
        cout << "Bienvenue dans notre collection de jeux de plateau!" << endl;
        cout << "Veuillez choisir un jeu:" << endl;
        cout << "1. Dames" << endl;
        cout << "2. Butin" << endl;
        cout << "3. Safari" << endl;
        cout << "4. Quitter" << endl;

        if (!(cin >> choixJeu)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrée invalide. Veuillez essayer à nouveau." << endl;
            continue;
        }

        switch (choixJeu) {
            case 1: {
                ControleurDames controleurDames{window, 2};
                controleurDames.run();
                if (!window.isOpen()) {
                    return 0; // Quitte le programme si la fenêtre est fermée
                }
                break;
            }
            case 2:
            case 3: {
                cout << "Choisir le nombre de joueurs (2 ou 3): ";
                if (!(cin >> nombreJoueurs)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Entrée invalide. Veuillez choisir un nombre." << endl;
                    break;
                }
                if (nombreJoueurs != 2 && nombreJoueurs != 3) {
                    cout << "Nombre de joueurs invalide. Veuillez choisir à nouveau." << endl;
                    break;
                }

                if (choixJeu == 2) {
                    ControleurButin controleurButin{window, nombreJoueurs};
                    controleurButin.run();
                } else {
                    ControleurSafari controleurSafari{window, nombreJoueurs};
                    controleurSafari.run();
                }
                if (!window.isOpen()) {
                    return 0; // Quitte le programme si la fenêtre est fermée
                }
                break;
            }
            case 4:
                return 0; // Quitte le programme directement
            default:
                cout << "Choix invalide. Veuillez choisir à nouveau." << endl;
        }
    }

    return 0;
}
