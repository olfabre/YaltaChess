#include "Pion.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../HexagonalCubique.h"  // on utilise les coordonnées cube
#include <vector>

using namespace sf;
using namespace std;

Pion::Pion(Cube pos, Couleur coul) : Piece(pos, coul) {}

void Pion::dessiner(RenderWindow& window) const {
    // Dessiner le Pion
}

bool Pion::mouvementValide(Vector2i nouvellePos) const {
    // Cette fonction n'est pas utilisée pour getLegalMoves, donc nous la laissons telle quelle
    Vector2i delta = nouvellePos - position;
    switch (couleur) {
        case BLANC: return delta == Vector2i{0, +1};
        case NOIR:  return delta == Vector2i{0, -1};
        case ROUGE: return delta == Vector2i{+1, 0};
    }
    return false;
}



vector<Cube> Pion::getLegalMoves(const Model& model) const {
    return Hex::movesPion(position, model, couleur);
}

string Pion::getTypeName() const {
    return "Pion";
}