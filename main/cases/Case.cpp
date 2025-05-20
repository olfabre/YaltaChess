#include "Case.h"
#include "../HexagonalCubique.h"
#include "../pieces/Piece.h"           // pour avoir la définition complète de Piece et de Couleur
#include <vector>


using namespace sf;
using namespace std;



Case::Case(const vector<Vector2f>& points, bool blanc, const Cube& cubePos)
     : estBlanc(blanc), piece(nullptr), cubePos(cubePos)
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
    bool inside = false;
    size_t n = forme.getPointCount();
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
        Vector2f p1 = forme.getPoint(i);
        Vector2f p2 = forme.getPoint(j);

        if (((p1.y > point.y) != (p2.y > point.y)) &&
            (point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x)) {
            inside = !inside;
        }
    }
    return inside;
}





