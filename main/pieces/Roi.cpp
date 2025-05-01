#include "Roi.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../HexagonalCubique.h"  // on utilise les coordonnées cube
#include <vector>
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Roi::Roi(Cube pos, Couleur coul) : Piece(pos, coul) {}

bool Roi::mouvementValide(Cube nouvellePos) const {
    int dx = abs(nouvellePos.x - positionCube.x);
    int dy = abs(nouvellePos.y - positionCube.y);
    int dz = abs(nouvellePos.z - positionCube.z);
    // … test en cube …
    return true;
}

void Roi::dessiner(RenderWindow& window) const {
    // Ici, dessiner le Roi (sprite ou forme)
}




vector<Cube> Roi::getLegalMoves(const Model& model) const {
    return Hex::movesRoi(positionCube, model, couleur);
}


string Roi::getTypeName() const {
    return "Roi";
}