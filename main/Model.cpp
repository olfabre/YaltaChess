#include "Model.h"
#include "cases/Case.h"
#include "Pion.h"     // tes classes
#include "Tour.h"
#include "Fou.h"
#include "Cavalier.h"
#include "Dame.h"
#include "Roi.h"
#include <cmath>
#include <random>
#include <algorithm>
using namespace sf;
using namespace std;



// ma table de départ (inspirée ddes infos que j'ai récupérée sur internet
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
    initialiserJoueurs();

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


void Model::initialiserJoueurs()
{
    // 1) Les trois couleurs possibles et un engine RNG
    vector<Couleur> cols = { BLANC, ROUGE, NOIR };
    static mt19937_64 rng{ random_device{}() };
    shuffle(cols.begin(), cols.end(), rng);

    // 2) Liste de prénoms pour IA (ajoutez les vôtres)
    vector<string> botNames = {
            "Alice", "Bob", "Charlie", "Diane", "Eve", "Frank", "Mickael"
    };
    shuffle(botNames.begin(), botNames.end(), rng);

    // 3) Construction du vecteur players
    players.clear();
    players.push_back({ "Humain", cols[0], true });      // toujours premier (le joueur)
    players.push_back({ botNames[0], cols[1], false });  // IA1
    players.push_back({ botNames[1], cols[2], false });  // IA2

    // 4) Tour de jeu initial: vous commencez toujours
    currentPlayerIdx = 0;
}



Model::~Model() {
    for (auto &c : cases) delete c;
    for(auto p: pieces) delete p;

}

void Model::ajouterCase(const vector<Vector2f>& points,
                        bool estBlanc,
                        Vector2i gridPos,
                        Side side
                        )
{
    /* cases.push_back(new Case(points, estBlanc, gridPos)); */
    Case* c = new Case(points, estBlanc, gridPos);
    c->setSide(side);       // on renseigne ici le Side de la case
    cases.push_back(c);
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

                /*
                //ajouterCase({p1,p2,p3,p4}, estBlanc);
                ajouterCase({p1,p2,p3,p4}, estBlanc, {x,y});
                 */
                // on détermine à quel joueur appartient ce bloc de 4×8 cases
                Side s;
                if (zone==4 || zone==5)      s = Side::White;  // bas du plateau
                else if (zone==0 || zone==1) s = Side::Red;    // en haut-gauche
                else s = Side::Black;  // en haut-droite
                ajouterCase({p1,p2,p3,p4}, estBlanc, {x,y}, s);

            }
    }

// ——————————————————————————————————————————
// 3) Lier les voisins intra-half-board (N/E/S/W)
// ——————————————————————————————————————————
    auto findCase = [&](sf::Vector2i p) -> Case* {
        for (Case* c : cases) {
            if (c->getGridPos() == p)
                return c;
        }
        return nullptr;
    };

    for (Case* c : cases) {
        sf::Vector2i g = c->getGridPos();
        // on ne lie que si le voisin existe ET appartient au même side
        Case* n = findCase({ g.x,     g.y - 1 });
        if (n && n->getSide() == c->getSide()) c->setNorth(n);
        Case* e = findCase({ g.x + 1, g.y     });
        if (e && e->getSide() == c->getSide()) c->setEast(e);
        Case* s = findCase({ g.x,     g.y + 1 });
        if (s && s->getSide() == c->getSide()) c->setSouth(s);
        Case* w = findCase({ g.x - 1, g.y     });
        if (w && w->getSide() == c->getSide()) c->setWest(w);
    }



}

Piece* Model::getPieceAt(Vector2i pos) const {
        for (Piece* p : pieces) {
                if (p->getPosition() == pos)
                        return p;
            }
        return nullptr;
    }

bool Model::isOccupied(Vector2i pos) const {
        return getPieceAt(pos) != nullptr;
    }

void Model::removePiece(Piece* p) {
    pieces.erase(
            std::remove(pieces.begin(), pieces.end(), p),
            pieces.end()
    );
    delete p;
}

void Model::movePiece(Piece* p, Vector2i dest) {
    // capture
    if (Piece* enemi = getPieceAt(dest))
        removePiece(enemi);
    // met à jour la position de p
    p->setPosition(dest);
    // change de joueur
    currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
}