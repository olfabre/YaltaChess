#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <array>
#include "Model.h"    // pour Model et Couleur

// Structure représentant une case sur la grille hexagonale en coordonnées cubiques
struct Cube { int x, y, z; };

namespace Hex {

    // Conversion d'une case en coordonnées "offset odd-r" (grille 2D) vers les coordonnées cubiques
    inline Cube grilleVersCube(const sf::Vector2i &g) {
        int q = g.x - (g.y - (g.y & 1)) / 2;
        int r = g.y;
        int x = q;
        int z = r;
        int y = -x - z;
        return {x, y, z};
    }

    // Conversion inverse : d'une position cubique vers la grille 2D "offset odd-r"
    inline sf::Vector2i cubeVersGrille(const Cube &c) {
        int q = c.x;
        int r = c.z;
        int col = q + (r - (r & 1)) / 2;
        return {col, r};
    }


}