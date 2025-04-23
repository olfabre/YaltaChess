#include "Dame.h"
#include <cmath>
using namespace sf;
using namespace std;

Dame::Dame(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Dame::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    return (dx == dy || dx == 0 || dy == 0);
}

void Dame::dessiner(RenderWindow& window) const {
    // Dessiner la Dame
}
