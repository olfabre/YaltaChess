#pragma once

#include <SFML/System/Vector2.hpp>
#include <string>
#include <map>
#include <vector>
#include "Couleur.h"

using namespace sf;
using namespace std;

// Structure pour les coordonnées cubiques hexagonales
struct Cube { int x, y, z; };

// Classe utilitaire pour la conversion des coordonnées dans un échiquier Yalta à 3 joueurs
namespace YaltaCoords {

    // Énumération des directions de mouvement
    enum Direction {
        FORWARD,  // Vers le centre de l'échiquier
        BACKWARD, // Vers l'extérieur de l'échiquier
        LEFT,     // Vers la gauche par rapport à la perspective du joueur
        RIGHT     // Vers la droite par rapport à la perspective du joueur
    };

    // Conversion d'une notation algébrique (ex: "a1", "l7") vers des coordonnées de grille (x,y)
    inline Vector2i algebraicToGrid(const string& algPos) {
        // Vérification de la validité de la notation algébrique
        if (algPos.length() < 2) return Vector2i(-1, -1);

        char file = algPos[0];
        int rank = stoi(algPos.substr(1));

        // Conversion de la colonne (a-l) en index (0-11)
        int col = file - 'a';
        if (col < 0 || col > 11) return Vector2i(-1, -1);

        // Conversion du rang (1-12) en coordonnées selon la zone
        if (rank >= 1 && rank <= 4) {
            // Zone blanche (bas)
            return Vector2i(col, 12 - rank);
        } else if (rank >= 5 && rank <= 8) {
            if (file >= 'a' && file <= 'd') {
                // Zone rouge intérieure (gauche)
                return Vector2i(3 - (file - 'a'), 14 - rank);
            } else if (file >= 'e' && file <= 'h') {
                // Zone noire intérieure (droite)
                return Vector2i(col, 12 - rank);
            } else if (file >= 'i' && file <= 'l') {
                // Zone rouge extérieure (gauche)
                return Vector2i(file - 'i', 12 - rank);
            }
        } else if (rank >= 9 && rank <= 12) {
            // Zone noire (droite)
            return Vector2i(col, 12 - rank);
        }

        return Vector2i(-1, -1); // Position invalide
    }

    // Conversion des coordonnées de grille (x,y) vers une notation algébrique
    inline string gridToAlgebraic(const Vector2i& gridPos) {
        int x = gridPos.x;
        int y = gridPos.y;

        // Vérification des limites
        if (x < 0 || x > 11 || y < 0 || y > 11) {
            return "(" + to_string(x) + "," + to_string(y) + ")";
        }

        // Détermination de la zone (blanche, rouge, noire)
        if (y >= 8) {
            // Zone blanche (bas)
            char file = 'a' + x;
            int rank = 12 - y;
            return string(1, file) + to_string(rank);
        } else if (x < 4) {
            // Zone rouge (gauche)
            if (y == 7) {
                // Rangée intérieure 8
                char file = 'a' + (3 - x);
                return string(1, file) + "8";
            } else if (y == 6) {
                // Rangée intérieure 7
                char file = 'a' + (3 - x);
                return string(1, file) + "7";
            } else if (y == 5) {
                // Rangée extérieure 7
                char file = 'i' + x;
                return string(1, file) + "7";
            } else if (y == 4) {
                // Rangée extérieure 8
                char file = 'i' + x;
                return string(1, file) + "8";
            } else if (y == 3) {
                // Rangée intérieure 6
                char file = 'a' + (3 - x);
                return string(1, file) + "6";
            } else if (y == 2) {
                // Rangée intérieure 5
                char file = 'a' + (3 - x);
                return string(1, file) + "5";
            } else if (y == 1) {
                // Rangée extérieure 6
                char file = 'i' + x;
                return string(1, file) + "6";
            } else if (y == 0) {
                // Rangée extérieure 5
                char file = 'i' + x;
                return string(1, file) + "5";
            }
        } else {
            // Zone noire (droite)
            char file = 'a' + x;
            int rank = 12 - y;
            return string(1, file) + to_string(rank);
        }

        return "(" + to_string(x) + "," + to_string(y) + ")";
    }

    // Conversion des coordonnées de grille (x,y) vers des coordonnées cubiques
    inline Cube gridToCube(const Vector2i& g) {
        // Basé sur la conversion "offset odd-r" standard pour les hexagones
        int q = g.x - (g.y - (g.y & 1)) / 2;
        int r = g.y;
        int x = q;
        int z = r;
        int y = -x - z;
        return {x, y, z};
    }

    // Conversion des coordonnées cubiques vers des coordonnées de grille (x,y)
    inline Vector2i cubeToGrid(const Cube& c) {
        int q = c.x;
        int r = c.z;
        int col = q + (r - (r & 1)) / 2;
        return {col, r};
    }

    // Obtenir la case voisine dans une direction donnée
    inline Vector2i getNeighbor(const Vector2i& pos, Direction dir, Couleur couleur) {
        int x = pos.x;
        int y = pos.y;

        switch (dir) {
            case FORWARD:
                if (y < 3) return Vector2i(x, y + 1); // Avancer dans la même zone

                // Traverser vers une autre zone
                if (couleur == BLANC) {
                    // De la zone blanche vers la zone rouge ou noire
                    if (x < 4) return Vector2i(3 - x, 6); // Vers la zone rouge
                    else return Vector2i(x, 3); // Vers la zone noire
                } else if (couleur == ROUGE) {
                    // De la zone rouge vers la zone blanche ou noire
                    if (y == 6) return Vector2i(3 - x, 8); // Vers la zone blanche
                    else return Vector2i(4, 3 - (y - 4)); // Vers la zone noire
                } else { // NOIR
                    // De la zone noire vers la zone blanche ou rouge
                    if (y == 3) return Vector2i(x, 8); // Vers la zone blanche
                    else return Vector2i(3, 6 - (y - 4)); // Vers la zone rouge
                }

            case BACKWARD:
                if (y > 0) return Vector2i(x, y - 1);
                return Vector2i(-1, -1); // Hors de l'échiquier

            case LEFT:
                if (x > 0) return Vector2i(x - 1, y);
                return Vector2i(-1, -1); // Hors de l'échiquier

            case RIGHT:
                if (x < 11) return Vector2i(x + 1, y);
                return Vector2i(-1, -1); // Hors de l'échiquier
        }

        return Vector2i(-1, -1); // Direction invalide
    }

    // Directions pour les mouvements de la tour (axes principaux)
    static const vector<Cube> rookDirections = {
            {+1, -1, 0}, {+1, 0, -1}, {0, +1, -1},
            {-1, +1, 0}, {-1, 0, +1}, {0, -1, +1}
    };

    // Directions pour les mouvements du fou (diagonales)
    static const vector<Cube> bishopDirections = {
            {+2, -1, -1}, {+1, +1, -2}, {-1, +2, -1},
            {-2, +1, +1}, {-1, -1, +2}, {+1, -2, +1}
    };

    // Directions pour les mouvements du cavalier
    inline vector<Cube> knightDirections() {
        vector<Cube> jumps;
        for (int i = 0; i < 6; ++i) {
            int v1 = (i + 1) % 6;
            int v2 = (i + 5) % 6;

            // Premier saut: 2 pas dans la direction i, puis 1 pas dans la direction v1
            jumps.push_back({
                                    rookDirections[i].x * 2 + rookDirections[v1].x,
                                    rookDirections[i].y * 2 + rookDirections[v1].y,
                                    rookDirections[i].z * 2 + rookDirections[v1].z
                            });

            // Second saut: 2 pas dans la direction i, puis 1 pas dans la direction v2
            jumps.push_back({
                                    rookDirections[i].x * 2 + rookDirections[v2].x,
                                    rookDirections[i].y * 2 + rookDirections[v2].y,
                                    rookDirections[i].z * 2 + rookDirections[v2].z
                            });
        }
        return jumps;
    }

    // Indice de la direction "avant" pour chaque couleur
    static const int pawnForwardIndex[3] = {
            5,  // BLANC (vers le haut/centre depuis le bas)
            0,  // ROUGE (vers bas-droite/centre depuis haut-gauche)
            1   // NOIR (vers bas-gauche/centre depuis haut-droite)
    };
}
