#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "cases/Case.h"
using namespace sf;
using namespace std;

class Model
{
private:
    vector<Case *> cases;
    static constexpr float WIDTH = 800.f;
    static constexpr float HEIGHT = 800.f;

    void ajouterCase(const vector<Vector2f>& points, bool estBlanc); // Correction ici

public:
    Model();
    ~Model();
    void initialiserEchiquier();
    const vector<Case *> &getCases() const { return cases; }
};

#endif
