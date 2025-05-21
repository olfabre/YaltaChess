#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Model.h"
#include "pieces/Piece.h"
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
    Case* selectedCase = nullptr;
    RenderWindow &window;
    const Model &model;
    Clock blinkClock; // mesure le temps pour le clignotement
    sf::View boardView;

    // police et labels bordure
    Font coordFont;
    vector<Text> borderLabels;

    void initBorderLabels();
    // helper pour convertir une position grille (x,y) en pixel centre de case
    Vector2f gridToPixel(const Vector2i &g) const;
    // même conversion **sans** la rotation appliquée dans gridToPixel()
    Vector2f gridToPixelRaw(const Vector2i &g) const;
    vector<Case*> highlightedCases;

public:
    YaltaChessView(RenderWindow &win, const Model &mod);
    RenderWindow& getWindow() { return window; }
    //void setHoveredPiece(Piece* p) { hoveredPiece = p; }
    void setHoveredCase(Case* c)  { hoveredCase = c; }
    void setSelectedCase(Case* c) { selectedCase = c; }
    void clearHighlights() { highlightedCases.clear(); }
    void draw();
    void setHighlightedCases(const std::vector<Case*>& cases);
    const sf::View& getBoardView() const { return boardView; }
};

#endif
