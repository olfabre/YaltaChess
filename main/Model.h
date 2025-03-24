#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "cases/Case.h"
#include "pieces/Piece.h"

class Model {
private:
    std::vector<Case> echiquier;  // 96 cases pour Yalta
    std::vector<std::unique_ptr<Piece>> pieces; // Pièces dynamiques

    void initialiserEchiquierYalta(); // Initialisation spécifique Yalta

public:
    Model();
    void update();

    const std::vector<Case>& getEchiquier() const;
};

#endif
