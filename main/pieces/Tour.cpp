#include "Tour.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../HexagonalCubique.h"  // Utilisation exclusive de Hex pour les conversions
#include <vector>
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Tour::Tour(Cube pos, Couleur coul) : Piece(pos, coul) {}

bool Tour::mouvementValide(Cube nouvellePos) const {
    int dx = abs(nouvellePos.x - positionCube.x);
    int dy = abs(nouvellePos.y - positionCube.y);
    int dz = abs(nouvellePos.z - positionCube.z);
    // … test en cube …
    return true;
}

void Tour::dessiner(RenderWindow& window) const {
    // Dessiner la Tour
}

vector<Cube> Tour::getLegalMoves(const Model& model) const {
    return Hex::movesTour(positionCube, model, couleur);
}

string Tour::getTypeName() const {
    return "Tour";
}
