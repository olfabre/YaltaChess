#include "Case.h"

Case::Case(sf::Vector2i pos) : position(pos), piece(nullptr) {}

bool Case::estOccupee() const { return piece != nullptr; }

Piece* Case::getPiece() const { return piece; }

void Case::setPiece(Piece* p) { piece = p; }

sf::Vector2i Case::getPosition() const { return position; }

// Correction ici :
void Case::dessiner(sf::RenderWindow& window) const {
    sf::RectangleShape carre({100.f, 100.f});
    carre.setPosition(sf::Vector2f(position.x * 100.f, position.y * 100.f));
    carre.setFillColor((position.x + position.y) % 2 ? sf::Color(209,139,71) : sf::Color(255,206,158));
    window.draw(carre);
}
