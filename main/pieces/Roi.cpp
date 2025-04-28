#include "Roi.h"
#include "cases/Case.h"   // pour .getGridPos() et .targets()
#include "Model.h"
#include "HexagonalCubique.h"
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Roi::Roi(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Roi::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    // une case maximum dans toutes les directions, sauf rester en place
    return (dx <= 1 && dy <= 1) && (dx != 0 || dy != 0);
}

void Roi::dessiner(RenderWindow& window) const {
    // Ici, dessiner le Roi (sprite ou forme)
}




vector<Vector2i> Roi::getLegalMoves(const Model& model) const {

    Case* cur = nullptr;
    for (auto c : model.getCases())
        if (c->getGridPos() == position) { cur = c; break; }
    if (!cur) return {};

    vector<string> dirs = { "N","NE","E","SE","S","SW","W","NW" };
    auto cibles = cur->targets(couleur, dirs, /*limit=*/1, /*mayCapture=*/true, /*mustCapture=*/false);

    vector<Vector2i> res;
    for (auto dst : cibles)
        res.push_back(dst->getGridPos());
    return res;
}


string Roi::getTypeName() const {
    return "Roi";
}