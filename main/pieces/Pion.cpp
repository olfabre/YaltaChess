#include "Pion.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../HexagonalCubique.h"  // on utilise les coordonnées cube
#include <vector>
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Pion::Pion(Cube pos, Couleur coul) : Piece(pos, coul) {}

void Pion::dessiner(RenderWindow& window) const {
    // Dessiner le Pion
}

bool Pion::mouvementValide(Cube nouvellePos) const {
    int dx = abs(nouvellePos.x - positionCube.x);
    int dy = abs(nouvellePos.y - positionCube.y);
    int dz = abs(nouvellePos.z - positionCube.z);
    // … test en cube …
    return true;
}



vector<Cube> Pion::getLegalMoves(const Model& model) const {
    return Hex::movesPion(positionCube, model, couleur);
}

string Pion::getTypeName() const {
    return "Pion";
}