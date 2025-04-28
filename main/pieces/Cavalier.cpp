#include "Cavalier.h"
#include "cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
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
    vector<Vector2i> res;
    Cube cur = Hex::grilleVersCube(position);
    Couleur pieceCouleur = getCouleur();

    // Utiliser les sauts du cavalier définis dans HexagonalCubique.h
    vector<Cube> jumps = Hex::sautsCavalier();

    // Parcourir tous les sauts possibles du cavalier
    for (const auto& jump : jumps) {
        // Calculer la position après le saut
        Cube nxt = { cur.x + jump.x, cur.y + jump.y, cur.z + jump.z };
        Vector2i gridPos = Hex::cubeVersGrille(nxt);

        // Vérifier si la case existe
        Case* c = model.getCaseAt(gridPos);
        if (!c) continue; // Passer au saut suivant si on sort de l'échiquier

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

    return res;
}



// implémentation du nom
string Cavalier::getTypeName() const {
        return "Cavalier";
    }


