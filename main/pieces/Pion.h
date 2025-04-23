#ifndef PION_H
#define PION_H

#include "Piece.h"
using namespace sf;
using namespace std;

// Classe Pion héritant de Piece
class Pion : public Piece {
public:
    Pion(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;
};

#endif
