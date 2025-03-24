#ifndef FOU_H
#define FOU_H

#include "Piece.h"

// Classe Fou héritant de Piece
class Fou : public Piece {
public:
    Fou(sf::Vector2i pos, Couleur coul);
    bool mouvementValide(sf::Vector2i nouvellePos) const override;
    void dessiner(sf::RenderWindow& window) const override;
};

#endif
