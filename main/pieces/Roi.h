#ifndef ROI_H
#define ROI_H

#include "Piece.h"

// Classe Roi héritant de Piece
class Roi : public Piece {
public:
    Roi(sf::Vector2i pos, Couleur coul);
    bool mouvementValide(sf::Vector2i nouvellePos) const override;
    void dessiner(sf::RenderWindow& window) const override;
};

#endif
