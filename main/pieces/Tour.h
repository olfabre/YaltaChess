#ifndef TOUR_H
#define TOUR_H

#include "Piece.h"
#include <vector>

using namespace sf;
using namespace std;

class Model;  // forward declaration

// Classe Tour héritant de Piece
class Tour : public Piece {
public:
    Tour(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;

    // génère tous les déplacements valides en glissant
    vector<Vector2i> getLegalMoves(const Model& model) const override;

    // nom pour identification / chargement texture
    string getTypeName() const override;
};

#endif
