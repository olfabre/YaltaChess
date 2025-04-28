#include "Dame.h"
#include "cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
#include <array>
#include <cmath>

using namespace sf;
using namespace std;

Dame::Dame(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Dame::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    // diagonale ou ligne/colonness
    return (dx == dy || dx == 0 || dy == 0);
}

void Dame::dessiner(RenderWindow& window) const {
    // Dessiner la Dame
}


vector<Vector2i> Dame::getLegalMoves(const Model& model) const {
    vector<Vector2i> res;
    Cube cur = Hex::grilleVersCube(position);
    Couleur pieceCouleur = getCouleur();

    // 1. Mouvements de la tour (axes principaux)
    for (const auto& dir : Hex::directionsTour) {
        Cube nxt = cur;
        while (true) {
            // Avancer d'une case dans la direction actuelle
            nxt = { nxt.x + dir.x, nxt.y + dir.y, nxt.z + dir.z };
            Vector2i gridPos = Hex::cubeVersGrille(nxt);

            // Vérifier si la case existe
            Case* c = model.getCaseAt(gridPos);
            if (!c) break; // Sortir de la boucle si on sort de l'échiquier

            // Vérifier si la case est occupée
            if (!model.isOccupied(gridPos)) {
                // Case vide, on peut y aller
                res.push_back(gridPos);
            } else {
                // Case occupée
                Piece* p = model.getPieceAt(gridPos);
                if (p && p->getCouleur() != pieceCouleur) {
                    // Pièce ennemie, on peut la capturer
                    res.push_back(gridPos);
                }
                // On ne peut pas aller plus loin dans cette direction
                break;
            }
        }
    }

    // 2. Mouvements du fou (diagonales)
    for (const auto& dir : Hex::directionsFou) {
        Cube nxt = cur;
        while (true) {
            // Avancer d'une case dans la direction diagonale actuelle
            nxt = { nxt.x + dir.x, nxt.y + dir.y, nxt.z + dir.z };
            Vector2i gridPos = Hex::cubeVersGrille(nxt);

            // Vérifier si la case existe
            Case* c = model.getCaseAt(gridPos);
            if (!c) break; // Sortir de la boucle si on sort de l'échiquier

            // Vérifier si la case est occupée
            if (!model.isOccupied(gridPos)) {
                // Case vide, on peut y aller
                res.push_back(gridPos);
            } else {
                // Case occupée
                Piece* p = model.getPieceAt(gridPos);
                if (p && p->getCouleur() != pieceCouleur) {
                    // Pièce ennemie, on peut la capturer
                    res.push_back(gridPos);
                }
                // On ne peut pas aller plus loin dans cette direction
                break;
            }
        }
    }

    return res;
}


// nom de la pièce (pour charger la texture, etc.)
// getTypeName()
string Dame::getTypeName() const {
    return "Dame";
    }