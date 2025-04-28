#include "Fou.h"
#include "cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
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
    vector<Vector2i> res;
    Cube cur = Hex::grilleVersCube(position);
    Couleur pieceCouleur = getCouleur();

    // Parcourir les 6 directions diagonales du fou dans un système hexagonal
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


string Fou::getTypeName() const {
    return "Fou";
}