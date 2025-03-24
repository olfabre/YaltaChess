#ifndef CAVALIER_H
#define CAVALIER_H

#include "Piece.h"

// Classe Cavalier héritant de Piece
class Cavalier : public Piece {
public:
    Cavalier(sf::Vector2i pos, Couleur coul);
    bool mouvementValide(sf::Vector2i nouvellePos) const override;
    void dessiner(sf::RenderWindow& window) const override;
};

#endif
