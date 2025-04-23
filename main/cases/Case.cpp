#include "Case.h"
using namespace sf;
using namespace std;



Case::Case(const vector<Vector2f>& points, bool blanc)
        : estBlanc(blanc), piece(nullptr)
{
    forme.setPointCount(points.size());
    for(size_t i = 0; i < points.size(); ++i)
        forme.setPoint(i, points[i]);

    forme.setFillColor(estBlanc ? Color(233,208,167) : Color(253,247,231));
    forme.setOutlineColor(Color::Black);
    forme.setOutlineThickness(2.f);
}

Case::~Case() {}

void Case::draw(RenderTarget &target, RenderStates states) const
{
    target.draw(forme, states);
}

bool Case::contientPoint(const Vector2f &point) const
{
    return forme.getGlobalBounds().contains(point);
}
