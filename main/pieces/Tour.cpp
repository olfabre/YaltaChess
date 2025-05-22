#include "Tour.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../HexagonalCubique.h"  // Utilisation exclusive de Hex pour les conversions
#include <vector>
#include <array>
#include <cmath>
#include <iostream>  // pour std::cout
#include "CubeToLabel.h"   // pour convertir Cube → "A1", "J7", etc.

using namespace sf;
using namespace std;

Tour::Tour(Cube pos, Couleur coul, Model* modelPtr) : Piece(pos, coul) {
    this->modelPtr = modelPtr;
}

bool Tour::mouvementValide(Cube nouvellePos) const {
    auto mouvements = Hex::mouvementsTour(positionCube, *modelPtr, couleur);
    return std::find(mouvements.begin(), mouvements.end(), nouvellePos) != mouvements.end();
}

void Tour::dessiner(RenderWindow& window) const {
    // Dessiner la Tour
}

vector<Cube> Tour::getLegalMoves(const Model& model) const {
    auto mouvements = Hex::mouvementsTour(positionCube, model, couleur);
    
    std::cout << "Mouvements légaux Tour = ";
    for(const Cube& m : mouvements) std::cout << cubeToLabel(m) << ' ';
    std::cout << '\n';
    
    return mouvements;
}

string Tour::getTypeName() const {
    return "Tour";
}
