#include "Model.h"
#include "cases/Case.h"
#include "pieces/Pion.h"     // tes classes
#include "pieces/Tour.h"
#include "pieces/Fou.h"
#include "pieces/Cavalier.h"
#include "pieces/Dame.h"
#include "pieces/Roi.h"
#include <iostream>
#include "HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include <cmath>
#include <random>
#include <algorithm>
#include <iomanip>
#include <map>
#include <tuple>


using namespace sf;
using namespace std;

// Génère un SETUP où chaque case affiche la couleur correspondant à son secteur
void genereSetupValide(const Model& model) {
    std::cout << "static const pair<int,int> SETUP[12][12] = {\n";
    for (int y = 0; y < 12; ++y) {
        std::cout << "    { ";
        for (int x = 0; x < 12; ++x) {
            Cube c = Hex::grilleVersCube({x, y});
            Case* ca = model.getCaseAtCube(c);
            int couleur = -1;
            int type = -1;
            if (ca) {
                int side = ca->getSide();
                if (side == 0) couleur = 0; // Blanc
                else if (side == 1) couleur = 1; // Rouge
                else if (side == 2) couleur = 2; // Noir
                // Option : type = 1 pour pion, ou -1 pour vide
            }
            std::cout << "{" << std::setw(2) << couleur << "," << std::setw(2) << type << "}";
            if (x != 11) std::cout << ", ";
        }
        std::cout << " },\n";
    }
    std::cout << "};\n";
}



// 0 = Blanc, 1 = Rouge, 2 = Noir, -1 = Vides
// 0 = Roi, 1 = Pion, 2 = Cavalier, 3 = Fou, 4 = Tour, 5 = Dame, -1 = vide
static const std::pair<int,int> SETUP[12][12] = {
        { { 1, 4}, { 1, 1}, { 1,-1}, { 1,-1}, { 0, 4}, { 0, 2}, { 0, 3}, { 0, 5}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} },
        { { 1, 2}, { 1, 1}, { 1,-1}, { 1,-1}, { 0, 1}, { 0, 1}, { 0, 1}, { 0, 1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} },
        { { 1, 3}, { 1, 1}, { 1,-1}, { 1,-1}, { 0,-1}, { 0, -1}, { 0, -1}, { 0, -1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} },
        { { 1, 0}, { 1, 1}, { 1,-1}, { 1,-1}, { 0,-1}, { 0, -1}, { 0, -1}, { 0, -1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} },
        { { 1, 4}, { 1, 2}, { 1, 3}, { 1, 5}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, { 2, 4}, { 2, 1}, { 2,-1}, { 2,-1} },
        { { 1, 1}, { 1, 1}, { 1, 1}, { 1, 1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, { 2, 2}, { 2, 1}, { 2,-1}, { 2,-1} },
        { { 1,-1}, { 1,-1}, { 1,-1}, { 1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, { 2, 3}, { 2, 1}, { 2,-1}, { 2,-1} },
        { { 1,-1}, { 1,-1}, { 1,-1}, { 1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, { 2, 0}, { 2, 1}, { 2,-1}, { 2,-1} },
        { {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, { 0, 4}, { 0, 1}, { 0, -1}, { 0,-1}, { 2, 4}, { 2, 2}, { 2, 3}, { 2, 5} },
        { {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, { 0, 2}, { 0, 1}, { 0, -1}, { 0,-1}, { 2, 1}, { 2, 1}, { 2, 1}, { 2, 1} },
        { {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, { 0, 3}, { 0, 1}, { 0, -1}, { 0,-1}, { 2,-1}, { 2,-1}, { 2,-1}, { 2,-1} },
        { {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, { 0, 0}, { 0, 1}, { 0, -1}, { 0,-1}, { 2,-1}, { 2,-1}, { 2,-1}, { 2,-1} },
};







Model::Model() {
    initialiserEchiquier();
    initialiserPieces();
    initialiserJoueurs();
}




void Model::initialiserPieces() {

    int compteur = 0;

    for (int y = 0; y < 12; ++y) { // ligne
        for (int x = 0; x < 12; ++x) { // colonne

            // desturcturation
            auto [coul, type] = SETUP[y][x];

            //si pas couleur, on passe à la suivante
            if (coul < 0 || type < 0) continue;

            ++compteur;
            // 1) Calcule la position cube et récupère la Case
            Cube c = Hex::grilleVersCube({x,y});
            //cout << "N°" << compteur << "ligne/colonne " << x << "/" << y << " ->(" << c.x << ", " << c.y << ", " <<  c.z << ")" << endl;
            Case* ca = getCaseAtCube(c);


            if (!ca) {
                std::cout << "ERREUR: Pas de case trouvée pour la position (" << x << "," << y << ")" << std::endl;
                std::cout << "Position cube calculée: " << c.x << "," << c.y << "," << c.z << std::endl;
                continue;
            }

            // 2) On utilise la couleur lue dans SETUP (pas besoin de side)

            Couleur cc;
            switch (coul) {
                case 0: cc = BLANC; break;
                case 1: cc = ROUGE; break;
                case 2: cc = NOIR;  break;
                default: cc = BLANC;
            }



            Piece* p = nullptr;
            // on crée la piece qui reçoit ses coordonnées et sa couleur
            switch(type) {
                case 0: p = new Roi(c, cc);       break;
                case 1: p = new Pion(c, cc, this);      break;
                case 2: p = new Cavalier(c, cc);  break;
                case 3: p = new Fou(c, cc);       break;
                case 4: p = new Tour(c, cc);      break;
                case 5: p = new Dame(c, cc);      break;
            }

            if (!p) continue;

            // debug
            string couleur;
            switch(coul){
                case 0: couleur = "BLANC"; break;
                case 1: couleur = "ROUGE"; break;
                case 2: couleur = "NOIR";  break;
                default: couleur = "BLANC";
            }
            cout << "N° " << compteur << ", " << couleur << " " << p->getTypeName() << " " << cc << ", ligne/colonne " << x << "/" << y << " ->(" << c.x << ", " << c.y << ", " <<  c.z << ")" << endl;
            // fin debug




            // 4) Diagnostic : Y a-t-il déjà une pièce à cette case ?
            if (ca->getPiece() != nullptr) {
                std::cout << "!!! DOUBLON PIECE SUR LA MEME CASE : cube("
                          << c.x << "," << c.y << "," << c.z << ")"
                          << " Ancien: " << ca->getPiece()->getTypeName()
                          << " / Nouveau: " << p->getTypeName() << std::endl;
            }

            pieces.push_back(p);
            ca->setPiece(p);
            if (p) {
                p->setPositionCube(ca->getCubePos());
            }


        }
    }

// === Vérification complète de doublons de cubes dans le vecteur pieces ===
    std::map<std::tuple<int, int, int>, Piece*> piecesParCube;
    for (Piece* p : pieces) {
        auto c = p->getPositionCube();
        auto t = std::make_tuple(c.x, c.y, c.z);

        if (piecesParCube.count(t)) {
            std::cout << "!!! DOUBLON TROUVE DANS VECTEUR PIECES : "
                      << "cube(" << c.x << "," << c.y << "," << c.z << ") : "
                      << p->getTypeName() << " et "
                      << piecesParCube[t]->getTypeName() << std::endl;
        } else {
            piecesParCube[t] = p;
        }
    }


   //realignerPieces();



    // === DÉBUG : afficher grid → cube pour chaque pièce ===
    /*
    std::cout << "=== Debug positions et sides ===\n";
    for (Piece* p : pieces) {
        auto c = p->getPositionCube();
        Case* ca = getCaseAtCube(c);
        std::cout
                << p->getTypeName()
                << " couleur=" << p->getCouleur()
                << "  cube(" << c.x << "," << c.y << "," << c.z << ")"
                << "  SIDE=" << (ca ? ca->getSide() : -1)
                << std::endl;
    }
    std::cout << "========================\n";
*/


//initialiserEchiquier();
    initialiserJoueurs();


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

void Model::ajouterCase(const vector<Vector2f>& points, bool estBlanc, const Cube& cubePos, Side side) {
    Case* c = new Case(points, estBlanc, cubePos);
    c->setSide(side);
    cases.push_back(c);
    caseMap[cubePos] = c;
}

void Model::initialiserEchiquier()
{
    cases.clear();
    caseMap.clear();

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
                //ajouterCase({p1,p2,p3,p4}, estBlanc, {x,y}, s);
                Cube c = Hex::grilleVersCube({x,y});
                ajouterCase({p1,p2,p3,p4}, estBlanc, c, s);

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
        Vector2i g = c->getGridPos();
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

    // ——————————————————————————————————————————
// 4) Lier les frontières entre half-boards (cross-group)
// ——————————————————————————————————————————
// 1) Regrouper les cases par Side
    array<vector<Case*>,3> bySide;
    for (Case* c : cases)
        bySide[c->getSide()].push_back(c);

// 2) Pour chaque paire de côtés adjacents (White→Red, Red→Black, Black→White)
    for (int s = 0; s < 3; ++s) {
        auto& cur = bySide[s];
        auto& nxt = bySide[(s + 1) % 3];

        // 2.a) Trier chaque vecteur pour isoler les 8 cases de l’arête :
        //     - On ordonne d’abord par "distance au joueur" (row % 4), puis par "half-col" (col % 4).
        auto comp = [](Case* a, Case* b){
            auto ga = a->getGridPos(), gb = b->getGridPos();
            int rowA = ga.y % 4, rowB = gb.y % 4;
            if (rowA != rowB) return rowA < rowB;
            int colA = ga.x % 4, colB = gb.x % 4;
            return colA < colB;
        };
        sort(cur.begin(), cur.end(), comp);
        sort(nxt.begin(), nxt.end(), comp);

        // 2.b) Les 8 dernières de cur (farthest row) vers 8 premières de nxt (nearest row)
        for (int i = 0; i < 8; ++i) {
            Case* a = cur[cur.size() - 8 + i];
            Case* b = nxt[i];
            // on traverse "en avant" : North de a → b, et South de b → a
            a->setNorth(b);
            b->setSouth(a);
        }
    }




}




// Recherche la pièce dont la positionCube == c
Piece* Model::getPieceAtCube(const Cube& c) const {
        for (auto p : pieces) {
                if (p->getPositionCube() == c)
                        return p;
            }
        return nullptr;
    }


// Déplace p vers dest (Cube), gère la capture et change de joueur
void Model::movePieceCube(Piece* p, const Cube& dest) {
        if (auto en = getPieceAtCube(dest))
                removePiece(en);
        p->setPositionCube(dest);
        currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
    }

bool Model::isOccupied(Vector2i pos) const {
        Cube c = Hex::grilleVersCube(pos);return getPieceAtCube(c) != nullptr;
    }

void Model::removePiece(Piece* p) {
    pieces.erase(
            std::remove(pieces.begin(), pieces.end(), p),
            pieces.end()
    );
    delete p;
}



Case* Model::getCaseAtCube(const Cube& c) const {
    auto it = caseMap.find(c);
    return it==caseMap.end() ? nullptr : it->second;
}








// ------------------------------------------------------------------
//  Corrige la coordonnée logique d'une pièce en se basant
//  sur la case qui contient réellement son centre pixel.
// ------------------------------------------------------------------
void Model::realignerPieces()
{
    // helper interne pour (x,y) → position-pixel
    auto gridToPixel = [](Vector2i g)->Vector2f
    {
        const float W = 1000.f, O = 50.f;
        Vector2f mid(W/2.f+O, W/2.f+O);
        float size=W/2.f, side=size/2.f;
        float h = std::sqrt(size*size - side*side);
        std::array<Vector2f,6> v = {{
                                            {-size*0.5f,-h},{ size*0.5f,-h},{ size,0},
                                            { size*0.5f, h},{-size*0.5f, h},{-size,0}
                                    }};
        std::array<std::pair<Vector2i,Vector2i>,6> inter = {{
            {{0,4},{0,4}},{{0,4},{4,8}},{{8,12},{4,8}},
            {{8,12},{8,12}},{{4,8},{8,12}},{{4,8},{0,4}}
             }};

        for(int z=0;z<6;++z){
            auto [ix,iy]=inter[z];
            if (g.x >= ix.x && g.x < ix.y && g.y >= iy.x && g.y < iy.y) {
            //if(g.x>=ix.first&&g.x<ix.second&&g.y>=iy.first&&g.y<iy.second){
                float rx=(g.x%4+0.5f)/4.f, ry=(g.y%4+0.5f)/4.f;
                Vector2f s1=v[z]*0.5f, s2=v[(z+2)%6]*0.5f;
                Vector2f corner=mid+v[(z+4)%6];
                Vector2f vabc[6]={
                        {-h*0.866f,-h*0.5f},{0,-h},{ h*0.866f,-h*0.5f},
                        { h*0.866f, h*0.5f},{0, h},{-h*0.866f, h*0.5f}};
                Vector2f U=vabc[(z+1)%6]*ry - s1*ry + s2;
                return corner + s1*ry + U*rx;
            }
        }
        return mid;                 // fallback
    };

    for (Piece* p : pieces)
    {
        if (!p) continue; //
        if (p == nullptr) {
            std::cout << "Piece nullptr detectee !" << std::endl;
            continue;
        }
        Vector2f centre = gridToPixel(p->getPosition());
        for (Case* c : cases)
        {
            if (c && c->contientPoint(centre))
            {
                p->setPositionCube(c->getCubePos());
                break;
            }
        }
    }

}





// Dans Model.cpp
void Model::deplacerPiece(Piece* piece, const Cube& destination) {
    if (!piece) return;

    // 1. Enlever la pièce de son ancienne case
    Cube oldPos = piece->getPositionCube();
    Case* oldCase = getCaseAtCube(oldPos);
    if (oldCase && oldCase->getPiece() == piece) {
        oldCase->setPiece(nullptr);
    }

    // 2. Si une pièce adverse est présente sur la case destination, la retirer
    Case* newCase = getCaseAtCube(destination);
    if (!newCase) return;
    if (newCase->estOccupee()) {
        Piece* adversaire = newCase->getPiece();
        // À adapter selon ta logique de capture !
        // removePiece(adversaire); // Si tu as une telle fonction
        newCase->setPiece(nullptr);
    }

    // 3. Déplacer la pièce (mettre à jour sa position)
    piece->setPositionCube(destination);

    // 4. Mettre à jour la case de destination
    newCase->setPiece(piece);
}
