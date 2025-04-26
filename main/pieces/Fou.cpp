#include "Fou.h"
#include "Model.h"
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
    // directions diagonales
    static const array<Vector2i,4> dirs = {{
     { 1,  1}, { 1, -1}, {-1,  1}, {-1, -1}
                                           }};

    vector<Vector2i> res;
    for (auto d : dirs) {
        Vector2i dest = position + d;
        // avancer tant que dans la grille 0..11
        while (dest.x >= 0 && dest.x < 12
               && dest.y >= 0 && dest.y < 12)
        {
            if (!mouvementValide(dest))
                break;

            Piece* cible = model.getPieceAt(dest);
            if (!cible) {
                // libre
                res.push_back(dest);
            } else {
                // occupée → capture si adversaire
                if (cible->getCouleur() != couleur)
                    res.push_back(dest);
                break;  // blocée par la pièce présente
            }
            dest += d;
        }
    }
    return res;
}

string Fou::getTypeName() const {
    return "Fou";
}