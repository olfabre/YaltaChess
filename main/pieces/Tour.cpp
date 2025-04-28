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

/*
vector<Vector2i> Tour::getLegalMoves(const Model& model) const {
    // directions cardinales
    static const array<Vector2i,4> dirs = {{
     { 1,  0}, {-1,  0}, { 0,  1}, { 0, -1}
                                           }};

    vector<Vector2i> res;
    for (auto d : dirs) {
        Vector2i dest = position + d;
        // glisser tant que sur la grille
        while (dest.x >= 0 && dest.x < 12
               && dest.y >= 0 && dest.y < 12)
        {
            // vérification ligne/colonne
            if (!mouvementValide(dest))
                break;

            Piece* cible = model.getPieceAt(dest);
            if (!cible) {
                // case libre
                res.push_back(dest);
            } else {
                // case occupée : capture si adversaire
                if (cible->getCouleur() != couleur)
                    res.push_back(dest);
                // arrêt dès qu'on rencontre une pièce
                break;
            }
            dest += d;
        }
    }
    return res;
}

 */

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