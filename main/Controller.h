#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Model;
class YaltaChessView;

class Controller
{
private:
    Model &model;
    YaltaChessView &view;;

public:
    Controller(Model &m, YaltaChessView &v);
    void handleEvent(const Event &event);
};

#endif
