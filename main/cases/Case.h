#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>
#include "../HexagonalCubique.h"
#include "../Couleur.h"
#include "../pieces/Piece.h"           // pour avoir la définition complète de Piece et de Couleur
#include <vector>
#include <string>
#include <utility>

// forward-déclaration pour pouvoir manipuler des Piece*
class Piece;

using namespace sf;
using namespace std;

using Vec2 = Vector2f;

enum Side { White=0, Red=1, Black=2 };

class Case : public Drawable
{
private:
    std::vector<sf::Vector2f> points;
    ConvexShape forme; // Quadrilatère
    bool estBlanc;
    Piece *piece;
    Cube cubePos;
    // --- NOUVEAUX MEMBRES pour la topo du plateau ---
    Side side = White;      // Le « groupe » (White, Red ou Black) dont fait partie cette case
    Case* N = nullptr;      // voisin Nord (du point de vue de `side`)
    Case* E = nullptr;      // voisin Est
    Case* S = nullptr;      // voisin Sud
    Case* W = nullptr;      // voisin Ouest

public:
    //Case(const vector<Vec2>& points, bool blanc);
    Case(const vector<Vec2>& points, bool blanc, const Cube& cubePos);

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

    // — setter/getter pour le side
    void setSide(Side s) { side = s; }
    Side getSide() const { return side; }

    // — setters pour les voisins
    void setNorth(Case* c) { N = c; }
    void setEast (Case* c) { E = c; }
    void setSouth(Case* c) { S = c; }
    void setWest (Case* c) { W = c; }

    // — getters pour les voisins (utiles ensuite)
    Case* getNorth() const { return N; }
    Case* getEast()  const { return E; }
    Case* getSouth() const { return S; }
    Case* getWest()  const { return W; }


    // nouveaux getters (tout gérer cube)
    // nouveau
    const Cube& getCubePos() const { return cubePos; }
    // utilitaire IHM si tu veux encore des grid :
    Vector2i getGridPos() const { return Hex::cubeVersGrille(cubePos); }



};

#endif
