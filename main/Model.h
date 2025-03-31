#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "cases/Case.h"

class Model
{
private:
    std::vector<Case *> cases;
    static constexpr float WIDTH = 800.f;
    static constexpr float HEIGHT = 800.f;

    void ajouterCase(const std::vector<sf::Vector2f>& points, bool estBlanc); // Correction ici

public:
    Model();
    ~Model();
    void initialiserEchiquier();
    const std::vector<Case *> &getCases() const { return cases; }
};

#endif
