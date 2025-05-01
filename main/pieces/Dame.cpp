#include "Dame.h"
#include "../cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
#include <array>
#include <cmath>

using namespace sf;
using namespace std;


Dame::Dame(Cube pos, Couleur coul) : Piece(pos, coul) {}

bool Dame::mouvementValide(Cube nouvellePos) const {
    int dx = abs(nouvellePos.x - positionCube.x);
    int dy = abs(nouvellePos.y - positionCube.y);
    int dz = abs(nouvellePos.z - positionCube.z);
    // … test en cube …
    return true;
}


void Dame::dessiner(RenderWindow& window) const {
    // Dessiner la Dame
}

vector<Cube> Dame::getLegalMoves(const Model& model) const {
    return Hex::movesDame(positionCube, model, couleur);
}


// nom de la pièce (pour charger la texture, etc.)
// getTypeName()
string Dame::getTypeName() const {
    return "Dame";
    }