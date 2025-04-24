#ifndef CAVALIER_H
#define CAVALIER_H

#include "Piece.h"
using namespace sf;
using namespace std;

// Classe Cavalier héritant de Piece
class Cavalier : public Piece {
public:
    Cavalier(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;
    string getTypeName() const override { return "Cavalier"; }
};

#endif
