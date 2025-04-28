#include "Cavalier.h"
#include "cases/Case.h"   // pour .getGridPos() et .targets()
#include "Model.h"   // pour getPieceAt / isOccupied
#include "HexagonalCubique.h"
#include <array>
#include <cmath>

using namespace sf;
using namespace std;



Cavalier::Cavalier(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Cavalier::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    return ((dx == 1 && dy == 2) || (dx == 2 && dy == 1));
}

void Cavalier::dessiner(RenderWindow& window) const {
    // Dessiner le Cavalier
}







vector<Vector2i> Cavalier::getLegalMoves(const Model& model) const {
    // 1) trouver la case actuelle
    Case* cur = nullptr;
    for (auto c : model.getCases())
        if (c->getGridPos() == position) { cur = c; break; }
    if (!cur) return {};

    // 2) directions de saut du cavalier, relatives à la case/side
    vector<string> dirs = { "NNE","NEE","SEE","SSE","SSW","SWW","NWW","NNW" };

    // 3) appeler targets(limit=1, mayCapture=true)
    auto cibles = cur->targets(couleur, dirs, 1, /*mayCapture=*/true, /*mustCapture=*/false);

    // 4) convertir en Vector2i
    vector<Vector2i> res;
    for (auto dst : cibles)
        res.push_back(dst->getGridPos());
    return res;
}



// implémentation du nom
string Cavalier::getTypeName() const {
        return "Cavalier";
    }


