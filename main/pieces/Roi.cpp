#include "Roi.h"
#include "Model.h"
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
    static const array<Vector2i,8> dirs = {{
                                                   { 1,  0}, { 1,  1}, { 0,  1}, {-1,  1},
                                                   {-1,  0}, {-1, -1}, { 0, -1}, { 1, -1}
                                           }};

    vector<Vector2i> res;
    for (auto d : dirs) {
        Vector2i dest = position + d;
        // vérifier qu’on reste sur la grille
        if (dest.x < 0 || dest.x >= 12 ||
            dest.y < 0 || dest.y >= 12)
            continue;
        // filtre par mouvementValide (au cas où)
        if (!mouvementValide(dest))
            continue;
        // case libre ou capturable
        if (Piece* cible = model.getPieceAt(dest)) {
            if (cible->getCouleur() != couleur)
                res.push_back(dest);
        } else {
            res.push_back(dest);
        }
    }
    return res;
}

string Roi::getTypeName() const {
    return "Roi";
}