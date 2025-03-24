#include "Pion.h"

Pion::Pion(sf::Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Pion::mouvementValide(sf::Vector2i nouvellePos) const {
    int dy = nouvellePos.y - position.y;
    return (dy == 1 && position.x == nouvellePos.x); // Simplifié pour exemple
}

void Pion::dessiner(sf::RenderWindow& window) const {
    // Dessiner le Pion
}
