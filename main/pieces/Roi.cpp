#include "Roi.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../HexagonalCubique.h"  // on utilise les coordonnées cube
#include <vector>
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Roi::Roi(Cube pos, Couleur coul, Model* modelPtr) : Piece(pos, coul) {
    this->modelPtr = modelPtr;
}

bool Roi::mouvementValide(Cube nouvellePos) const {
    auto mouvements = Hex::mouvementsRoi(positionCube, *modelPtr, couleur);
    return std::find(mouvements.begin(), mouvements.end(), nouvellePos) != mouvements.end();
}

void Roi::dessiner(RenderWindow& window) const {
    // Ici, dessiner le Roi (sprite ou forme)
}

vector<Cube> Roi::getLegalMoves(const Model& model) const {
    return Hex::mouvementsRoi(positionCube, model, couleur);
}

string Roi::getTypeName() const {
    return "Roi";
}