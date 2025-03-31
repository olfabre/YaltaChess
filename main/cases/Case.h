#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Piece;

class Case : public sf::Drawable
{
private:
    sf::ConvexShape forme; // Quadrilatère
    bool estBlanc;
    Piece *piece;

public:
    Case(const std::vector<sf::Vector2f>& points, bool blanc);
    virtual ~Case();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    bool contientPoint(const sf::Vector2f &point) const;

    // Getters
    bool estOccupee() const { return piece != nullptr; }
    Piece *getPiece() const { return piece; }

    // Setters
    void setPiece(Piece *p) { piece = p; }
};

#endif
