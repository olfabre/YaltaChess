#include "Roi.h"
#include <cmath>

Roi::Roi(sf::Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Roi::mouvementValide(sf::Vector2i nouvellePos) const {
    int dx = std::abs(nouvellePos.x - position.x);
    int dy = std::abs(nouvellePos.y - position.y);
    return (dx <= 1 && dy <= 1);
}

void Roi::dessiner(sf::RenderWindow& window) const {
    // Ici, dessiner le Roi (sprite ou forme)
}
