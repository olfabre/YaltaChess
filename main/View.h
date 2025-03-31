#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

class Model;

class View
{
private:
    sf::RenderWindow &window;
    const Model &model;

public:
    View(sf::RenderWindow &win, const Model &mod);
    void draw();
};

#endif
