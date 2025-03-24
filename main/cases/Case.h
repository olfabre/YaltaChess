#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>
#include "../pieces/Piece.h"

class Case {
private:
    sf::ConvexShape forme;
    Piece* piece;

public:
    Case(const std::vector<sf::Vector2f>& points, sf::Color couleur);

    bool estOccupee() const;
    Piece* getPiece() const;
    void setPiece(Piece* p);

    void dessiner(sf::RenderWindow& window) const;
};

#endif
