#include "Case.h"

Case::Case(const std::vector<sf::Vector2f>& points, sf::Color couleur) : piece(nullptr) {
    forme.setPointCount(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        forme.setPoint(i, points[i]);
    }
    forme.setFillColor(couleur);  // Utiliser la couleur passée en paramètre
    forme.setOutlineThickness(1.f);
    forme.setOutlineColor(sf::Color::Black);
}

bool Case::estOccupee() const { return piece != nullptr; }
Piece* Case::getPiece() const { return piece; }
void Case::setPiece(Piece* p) { piece = p; }

void Case::dessiner(sf::RenderWindow& window) const {
    window.draw(forme);
    if (piece)
        piece->dessiner(window);
}
