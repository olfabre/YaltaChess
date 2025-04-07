#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Model;

class YaltaChessView
{
private:
    RenderWindow &window;
    const Model &model;

public:
    YaltaChessView(RenderWindow &win, const Model &mod);
    void draw();
};

#endif
