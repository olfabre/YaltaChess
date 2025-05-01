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

bool Dame::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    // diagonale ou ligne/colonness
    return (dx == dy || dx == 0 || dy == 0);
}

void Dame::dessiner(RenderWindow& window) const {
    // Dessiner la Dame
}


vector<Cube> Dame::getLegalMoves(const Model& model) const {
    return Hex::movesDame(position, model, couleur);
}


// nom de la pièce (pour charger la texture, etc.)
// getTypeName()
string Dame::getTypeName() const {
    return "Dame";
    }