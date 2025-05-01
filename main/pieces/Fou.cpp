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

bool Fou::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    return (dx == dy);
}

void Fou::dessiner(RenderWindow& window) const {
    // Dessiner le Fou
}



vector<Cube> Fou::getLegalMoves(const Model& model) const {
    return Hex::movesFou(position, model, couleur);
}


string Fou::getTypeName() const {
    return "Fou";
}