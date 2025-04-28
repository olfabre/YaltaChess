#ifndef CASE_H
#define CASE_H

#include <SFML/Graphics.hpp>
#include "Piece.h"           // pour avoir la définition complète de Piece et de Couleur
#include <vector>
#include <string>
#include <utility>

enum Couleur { BLANC, NOIR, ROUGE };

// forward-déclaration pour pouvoir manipuler des Piece*
class Piece;

using namespace sf;
using namespace std;

Piece *piece;



using Vec2 = Vector2f;

enum Side { White=0, Red=1, Black=2 };

class Case : public Drawable
{
private:
    ConvexShape forme; // Quadrilatère
    bool estBlanc;
    Piece *piece;
    sf::Vector2i gridPos;
    // --- NOUVEAUX MEMBRES pour la topo du plateau ---
    Side side = White;      // Le « groupe » (White, Red ou Black) dont fait partie cette case
    Case* N = nullptr;      // voisin Nord (du point de vue de `side`)
    Case* E = nullptr;      // voisin Est
    Case* S = nullptr;      // voisin Sud
    Case* W = nullptr;      // voisin Ouest

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

    /**
     * Parcourt un chemin relatif (ex: "NNE" ou "SW") depuis cette case.
     * @param path    : chaîne de directions parmi 'N','E','S','W'
     * @param reverse : si true, on inverse N<->S et E<->W au premier changement de side
     * @param out     : vecteur de paires (Case* destination, bool reverseFinal)
     *                  pour chaque extrémité atteinte, avec l’état de reverse correspondant.
     */
    void walk(const std::string& path,
              bool reverse,
              std::vector<std::pair<Case*,bool>>& out) const;


      /**
     * Calcule toutes les cases atteignables depuis *this* selon un jeu de directions.
     * @param playerColor : couleur du joueur (Couleur)
     * @param directions : vecteur de chaînes (ex. {"N","E","S","W"} pour une tour)
     * @param limit      : nombre max d’itérations dans chaque direction
     * @param mayCapture : autorise les cases occupées pour capture
     * @param mustCapture: n’autorise que les cases occupées
     * @return vecteur de Case* atteignables
     */
     //vector<Case*> targets(Couleur playerColor, const std::vector<std::string>& directions, int limit = 10, bool mayCapture = true, bool mustCapture = false) const;
     vector<Case*> targets(Couleur playerColor, const std::vector<std::string>& directions, int limit = 10, bool mayCapture = true, bool mustCapture = false) const;
};

#endif
