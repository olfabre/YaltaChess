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

public:
    YaltaChessView(RenderWindow &win, const Model &mod);
    void draw();
};

#endif
