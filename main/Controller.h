#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

class Model;
class YaltaChessView;

class Controller
{
private:
    Model &model;
    YaltaChessView &view;;

public:
    Controller(Model &m, YaltaChessView &v);
    void handleEvent(const sf::Event &event);
};

#endif
