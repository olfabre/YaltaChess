#include "Fou.h"
#include "../cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Fou::Fou(Cube pos, Couleur coul) : Piece(pos, coul) {}

bool Fou::mouvementValide(Cube nouvellePos) const {
    int dx = abs(nouvellePos.x - positionCube.x);
    int dy = abs(nouvellePos.y - positionCube.y);
    int dz = abs(nouvellePos.z - positionCube.z);
    // … test en cube …
    return true;
}

void Fou::dessiner(RenderWindow& window) const {
    // Dessiner le Fou
}



vector<Cube> Fou::getLegalMoves(const Model& model) const {
    return Hex::movesFou(positionCube, model, couleur);
}


string Fou::getTypeName() const {
    return "Fou";
}