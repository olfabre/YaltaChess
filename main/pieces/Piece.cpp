#include "Piece.h"

Piece::Piece(sf::Vector2i pos, Couleur coul)
        : position(pos), couleur(coul) {}

sf::Vector2i Piece::getPosition() const {
    return position;
}

void Piece::setPosition(sf::Vector2i nouvellePos) {
    position = nouvellePos;
}

Couleur Piece::getCouleur() const {
    return couleur;
}