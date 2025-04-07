#include "Case.h"




Case::Case(const std::vector<sf::Vector2f>& points, bool blanc)
        : estBlanc(blanc), piece(nullptr)
{
    forme.setPointCount(points.size());
    for(size_t i = 0; i < points.size(); ++i)
        forme.setPoint(i, points[i]);

    forme.setFillColor(estBlanc ? sf::Color(235,235,208) : sf::Color(119,148,85));
}

Case::~Case() {}

void Case::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(forme, states);
}

bool Case::contientPoint(const sf::Vector2f &point) const
{
    return forme.getGlobalBounds().contains(point);
}
