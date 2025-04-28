#include "Pion.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../YaltaCoords.h"
#include <vector>

using namespace sf;
using namespace std;

Pion::Pion(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

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

void Pion::dessiner(RenderWindow& window) const {
    // Dessiner le Pion
}

vector<Vector2i> Pion::getLegalMoves(const Model& model) const {
    vector<Vector2i> res;

    // Utiliser les coordonnées cubiques pour les calculs
    Cube cur = YaltaCoords::gridToCube(position);

    // Direction "avant" pour cette couleur
    Cube forward = YaltaCoords::rookDirections[YaltaCoords::pawnForwardIndex[couleur]];

    // Avancer d'une case
    Cube oneStep = { cur.x + forward.x, cur.y + forward.y, cur.z + forward.z };
    Vector2i g1 = YaltaCoords::cubeToGrid(oneStep);

    // Vérifier si la case existe et est vide
    if (model.getCaseAt(g1) && !model.isOccupied(g1)) {
        res.push_back(g1);
    }

    // Captures diagonales
    for (const auto& diagDir : YaltaCoords::bishopDirections) {
        // Calculer le produit scalaire pour déterminer si la direction est "vers l'avant"
        int dotProduct = diagDir.x * forward.x + diagDir.y * forward.y + diagDir.z * forward.z;

        if (dotProduct > 0) { // Direction diagonale vers l'avant
            Cube captureCube = { cur.x + diagDir.x/2, cur.y + diagDir.y/2, cur.z + diagDir.z/2 };
            Vector2i g2 = YaltaCoords::cubeToGrid(captureCube);

            // Vérifier si la case existe et contient une pièce ennemie
            Piece* targetPiece = model.getPieceAt(g2);
            if (targetPiece && targetPiece->getCouleur() != couleur) {
                res.push_back(g2);
            }
        }
    }

    return res;
}

string Pion::getTypeName() const {
    return "Pion";
}