#include "Fou.h"
#include "../cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Fou::Fou(Cube pos, Couleur coul, Model* modelPtr) : Piece(pos, coul) {
    this->modelPtr = modelPtr;
}

bool Fou::mouvementValide(Cube nouvellePos) const {
    auto mouvements = Hex::mouvementsFou(positionCube, *modelPtr, couleur);
    return std::find(mouvements.begin(), mouvements.end(), nouvellePos) != mouvements.end();
}

void Fou::dessiner(RenderWindow& window) const {
    // Dessiner le Fou
}

vector<Cube> Fou::getLegalMoves(const Model& model) const {
    return Hex::mouvementsFou(positionCube, model, couleur);
}

string Fou::getTypeName() const {
    return "Fou";
}