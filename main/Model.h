#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "cases/Case.h"
#include "pieces/Piece.h"

class Model {
private:
    std::vector<std::vector<Case>> echiquier; // 12x8 = 96 cases
    std::vector<std::unique_ptr<Piece>> pieces; // gestion dynamique des pièces

public:
    Model();
    void update();
    Case& getCase(sf::Vector2i pos);
    const std::vector<std::vector<Case>>& getEchiquier() const;
};

#endif
