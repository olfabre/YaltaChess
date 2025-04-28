#include "Fou.h"
#include "cases/Case.h"   // pour .getGridPos() et .targets()
#include "Model.h"
#include "HexagonalCubique.h"
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Fou::Fou(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Fou::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    return (dx == dy);
}

void Fou::dessiner(RenderWindow& window) const {
    // Dessiner le Fou
}



vector<Vector2i> Fou::getLegalMoves(const Model& model) const {
    Case* cur = nullptr;
    for (auto c : model.getCases())
        if (c->getGridPos() == position) { cur = c; break; }
    if (!cur) return {};

    vector<string> dirs = { "NE","NW","SE","SW" };
    auto cibles = cur->targets(couleur, dirs, /*limit=*/10, /*mayCapture=*/true, /*mustCapture=*/false);

    vector<Vector2i> res;
    for (auto dst : cibles)
        res.push_back(dst->getGridPos());
    return res;
}


string Fou::getTypeName() const {
    return "Fou";
}