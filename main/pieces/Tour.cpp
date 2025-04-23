#include "Tour.h"
using namespace sf;
using namespace std;

Tour::Tour(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Tour::mouvementValide(Vector2i nouvellePos) const {
    return (nouvellePos.x == position.x || nouvellePos.y == position.y);
}

void Tour::dessiner(RenderWindow& window) const {
    // Dessiner la Tour
}
