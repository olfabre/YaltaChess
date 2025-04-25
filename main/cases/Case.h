#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Piece;

using Vec2 = Vector2f;

class Case : public Drawable
{
private:
    ConvexShape forme; // Quadrilatère
    bool estBlanc;
    Piece *piece;
    sf::Vector2i gridPos;

public:
    //Case(const vector<Vec2>& points, bool blanc);
    Case(const std::vector<sf::Vector2f>& points, bool blanc, sf::Vector2i gridPos);

    virtual ~Case();

    virtual void draw(RenderTarget &target, RenderStates states) const override;
    bool contientPoint(const Vector2f &point) const;
    sf::Vector2i getGridPos() const { return gridPos; }

    // Getters
    bool estOccupee() const { return piece != nullptr; }
    Piece *getPiece() const { return piece; }

    // Pour le highlight en survol
    const ConvexShape& getShape() const { return forme; }

    // Setters
    void setPiece(Piece *p) { piece = p; }
};

#endif
