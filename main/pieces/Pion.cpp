#include "Pion.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../HexagonalCubique.h"  // on utilise les coordonnées cube
#include <vector>
#include <array>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

//Pion::Pion(Cube pos, Couleur coul) : Piece(pos, coul) {}
Pion::Pion(Cube pos, Couleur coul, Model* modelPtr)
        : Piece(pos, coul)
{
    this->modelPtr = modelPtr;
}

void Pion::dessiner(RenderWindow& window) const {
    // Dessiner le Pion
}

bool Pion::mouvementValide(Cube nouvellePos) const
{
    auto moves = Hex::movesPion(positionCube, *modelPtr, couleur);
    return std::find(moves.begin(), moves.end(), nouvellePos) != moves.end();
}



vector<Cube> Pion::getLegalMoves(const Model& model) const {
    //return Hex::movesPion(positionCube, model, couleur);

    std::vector<Cube> moves;
    Cube pos = this->getPositionCube();
    int couleur = this->getCouleur();

    Case* caseAssociee = model.getCaseAtCube(pos);
    if (caseAssociee) {
        std::cout << "[getLegalMoves] Case de la pièce : cube("
                  << caseAssociee->getCubePos().x << ","
                  << caseAssociee->getCubePos().y << ","
                  << caseAssociee->getCubePos().z << ") "
                  << "side=" << caseAssociee->getSide()
                  << " type=" << (caseAssociee->getPiece() ? caseAssociee->getPiece()->getTypeName() : "Aucune")
                  << std::endl;
    }
    std::cout << "[getLegalMoves] Position interne de la pièce : cube("
              << pos.x << "," << pos.y << "," << pos.z << ") "
              << "couleur=" << this->getCouleur()
              << " type=" << this->getTypeName()
              << std::endl;

    // *** Exemple de logique simple, à personnaliser selon ton hexagone ***
    if (couleur == 0) { // BLANC
        Cube dest = {pos.x + 1, pos.y - 0, pos.z};
        Case* target = model.getCaseAtCube(dest);
        if (target && !target->getPiece())
            moves.push_back(dest);
    } else if (couleur == 1) { // ROUGE
        Cube dest = {pos.x, pos.y + 1, pos.z - 1};
        Case* target = model.getCaseAtCube(dest);
        if (target && !target->getPiece())
            moves.push_back(dest);
    } else if (couleur == 2) { // NOIR
        Cube dest = {pos.x - 1, pos.y, pos.z + 1};
        Case* target = model.getCaseAtCube(dest);
        if (target && !target->getPiece())
            moves.push_back(dest);
    }
    // Pour l’instant, on fait juste "avance simple" (à améliorer après)
    return moves;

}

string Pion::getTypeName() const {
    return "Pion";
}