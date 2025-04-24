#include "Model.h"
#include "cases/Case.h"
#include "Pion.h"     // tes classes
#include "Tour.h"
#include "Fou.h"
#include "Cavalier.h"
#include "Dame.h"
#include "Roi.h"
#include <cmath>
using namespace sf;
using namespace std;

// Ta table de départ (inspirée du Python)
// en haut de Model.cpp, juste après les includes :
static const pair<int,int> SETUP[12][12] = {
        //  y=0
        { {0,4},{0,2},{0,3},{0,5},{0,4},{0,1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1} },
        //  y=1
        { {0,1},{0,1},{0,1},{0,1},{0,2},{0,1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1} },
        //  y=2
        { {-1,-1},{-1,-1},{-1,-1},{-1,-1},{0,3},{0,1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1} },
        //  y=3
        { {-1,-1},{-1,-1},{-1,-1},{-1,-1},{0,0},{0,1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1} },
        //  y=4
        { {1,4},{1,1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{1,4},{1,2},{1,3},{1,5} },
        //  y=5
        { {1,2},{1,1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{1,1},{1,1},{1,1},{1,1} },
        //  y=6
        { {1,3},{1,1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1} },
        //  y=7
        { {1,0},{1,1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1} },
        //  y=8
        { {-1,-1},{-1,-1},{-1,-1},{-1,-1},{2,4},{2,2},{2,3},{2,5},{2,4},{2,1},{-1,-1},{-1,-1} },
        //  y=9
        { {-1,-1},{-1,-1},{-1,-1},{-1,-1},{2,1},{2,1},{2,1},{2,1},{2,2},{2,1},{-1,-1},{-1,-1} },
        // y=10
        { {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{2,3},{2,1},{-1,-1},{-1,-1} },
        // y=11
        { {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{2,0},{2,1},{-1,-1},{-1,-1} }
};

Model::Model() {
    initialiserEchiquier();
    for (int y = 0; y < 12; ++y) {
        for (int x = 0; x < 12; ++x) {
            auto [coul, type] = SETUP[y][x];
            if (coul < 0) continue;
            Vector2i grid{x,y};
            Piece* p = nullptr;
            Couleur cc = (coul==0? BLANC : coul==1? ROUGE : NOIR);
            switch(type) {
                case 0: p = new Roi(grid, cc);       break;
                case 1: p = new Pion(grid, cc);      break;
                case 2: p = new Cavalier(grid, cc);  break;
                case 3: p = new Fou(grid, cc);       break;
                case 4: p = new Tour(grid, cc);      break;
                case 5: p = new Dame(grid, cc);      break;
            }
            pieces.push_back(p);
        }
    }
}

Model::~Model() {
    for (auto &c : cases) delete c;
    for(auto p: pieces) delete p;

}

void Model::ajouterCase(const vector<Vector2f>& points, bool estBlanc)
{
    cases.push_back(new Case(points, estBlanc));
}

void Model::initialiserEchiquier()
{
    cases.clear();

    const float WIDTH = 1000.f, HEIGHT = 1000.f;  // Échiquier 1000x1000
    const float OFFSET_X = 50.f, OFFSET_Y = 50.f; // Décalage pour centrer dans une fenêtre 1100x1100

    Vector2f mid(WIDTH / 2.f + OFFSET_X, HEIGHT / 2.f + OFFSET_Y);
    float size = WIDTH / 2.f;
    float side = size / 2.f;
    float height = sqrt(size * size - side * side);

    Vector2f v123[] = {
            {-size*0.5f, -height}, {size*0.5f,-height}, {size,0},
            {size*0.5f, height}, {-size*0.5f,height}, {-size,0}
    };

    Vector2f vabc[] = {
            {static_cast<float>(-height*cos(M_PI/6)), static_cast<float>(-height*sin(M_PI/6))},
            {0.f, -height},
            {static_cast<float>(height*cos(M_PI/6)), static_cast<float>(-height*sin(M_PI/6))},
            {static_cast<float>(height*cos(M_PI/6)), static_cast<float>(height*sin(M_PI/6))},
            {0.f, height},
            {static_cast<float>(-height*cos(M_PI/6)), static_cast<float>(height*sin(M_PI/6))}
    };

    vector<pair<Vector2i, Vector2i>> intervals = {
            {{0,4},{0,4}},{{0,4},{4,8}},{{8,12},{4,8}},
            {{8,12},{8,12}},{{4,8},{8,12}},{{4,8},{0,4}}
    };

    for(int zone = 0; zone < 6; zone++)
    {
        auto [ix, iy] = intervals[zone];
        Vector2f s1 = v123[zone]*0.5f;
        Vector2f s2 = v123[(zone+2)%6]*0.5f;
        Vector2f corner = mid + v123[(zone+4)%6];

        for(int x = ix.x; x < ix.y; x++)
            for(int y = iy.x; y < iy.y; y++)
            {
                float rx1 = (x%4)/4.f, ry1 = (y%4)/4.f;
                float rx2 = (x%4+1)/4.f, ry2 = (y%4+1)/4.f;

                Vector2f U1 = vabc[(zone+1)%6]*ry1 - s1*ry1 + s2;
                Vector2f U2 = vabc[(zone+1)%6]*ry2 - s1*ry2 + s2;

                Vector2f p1 = corner + s1*ry1 + U1*rx1;
                Vector2f p2 = corner + s1*ry1 + U1*rx2;
                Vector2f p3 = corner + s1*ry2 + U2*rx2;
                Vector2f p4 = corner + s1*ry2 + U2*rx1;

                bool estBlanc = (x + y + zone) % 2 == 0;
                ajouterCase({p1,p2,p3,p4}, estBlanc);
            }
    }
}
