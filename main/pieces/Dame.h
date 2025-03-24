#ifndef DAME_H
#define DAME_H

#include "Piece.h"

// Classe Dame héritant de Piece
class Dame : public Piece {
public:
    Dame(sf::Vector2i pos, Couleur coul);
    bool mouvementValide(sf::Vector2i nouvellePos) const override;
    void dessiner(sf::RenderWindow& window) const override;
};

#endif
