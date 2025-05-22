#include "Fou.h"
#include "../cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
#include <array>
#include <cmath>
#include <iostream>  // pour std::cout
#include "CubeToLabel.h"   // pour convertir Cube → "A1", "J7", etc.

using namespace sf;
using namespace std;

Fou::Fou(Cube pos, Couleur coul, Model* modelPtr) : Piece(pos, coul) {
    this->modelPtr = modelPtr;
}

bool Fou::mouvementValide(Cube nouvellePos) const {
    auto mouvements = Hex::mouvementsFou(positionCube, *modelPtr, couleur);
    return std::find(mouvements.begin(), mouvements.end(), nouvellePos) != mouvements.end();
}

void Fou::dessiner(RenderWindow& window) const {
    // Dessiner le Fou
}

vector<Cube> Fou::getLegalMoves(const Model& model) const {
    auto mouvements = Hex::mouvementsFou(positionCube, model, couleur);
    
    std::cout << "Mouvements légaux Fou = ";
    for(const Cube& m : mouvements) std::cout << cubeToLabel(m) << ' ';
    std::cout << '\n';
    
    return mouvements;
}

string Fou::getTypeName() const {
    return "Fou";
}