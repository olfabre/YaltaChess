#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Piece;

using Vec2 = sf::Vector2f;

class Case : public Drawable
{
private:
    ConvexShape forme; // Quadrilatère
    bool estBlanc;
    Piece *piece;

public:
    Case(const vector<Vec2>& points, bool blanc);
    virtual ~Case();

    virtual void draw(RenderTarget &target, RenderStates states) const override;
    bool contientPoint(const Vector2f &point) const;

    // Getters
    bool estOccupee() const { return piece != nullptr; }
    Piece *getPiece() const { return piece; }

    // Pour le highlight en survol
    const ConvexShape& getShape() const { return forme; }

    // Setters
    void setPiece(Piece *p) { piece = p; }
};

#endif
