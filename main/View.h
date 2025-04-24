#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include "Model.h"
#include <vector>
using namespace sf;
using namespace std;

class Model;

class YaltaChessView
{
private:
    RenderWindow &window;
    const Model &model;

    // police et labels bordure
    Font coordFont;
    vector<Text> borderLabels;

    void initBorderLabels();
    // helper pour convertir une position grille (x,y) en pixel centre de case
    Vector2f gridToPixel(const Vector2i &g) const;

public:
    YaltaChessView(RenderWindow &win, const Model &mod);
    void draw();
};

#endif
