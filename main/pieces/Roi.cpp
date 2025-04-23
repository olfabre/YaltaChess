#include "Roi.h"
#include <cmath>
using namespace sf;
using namespace std;

Roi::Roi(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Roi::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    return (dx <= 1 && dy <= 1);
}

void Roi::dessiner(RenderWindow& window) const {
    // Ici, dessiner le Roi (sprite ou forme)
}
