#include "Tour.h"
#include "../cases/Case.h"
#include "../Model.h"
#include "../YaltaCoords.h"
#include <vector>

using namespace sf;
using namespace std;

Tour::Tour(Vector2i pos, Couleur coul) : Piece(pos, coul) {}

bool Tour::mouvementValide(Vector2i nouvellePos) const {
    // Cette fonction n'est pas utilisée pour getLegalMoves, donc nous la laissons telle quelle
    return (nouvellePos.x == position.x || nouvellePos.y == position.y)
           && !(nouvellePos == position);
}

void Tour::dessiner(RenderWindow& window) const {
    // Dessiner la Tour
}

vector<Vector2i> Tour::getLegalMoves(const Model& model) const {
    vector<Vector2i> res;

    // Utiliser les coordonnées cubiques pour les calculs
    Cube cur = YaltaCoords::gridToCube(position);

    // Parcourir les 6 directions principales (axes) de la tour dans un système hexagonal
    for (const auto& dir : YaltaCoords::rookDirections) {
        Cube nxt = cur;
        while (true) {
            // Avancer d'une case dans la direction actuelle
            nxt = { nxt.x + dir.x, nxt.y + dir.y, nxt.z + dir.z };
            Vector2i gridPos = YaltaCoords::cubeToGrid(nxt);

            // Vérifier si la case existe
            Case* c = model.getCaseAt(gridPos);
            if (!c) break; // Sortir de la boucle si on sort de l'échiquier

            // Vérifier si la case est occupée
            if (!model.isOccupied(gridPos)) {
                // Case vide, on peut y aller
                res.push_back(gridPos);
            } else {
                // Case occupée
                Piece* p = model.getPieceAt(gridPos);
                if (p && p->getCouleur() != couleur) {
                    // Pièce ennemie, on peut la capturer
                    res.push_back(gridPos);
                }
                // On ne peut pas aller plus loin dans cette direction
                break;
            }
        }
    }

    return res;
}

string Tour::getTypeName() const {
    return "Tour";
}
