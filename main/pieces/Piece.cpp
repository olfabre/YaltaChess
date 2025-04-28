#include "Piece.h"
#include "../Model.h"
#include "../cases/Case.h"

using namespace sf;
using namespace std;

Piece::Piece(Vector2i pos, Couleur coul)
        : position(pos), couleur(coul) {}

Vector2i Piece::getPosition() const {
    return position;
}

void Piece::setPosition(Vector2i nouvellePos) {
    position = nouvellePos;
}

Couleur Piece::getCouleur() const {
    return couleur;
}

std::vector<Vector2i> Piece::slideOrJumpMoves(
        const Model& model,
        const std::vector<std::string>& directions,
        int limit,
        bool mayCapture,
        bool mustCapture
) const {
    std::vector<Vector2i> res;
    // 1) on récupère la case actuelle
    Case* cur = model.getCaseAt(position);
    if (!cur) return res;

    // 2) on appelle targets() pour obtenir les Case*
    auto cibles = cur->targets(couleur, directions, limit, mayCapture, mustCapture);

    // 3) on convertit en coordonnées grille
    for (Case* dst : cibles) {
        res.push_back(dst->getGridPos());
    }
    return res;
}