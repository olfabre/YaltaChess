#include "Cavalier.h"
#include "../cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
#include <array>
#include <cmath>

using namespace sf;
using namespace std;



Cavalier::Cavalier(Cube pos, Couleur coul) : Piece(pos, coul) {}

bool Cavalier::mouvementValide(Cube nouvellePos) const {
    int dx = abs(nouvellePos.x - positionCube.x);
    int dy = abs(nouvellePos.y - positionCube.y);
    int dz = abs(nouvellePos.z - positionCube.z);
    // … test en cube …
    return true;
}

void Cavalier::dessiner(RenderWindow& window) const {
    // Dessiner le Cavalier
}



vector<Cube> Cavalier::getLegalMoves(const Model& model) const {
    return Hex::movesCavalier(positionCube, model, couleur);
}



// implémentation du nom
string Cavalier::getTypeName() const {
        return "Cavalier";
    }


