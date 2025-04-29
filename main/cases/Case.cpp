#include "Case.h"
#include "Piece.h"           // pour avoir la définition complète de Piece et de Couleur
#include <vector>
#include <string>
#include <utility>
#include <algorithm>  // pour std::reverse

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

void Case::walk(const std::string& path,
                bool reverse,
                std::vector<std::pair<Case*,bool>>& out) const
{
    // mapping N<->S, E<->W quand on inverse
    auto nextDir = [&](Case const* cur, char step, bool rev) -> Case* {
        switch(step) {
            case 'N': return rev ? cur->getSouth() : cur->getNorth();
            case 'E': return rev ? cur->getWest()  : cur->getEast();
            case 'S': return rev ? cur->getNorth() : cur->getSouth();
            case 'W': return rev ? cur->getEast()  : cur->getWest();
        }
        return nullptr;
    };

    const std::string revPath = [&](){
        string s = path;
        std::reverse(s.begin(), s.end());
        return s;
    }();

    // si path est palindrome, on n’a qu’à l’essayer une fois
    auto tryOne = [&](const std::string& p){
        Case const* prev = nullptr;
        Case const* cur  = this;
        bool revState = reverse;
        for(char step : p) {
            Case const* nxt = nextDir(cur, step, revState);
            if (!nxt || nxt == prev) return;  // hors plateau ou boucle
            // si on change de half-board, on inverse revState
            if (nxt->getSide() != cur->getSide())
                revState = !revState;
            prev = cur;
            cur  = nxt;
        }
        out.emplace_back(const_cast<Case*>(cur), revState);
    };

    tryOne(path);
    if (path != revPath)
        tryOne(revPath);
}



std::vector<Case*> Case::targets(Couleur playerColor,
                                 const std::vector<std::string>& directions,
                                 int limit,
                                 bool mayCapture,
                                 bool mustCapture) const
{
    // on inverse les directions si le joueur n’est pas sur ce side
    bool rev = (playerColor != Couleur(getSide()));
    struct Frame { const Case* c; bool rev; const std::string* path; int lim; };
    std::vector<Case*> result;
    std::vector<Frame> stack;

    // un frame par direction
    for (auto& dir : directions)
        stack.push_back({ this, rev, &dir, limit });

    while (!stack.empty()) {
        auto f = stack.back(); stack.pop_back();

        // on calcule toutes les extrémités atteintes pour ce chemin
        std::vector<std::pair<Case*,bool>> ends;
        f.c->walk(*f.path, f.rev, ends);

        for (auto [dst, rev2] : ends) {
            Piece* occ = dst->getPiece();
            bool occupiedByEnemy = occ && occ->getCouleur() != playerColor;

            // filtrage
            if ((occupiedByEnemy && mayCapture) || (!occ && !mustCapture))
                result.push_back(dst);

            // si pas de pièce et qu’on peut continuer la glissade
            if (f.lim > 1 && !occ)
                stack.push_back({ dst, rev2, f.path, f.lim - 1 });
        }
    }
    return result;
}