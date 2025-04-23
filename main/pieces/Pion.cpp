#include "Pion.h"
using namespace sf;
using namespace std;

Pion::Pion(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Pion::mouvementValide(Vector2i nouvellePos) const {
    int dy = nouvellePos.y - position.y;
    return (dy == 1 && position.x == nouvellePos.x); // Simplifié pour exemple
}

void Pion::dessiner(RenderWindow& window) const {
    // Dessiner le Pion
}
