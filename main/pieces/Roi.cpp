#include "Roi.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../HexagonalCubique.h"  // on utilise les coordonnées cube
#include <vector>

using namespace sf;
using namespace std;

Roi::Roi(Cube pos, Couleur coul) : Piece(pos, coul) {}

bool Roi::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    // une case maximum dans toutes les directions, sauf rester en place
    return (dx <= 1 && dy <= 1) && (dx != 0 || dy != 0);
}

void Roi::dessiner(RenderWindow& window) const {
    // Ici, dessiner le Roi (sprite ou forme)
}




vector<Cube> Roi::getLegalMoves(const Model& model) const {
    return Hex::movesRoi(position, model, couleur);
}


string Roi::getTypeName() const {
    return "Roi";
}