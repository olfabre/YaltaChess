#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Model.h"
#include "cases/Case.h"

using namespace sf;
using namespace std;

class Model;
class YaltaChessView;

class Controller
{
private:
    Model &model;
    YaltaChessView &view;;
    //Piece* hoveredPiece = nullptr; // une pièce sous la souris ou pas alors null du pointeur(nullptr)
    Case* hoveredCase = nullptr;


public:
    Controller(Model &m, YaltaChessView &v);
    void handleEvent(const Event &event);
};

#endif
