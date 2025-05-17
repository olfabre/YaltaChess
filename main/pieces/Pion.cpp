#include "Pion.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../HexagonalCubique.h"  // on utilise les coordonnées cube
#include <vector>
#include <array>
#include <cmath>

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
    return Hex::movesPion(positionCube, model, couleur);
}

string Pion::getTypeName() const {
    return "Pion";
}