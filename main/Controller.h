#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "HexagonalCubique.h"  // pour Cube
#include <SFML/Graphics.hpp>
#include "pieces/Piece.h"
#include "Model.h"
#include "View.h"
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
    Case* selectedCase = nullptr;
    Piece*   selectedPiece = nullptr;   // pièce en cours de sélection
    std::vector<Cube> legalMoves;    // ses coups légaux


public:
    Controller(Model &m, YaltaChessView &v);
    void handleEvent(const Event &event);
};

#endif
