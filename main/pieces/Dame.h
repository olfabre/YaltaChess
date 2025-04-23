#ifndef DAME_H
#define DAME_H

#include "Piece.h"
using namespace sf;
using namespace std;

// Classe Dame héritant de Piece
class Dame : public Piece {
public:
    Dame(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;
};

#endif
