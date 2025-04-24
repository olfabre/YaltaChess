#ifndef FOU_H
#define FOU_H

#include "Piece.h"
using namespace sf;
using namespace std;

// Classe Fou héritant de Piece
class Fou : public Piece {
public:
    Fou(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;
    string getTypeName() const override { return "Fou"; }
};

#endif
