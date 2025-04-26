#include "Dame.h"
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

// renvoie tous les déplacements valides jusqu’à obstacle
vector<Vector2i> Dame::getLegalMoves(const Model& model) const {
    static const array<Vector2i,8> dirs = {{
        { 1,  0}, { 0,  1}, {-1,  0}, { 0, -1},
        { 1,  1}, { 1, -1}, {-1,  1}, {-1, -1}
                                           }};

    vector<Vector2i> res;
    for (auto d : dirs) {
        Vector2i dest = position + d;
        // on avance tant qu’on reste dans la grille 0..11
        while (dest.x >= 0 && dest.x < 12
               && dest.y >= 0 && dest.y < 12)
        {
            if (!mouvementValide(dest))
                break;

            Piece* cible = model.getPieceAt(dest);
            if (!cible) {
                // case libre
                res.push_back(dest);
            } else {
                // case occupée : capture possible si adversaire
                if (cible->getCouleur() != couleur)
                    res.push_back(dest);
                break;  // obstacle terminé
            }
            dest += d;
        }
    }
    return res;
}

// nom de la pièce (pour charger la texture, etc.)
// getTypeName()
string Dame::getTypeName() const {
    return "Dame";
    }