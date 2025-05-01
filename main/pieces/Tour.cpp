#include "Tour.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../HexagonalCubique.h"  // Utilisation exclusive de Hex pour les conversions
#include <vector>

using namespace sf;
using namespace std;

Tour::Tour(Cube pos, Couleur coul) : Piece(pos, coul) {}

bool Tour::mouvementValide(Vector2i nouvellePos) const {
    // Cette fonction n'est pas utilisée pour getLegalMoves, donc nous la laissons telle quelle
    return (nouvellePos.x == position.x || nouvellePos.y == position.y)
           && !(nouvellePos == position);
}

void Tour::dessiner(RenderWindow& window) const {
    // Dessiner la Tour
}

vector<Cube> Tour::getLegalMoves(const Model& model) const {
    return Hex::movesTour(position, model, couleur);
}

string Tour::getTypeName() const {
    return "Tour";
}
