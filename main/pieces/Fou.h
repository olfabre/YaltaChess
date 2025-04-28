#ifndef FOU_H
#define FOU_H

#include "Piece.h"
#include <vector>

using namespace sf;
using namespace std;

class Model;  // forward declaration

// Classe Fou héritant de Piece
class Fou : public Piece {
public:
    Fou(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;

    // génération des coups légaux
    vector<Vector2i> getLegalMoves(const Model& model) const override;

    // nom pour l’infrastructure
    string getTypeName() const override;
};

#endif
