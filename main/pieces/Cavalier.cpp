#include "Cavalier.h"
#include "../cases/Case.h"   // pour .getGridPos() et .targets()
#include "../Model.h"
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <vector>
#include <array>
#include <cmath>

using namespace sf;
using namespace std;



Cavalier::Cavalier(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Cavalier::mouvementValide(Vector2i nouvellePos) const {
    int dx = abs(nouvellePos.x - position.x);
    int dy = abs(nouvellePos.y - position.y);
    return ((dx == 1 && dy == 2) || (dx == 2 && dy == 1));
}

void Cavalier::dessiner(RenderWindow& window) const {
    // Dessiner le Cavalier
}







vector<Vector2i> Cavalier::getLegalMoves(const Model& model) const {
    return Hex::movesCavalier(position, model, couleur);
}



// implémentation du nom
string Cavalier::getTypeName() const {
        return "Cavalier";
    }


