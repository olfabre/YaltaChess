#include "Tour.h"
#include "cases/Case.h"   // pour .getGridPos() et .targets()
#include "Model.h"    // pour Model::getPieceAt
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Tour::Tour(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Tour::mouvementValide(Vector2i nouvellePos) const {
    // même colonne ou même ligne
    return (nouvellePos.x == position.x || nouvellePos.y == position.y)
           && !(nouvellePos == position);
}

void Tour::dessiner(RenderWindow& window) const {
    // Dessiner la Tour
}



vector<Vector2i> Tour::getLegalMoves(const Model& model) const {
    Case* cur = nullptr;
    for (auto c : model.getCases())
        if (c->getGridPos() == position) { cur = c; break; }
    if (!cur) return {};

    vector<string> dirs = { "N","E","S","W" };
    auto cibles = cur->targets(couleur, dirs, /*limit=*/10, /*mayCapture=*/true, /*mustCapture=*/false);

    vector<Vector2i> res;
    for (auto dst : cibles)
        res.push_back(dst->getGridPos());
    return res;
}



string Tour::getTypeName() const {
    return "Tour";
}