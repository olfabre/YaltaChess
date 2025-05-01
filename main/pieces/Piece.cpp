#include "Piece.h"
#include "../HexagonalCubique.h"   // pour struct Cube, operator==, CubeHash
#include "../Model.h"
#include "../cases/Case.h"
#include "../Couleur.h"

using namespace sf;
using namespace std;

Piece::Piece(Cube pos, Couleur coul)
    : positionCube(pos), couleur(coul) {}



void Piece::setPosition(Cube nouvellePos) {
        positionCube = nouvellePos;
    }

Couleur Piece::getCouleur() const {
    return couleur;
}

