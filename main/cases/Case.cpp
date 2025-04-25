#include "Case.h"
using namespace sf;
using namespace std;



Case::Case(const vector<Vector2f>& points, bool blanc, Vector2i gridPos)
        : estBlanc(blanc), piece(nullptr), gridPos(gridPos)
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
    //return forme.getGlobalBounds().contains(point);
    // Comme nos ConvexShape stockent déjà les sommets
    // en coordonnées monde (pas de transform), on peut
    // directement faire un test "cross-product" pour un
    // polygone convexe.

    size_t n = forme.getPointCount();
    bool hasPos = false, hasNeg = false;

    for (size_t i = 0; i < n; ++i)
    {
        // récupération des deux sommets de l’arête
        Vector2f a = forme.getPoint(i);
        Vector2f b = forme.getPoint((i + 1) % n);

        // on calcule le cross produit (b–a) × (point–a)
        float cross = (b.x - a.x) * (point.y - a.y)
                      - (b.y - a.y) * (point.x - a.x);

        if (cross > 0)  hasPos = true;
        else if (cross < 0)  hasNeg = true;

        // si on a des signes différents, point hors polygone
        if (hasPos && hasNeg)
            return false;
    }
    return true;
}
