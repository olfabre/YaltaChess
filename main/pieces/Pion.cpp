#include "Pion.h"
#include "cases/Case.h"   // pour .getGridPos() et .targets()
#include "Model.h"
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Pion::Pion(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Pion::mouvementValide(Vector2i nouvellePos) const {
    // ne gère que l’avance d’une case
    Vector2i delta = nouvellePos - position;
    switch (couleur) {
        case BLANC: return delta == Vector2i{0, +1};
        case NOIR:  return delta == Vector2i{0, -1};
        case ROUGE: return delta == Vector2i{+1, 0};
    }
    return false;
}


void Pion::dessiner(RenderWindow& window) const {
    // Dessiner le Pion
}


/*
vector<Vector2i> Pion::getLegalMoves(const Model& model) const {
    vector<Vector2i> res;

    // direction “avant” selon la couleur
    Vector2i forward;
    switch (couleur) {
        case BLANC: forward = {0, +1}; break;
        case NOIR:  forward = {0, -1}; break;
        case ROUGE: forward = {+1, 0}; break;
    }

    // 1) case vide devant
    Vector2i one = position + forward;
    if (one.x >= 0 && one.x < 12 && one.y >= 0 && one.y < 12
        && !model.getPieceAt(one)) {
        res.push_back(one);
    }

    // 2) captures diagonales/latérales : forward ± perpendicular
    Vector2i perp1 = { forward.y, -forward.x };
    Vector2i perp2 = { -forward.y, forward.x };
    for (auto side : {perp1, perp2}) {
        Vector2i cap = position + forward + side;
        if (cap.x < 0 || cap.x >= 12 || cap.y < 0 || cap.y >= 12)
            continue;
        if (Piece* cible = model.getPieceAt(cap)) {
            if (cible->getCouleur() != couleur)
                res.push_back(cap);
        }
    }

    return res;
}

 */

vector<Vector2i> Pion::getLegalMoves(const Model& model) const {
    Case* cur = nullptr;
    for (auto c : model.getCases())
        if (c->getGridPos() == position) { cur = c; break; }
    if (!cur) return {};

    vector<Vector2i> res;

    // 1) avancer d’une case (direction "N" relative à la side)
    {
        auto adv = cur->targets(couleur, { "N" }, 1, /*mayCapture=*/false, /*mustCapture=*/false);
        for (auto dst : adv)
            res.push_back(dst->getGridPos());
    }

    // 2) captures diagonales (NE et NW), mustCapture=true
    {
        auto caps = cur->targets(couleur, { "NE","NW" }, 1, /*mayCapture=*/true, /*mustCapture=*/true);
        for (auto dst : caps)
            res.push_back(dst->getGridPos());
    }

    return res;
}



string Pion::getTypeName() const {
    return "Pion";
}