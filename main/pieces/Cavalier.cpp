#include "Cavalier.h"
#include "../cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
#include <iostream>  // pour std::cout
#include "CubeToLabel.h"   // pour convertir Cube → "A1", "J7", etc.

using namespace sf;
using namespace std;



Cavalier::Cavalier(Cube pos, Couleur coul, Model* modelPtr) : Piece(pos, coul) {
    this->modelPtr = modelPtr;
}

bool Cavalier::mouvementValide(Cube nouvellePos) const {
    auto mouvements = Hex::mouvementsCavalier(positionCube, *modelPtr, couleur);
    return std::find(mouvements.begin(), mouvements.end(), nouvellePos) != mouvements.end();
}

void Cavalier::dessiner(RenderWindow& window) const {
    // Dessiner le Cavalier
}



vector<Cube> Cavalier::getLegalMoves(const Model& model) const {
    auto mouvements = Hex::mouvementsCavalier(positionCube, model, couleur);
    
    std::cout << "Mouvements légaux Cavalier = ";
    for(const Cube& m : mouvements) std::cout << cubeToLabel(m) << ' ';
    std::cout << '\n';
    
    return mouvements;
}



// implémentation du nom
string Cavalier::getTypeName() const {
        return "Cavalier";
    }


