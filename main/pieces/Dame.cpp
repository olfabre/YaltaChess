#include "Dame.h"
#include "../cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
#include <array>
#include <cmath>

using namespace sf;
using namespace std;


Dame::Dame(Cube pos, Couleur coul, Model* modelPtr) : Piece(pos, coul) {
    this->modelPtr = modelPtr;
}

bool Dame::mouvementValide(Cube nouvellePos) const {
    auto mouvements = Hex::mouvementsDame(positionCube, *modelPtr, couleur);
    return std::find(mouvements.begin(), mouvements.end(), nouvellePos) != mouvements.end();
}


void Dame::dessiner(RenderWindow& window) const {
    // Dessiner la Dame
}

vector<Cube> Dame::getLegalMoves(const Model& model) const {
    return Hex::mouvementsDame(positionCube, model, couleur);
}


// nom de la pièce (pour charger la texture, etc.)
// getTypeName()
string Dame::getTypeName() const {
    return "Dame";
    }