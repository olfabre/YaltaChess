// Case.h (correction)
#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>
#include "../pieces/Piece.h"

class Case {
private:
    sf::Vector2i position;
    Piece* piece; // Pointeur vers une pièce ou nullptr

public:
    Case(sf::Vector2i pos);

    bool estOccupee() const;
    Piece* getPiece() const;
    void setPiece(Piece* p);
    sf::Vector2i getPosition() const;

    // Correction : ajout de const ici
    void dessiner(sf::RenderWindow& window) const;
};

#endif
