#include "Fou.h"
#include <cmath>
using namespace sf;
using namespace std;

Fou::Fou(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Fou::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    return (dx == dy);
}

void Fou::dessiner(RenderWindow& window) const {
    // Dessiner le Fou
}
