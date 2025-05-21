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

// Définition quelque part en scope global ou static dans Pion.cpp
static const std::array<Cube,3> dirAvance = {
        Cube{+1,  0, -1},   // pour BLANC
        Cube{ 0, +1, -1},   // pour ROUGE
        Cube{-1,  0, +1}    // pour NOIR
};
static const std::array<std::array<Cube,2>,3> dirCapture = {{
                                                                    { Cube{+1,-1, 0}, Cube{ 0,-1,+1} },  // capturer pour BLANC
                                                                    { Cube{+1, 0,-1}, Cube{-1,+1, 0} },  // pour ROUGE
                                                                    { Cube{ 0,+1,-1}, Cube{-1, 0,+1} }   // pour NOIR
                                                            }};

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
    std::cout << "[getLegalMoves] posCube=(" << positionCube.x << "," 
              << positionCube.y << "," << positionCube.z 
              << ") couleur=" << static_cast<int>(couleur) << "\n";
    return Hex::movesPion(positionCube, model, couleur);
}

string Pion::getTypeName() const {
    return "Pion";
}