#include "Model.h"
#include <cmath>

Model::Model() { initialiserEchiquier(); }

Model::~Model() { for (auto &c : cases) delete c; }

void Model::ajouterCase(const std::vector<sf::Vector2f>& points, bool estBlanc)
{
    cases.push_back(new Case(points, estBlanc));
}

void Model::initialiserEchiquier()
{
    cases.clear();

    const float WIDTH = 1000.f, HEIGHT = 1000.f;  // Échiquier 1000x1000
    const float OFFSET_X = 50.f, OFFSET_Y = 50.f; // Décalage pour centrer dans une fenêtre 1100x1100

    sf::Vector2f mid(WIDTH / 2.f + OFFSET_X, HEIGHT / 2.f + OFFSET_Y);
    float size = WIDTH / 2.f;
    float side = size / 2.f;
    float height = std::sqrt(size * size - side * side);

    sf::Vector2f v123[] = {
            {-size*0.5f, -height}, {size*0.5f,-height}, {size,0},
            {size*0.5f, height}, {-size*0.5f,height}, {-size,0}
    };

    sf::Vector2f vabc[] = {
            {static_cast<float>(-height*cos(M_PI/6)), static_cast<float>(-height*sin(M_PI/6))},
            {0.f, -height},
            {static_cast<float>(height*cos(M_PI/6)), static_cast<float>(-height*sin(M_PI/6))},
            {static_cast<float>(height*cos(M_PI/6)), static_cast<float>(height*sin(M_PI/6))},
            {0.f, height},
            {static_cast<float>(-height*cos(M_PI/6)), static_cast<float>(height*sin(M_PI/6))}
    };

    std::vector<std::pair<sf::Vector2i, sf::Vector2i>> intervals = {
            {{0,4},{0,4}},{{0,4},{4,8}},{{8,12},{4,8}},
            {{8,12},{8,12}},{{4,8},{8,12}},{{4,8},{0,4}}
    };

    for(int zone = 0; zone < 6; zone++)
    {
        auto [ix, iy] = intervals[zone];
        sf::Vector2f s1 = v123[zone]*0.5f;
        sf::Vector2f s2 = v123[(zone+2)%6]*0.5f;
        sf::Vector2f corner = mid + v123[(zone+4)%6];

        for(int x = ix.x; x < ix.y; x++)
            for(int y = iy.x; y < iy.y; y++)
            {
                float rx1 = (x%4)/4.f, ry1 = (y%4)/4.f;
                float rx2 = (x%4+1)/4.f, ry2 = (y%4+1)/4.f;

                sf::Vector2f U1 = vabc[(zone+1)%6]*ry1 - s1*ry1 + s2;
                sf::Vector2f U2 = vabc[(zone+1)%6]*ry2 - s1*ry2 + s2;

                sf::Vector2f p1 = corner + s1*ry1 + U1*rx1;
                sf::Vector2f p2 = corner + s1*ry1 + U1*rx2;
                sf::Vector2f p3 = corner + s1*ry2 + U2*rx2;
                sf::Vector2f p4 = corner + s1*ry2 + U2*rx1;

                bool estBlanc = (x + y + zone) % 2 == 0;
                ajouterCase({p1,p2,p3,p4}, estBlanc);
            }
    }
}
