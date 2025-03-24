#include "Cavalier.h"
#include <cmath>

Cavalier::Cavalier(sf::Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Cavalier::mouvementValide(sf::Vector2i nouvellePos) const {
    int dx = std::abs(nouvellePos.x - position.x);
    int dy = std::abs(nouvellePos.y - position.y);
    return ((dx == 1 && dy == 2) || (dx == 2 && dy == 1));
}

void Cavalier::dessiner(sf::RenderWindow& window) const {
    // Dessiner le Cavalier
}
