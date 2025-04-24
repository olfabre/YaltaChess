#ifndef ROI_H
#define ROI_H

#include "Piece.h"
using namespace sf;
using namespace std;

// Classe Roi héritant de Piece
class Roi : public Piece {
public:
    Roi(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;
    string getTypeName() const override { return "Roi"; }
};

#endif
