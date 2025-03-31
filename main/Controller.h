#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

// Forward declarations
class Model;
class View;

class Controller
{
private:
    Model &model;
    View &view;

public:
    Controller(Model &m, View &v);
    void handleEvent(const sf::Event &event);
};

#endif