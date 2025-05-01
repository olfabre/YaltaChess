#include "Piece.h"
#include "../Model.h"
#include "../cases/Case.h"

using namespace sf;
using namespace std;

Piece::Piece(Cube pos, Couleur coul)
        : positionCube(pos), couleur(coul) {}

Cube Piece::getPosition() const {
    return position;
}

void Piece::setPosition(Cube nouvellePos) {
    positionCube = nouvellePos;
}

Couleur Piece::getCouleur() const {
    return couleur;
}

