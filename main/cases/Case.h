#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>

class Piece;

class Case : public sf::Drawable
{
private:
    sf::RectangleShape forme;
    sf::Vector2f position;
    bool estBlanc;
    Piece *piece;
    static constexpr float TAILLE_CASE = 60.f;

public:
    Case(const sf::Vector2f &pos, bool blanc);
    virtual ~Case();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    bool contientPoint(const sf::Vector2f &point) const;
    void surbrillance(bool actif);

    // Getters
    const sf::Vector2f &getPosition() const { return position; }
    bool estOccupee() const { return piece != nullptr; }
    Piece *getPiece() const { return piece; }

    // Setters
    void setPiece(Piece *p) { piece = p; }
};

#endif