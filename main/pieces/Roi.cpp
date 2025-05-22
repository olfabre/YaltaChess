#include "Roi.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../HexagonalCubique.h"  // on utilise les coordonnées cube
#include <vector>
#include <array>
#include <cmath>
#include <iostream>  // pour std::cout
#include "CubeToLabel.h"   // pour convertir Cube → "A1", "J7", etc.

using namespace sf;
using namespace std;

Roi::Roi(Cube pos, Couleur coul, Model* modelPtr) : Piece(pos, coul) {
    this->modelPtr = modelPtr;
}

bool Roi::mouvementValide(Cube nouvellePos) const {
    auto mouvements = Hex::mouvementsRoi(positionCube, *modelPtr, couleur);
    return std::find(mouvements.begin(), mouvements.end(), nouvellePos) != mouvements.end();
}

void Roi::dessiner(RenderWindow& window) const {
    // Ici, dessiner le Roi (sprite ou forme)
}

vector<Cube> Roi::getLegalMoves(const Model& model) const {
    auto mouvements = Hex::mouvementsRoi(positionCube, model, couleur);
    
    std::cout << "Mouvements légaux Roi = ";
    for(const Cube& m : mouvements) std::cout << cubeToLabel(m) << ' ';
    std::cout << '\n';
    
    return mouvements;
}

string Roi::getTypeName() const {
    return "Roi";
}