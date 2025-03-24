#include "Tour.h"

Tour::Tour(sf::Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Tour::mouvementValide(sf::Vector2i nouvellePos) const {
    return (nouvellePos.x == position.x || nouvellePos.y == position.y);
}

void Tour::dessiner(sf::RenderWindow& window) const {
    // Dessiner la Tour
}
