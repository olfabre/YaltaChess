#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Model.h"
#include "Piece.h"
#include "cases/Case.h"
#include <vector>

using namespace sf;
using namespace std;

class Model;

class YaltaChessView
{
private:
    //Piece* hoveredPiece = nullptr; // une pièce sous la souris ou pas alors null du pointeur(nullptr)
    Case* hoveredCase = nullptr;
    RenderWindow &window;
    const Model &model;
    Clock blinkClock; // mesure le temps pour le clignotement

    // police et labels bordure
    Font coordFont;
    vector<Text> borderLabels;

    void initBorderLabels();
    // helper pour convertir une position grille (x,y) en pixel centre de case
    Vector2f gridToPixel(const Vector2i &g) const;
    vector<Case*> highlightedCases;

public:
    YaltaChessView(RenderWindow &win, const Model &mod);
    RenderWindow& getWindow() { return window; }
    //void setHoveredPiece(Piece* p) { hoveredPiece = p; }
    void setHoveredCase(Case* c)  { hoveredCase = c; }
    void setHighlightedCases(const std::vector<Case*>& c) { highlightedCases = c; }
    void clearHighlights() { highlightedCases.clear(); }
    void draw();
};

#endif
