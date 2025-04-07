#include "Case.h"
using namespace sf;
using namespace std;



Case::Case(const vector<Vector2f>& points, bool blanc)
        : estBlanc(blanc), piece(nullptr)
{
    forme.setPointCount(points.size());
    for(size_t i = 0; i < points.size(); ++i)
        forme.setPoint(i, points[i]);

    forme.setFillColor(estBlanc ? Color(235,235,208) : Color(119,148,85));
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
