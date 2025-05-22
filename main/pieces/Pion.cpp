#include "Pion.h"
#include "../cases/Case.h"
#include "../Model.h"
#include <vector>
#include <array>
#include <iostream>
#include "CubeToLabel.h"   // pour convertir Cube → "A1", "J7", etc.


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

    auto moves = Hex::movesPion(positionCube, model, couleur);   // ← récupère les coups légaux

    std::cout << "Legal moves = ";
    for(const Cube& m : moves) std::cout << cubeToLabel(m) << ' ';
    std::cout << '\n';
/*
    std::cout << "[getLegalMoves] posCube=(" << positionCube.x << ","
              << positionCube.y << "," << positionCube.z
              << ") couleur=" << static_cast<int>(couleur) << "\n";
*/


    return moves;   // ← on renvoie quand même la liste au reste du programme
}

string Pion::getTypeName() const {
    return "Pion";
}