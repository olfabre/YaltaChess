#ifndef TOUR_H
#define TOUR_H

#include "Piece.h"
using namespace sf;
using namespace std;

// Classe Tour héritant de Piece
class Tour : public Piece {
public:
    Tour(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;
    string getTypeName() const override { return "Tour"; }
};

#endif
