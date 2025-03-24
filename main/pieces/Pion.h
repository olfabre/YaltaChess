#ifndef PION_H
#define PION_H

#include "Piece.h"

// Classe Pion héritant de Piece
class Pion : public Piece {
public:
    Pion(sf::Vector2i pos, Couleur coul);
    bool mouvementValide(sf::Vector2i nouvellePos) const override;
    void dessiner(sf::RenderWindow& window) const override;
};

#endif
