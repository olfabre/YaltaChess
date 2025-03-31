#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "cases/Case.h"

class Model
{
private:
    std::vector<Case *> cases;
    static constexpr float CENTRE_X = 400.f;
    static constexpr float CENTRE_Y = 400.f;
    static constexpr float TAILLE_CASE = 60.f;

public:
    Model();
    ~Model();
    void initialiserEchiquier();
    void ajouterCase(float x, float y, bool estBlanc);
    const std::vector<Case *> &getCases() const { return cases; }
};

#endif // MODEL_H