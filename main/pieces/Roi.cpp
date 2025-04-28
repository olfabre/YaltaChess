#include "Roi.h"
#include "cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
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
    vector<Vector2i> res;
    Cube cur = Hex::grilleVersCube(position);
    Couleur pieceCouleur = getCouleur();

    // 1. Mouvements dans les directions principales (comme la tour, mais une seule case)
    for (const auto& dir : Hex::directionsTour) {
        Cube nxt = { cur.x + dir.x, cur.y + dir.y, cur.z + dir.z };
        Vector2i gridPos = Hex::cubeVersGrille(nxt);

        // Vérifier si la case existe
        Case* c = model.getCaseAt(gridPos);
        if (!c) continue; // Passer à la direction suivante si on sort de l'échiquier

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
        }
    }

    // 2. Mouvements dans les directions diagonales (comme le fou, mais une seule case)
    for (const auto& dir : Hex::directionsFou) {
        Cube nxt = { cur.x + dir.x, cur.y + dir.y, cur.z + dir.z };
        Vector2i gridPos = Hex::cubeVersGrille(nxt);

        // Vérifier si la case existe
        Case* c = model.getCaseAt(gridPos);
        if (!c) continue; // Passer à la direction suivante si on sort de l'échiquier

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
        }
    }

    // Note: Le roque n'est pas implémenté ici, car il n'est pas clair s'il est applicable dans Yalta

    return res;
}


string Roi::getTypeName() const {
    return "Roi";
}