#include "Pion.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "HexagonalCubique.h"  // on utilise les coordonnées cube
#include <vector>

using namespace sf;
using namespace std;

Pion::Pion(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

void Pion::dessiner(RenderWindow& window) const {
    // Dessiner le Pion
}

bool Pion::mouvementValide(Vector2i nouvellePos) const {
    // Cette fonction n'est pas utilisée pour getLegalMoves, donc nous la laissons telle quelle
    Vector2i delta = nouvellePos - position;
    switch (couleur) {
        case BLANC: return delta == Vector2i{0, +1};
        case NOIR:  return delta == Vector2i{0, -1};
        case ROUGE: return delta == Vector2i{+1, 0};
    }
    return false;
}



vector<Vector2i> Pion::getLegalMoves(const Model& model) const {
    vector<Vector2i> res;
    // Conversion grille -> cube
    Cube cur = Hex::grilleVersCube(position);

    // Direction "avant" selon la couleur
    Cube forward;
    switch (couleur) {
        case BLANC: forward = Hex::directionsTour[2]; break;   // Nord
        case ROUGE: forward = Hex::directionsTour[3]; break;   // Sud-Ouest
        case NOIR:  forward = Hex::directionsTour[5]; break;   // Sud-Est
    }

    // Un pas en avant
    Cube step = { cur.x + forward.x, cur.y + forward.y, cur.z + forward.z };
    Vector2i g1 = Hex::cubeVersGrille(step);
    if (model.getCaseAt(g1) && !model.isOccupied(g1))
        res.push_back(g1);

    // Captures diagonales
    for (const auto& dir : Hex::directionsFou) {
        int dot = dir.x * forward.x + dir.y * forward.y + dir.z * forward.z;
        if (dot <= 0) continue;  // seules les diagonales vers l'avant
        Cube cap = { cur.x + dir.x, cur.y + dir.y, cur.z + dir.z };
        Vector2i g2 = Hex::cubeVersGrille(cap);
        Case* c = model.getCaseAt(g2);
        if (c) {
            Piece* p = model.getPieceAt(g2);
            if (p && p->getCouleur() != couleur)
                res.push_back(g2);
        }
    }

    return res;
}

string Pion::getTypeName() const {
    return "Pion";
}