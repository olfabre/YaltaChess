#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include "Model.h"

class View
{
private:
    sf::RenderWindow &window;
    Model &model;

public:
    View(sf::RenderWindow &win, Model &mod) : window(win), model(mod) {}
    void draw();
};

#endif // VIEW_H