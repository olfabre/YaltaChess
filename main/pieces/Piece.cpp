#include "Piece.h"
#include "../Model.h"
#include "../cases/Case.h"

using namespace sf;
using namespace std;

Piece::Piece(Vector2i pos, Couleur coul)
        : position(pos), couleur(coul) {}

Vector2i Piece::getPosition() const {
    return position;
}

void Piece::setPosition(Vector2i nouvellePos) {
    position = nouvellePos;
}

Couleur Piece::getCouleur() const {
    return couleur;
}

