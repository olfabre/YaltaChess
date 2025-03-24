#include "Fou.h"
#include <cmath>

Fou::Fou(sf::Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Fou::mouvementValide(sf::Vector2i nouvellePos) const {
    int dx = std::abs(nouvellePos.x - position.x);
    int dy = std::abs(nouvellePos.y - position.y);
    return (dx == dy);
}

void Fou::dessiner(sf::RenderWindow& window) const {
    // Dessiner le Fou
}
