#ifndef TOUR_H
#define TOUR_H

#include "Piece.h"

// Classe Tour héritant de Piece
class Tour : public Piece {
public:
    Tour(sf::Vector2i pos, Couleur coul);
    bool mouvementValide(sf::Vector2i nouvellePos) const override;
    void dessiner(sf::RenderWindow& window) const override;
};

#endif
