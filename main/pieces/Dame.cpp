#include "Dame.h"
#include <cmath>

Dame::Dame(sf::Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Dame::mouvementValide(sf::Vector2i nouvellePos) const {
    int dx = std::abs(nouvellePos.x - position.x);
    int dy = std::abs(nouvellePos.y - position.y);
    return (dx == dy || dx == 0 || dy == 0);
}

void Dame::dessiner(sf::RenderWindow& window) const {
    // Dessiner la Dame
}
