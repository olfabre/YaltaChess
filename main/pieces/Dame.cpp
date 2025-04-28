#include "Dame.h"
#include "cases/Case.h"   // pour .getGridPos() et .targets()
#include "Model.h"    // pour getPieceAt
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Dame::Dame(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Dame::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    // diagonale ou ligne/colonne
    return (dx == dy || dx == 0 || dy == 0);
}

void Dame::dessiner(RenderWindow& window) const {
    // Dessiner la Dame
}


vector<Vector2i> Dame::getLegalMoves(const Model& model) const {
    Case* cur = nullptr;
    for (auto c : model.getCases())
        if (c->getGridPos() == position) { cur = c; break; }
    if (!cur) return {};

    vector<string> dirs = { "N","E","S","W","NE","NW","SE","SW" };
    auto cibles = cur->targets(couleur, dirs, /*limit=*/10, /*mayCapture=*/true, /*mustCapture=*/false);

    vector<Vector2i> res;
    for (auto dst : cibles)
        res.push_back(dst->getGridPos());
    return res;
}


// nom de la pièce (pour charger la texture, etc.)
// getTypeName()
string Dame::getTypeName() const {
    return "Dame";
    }