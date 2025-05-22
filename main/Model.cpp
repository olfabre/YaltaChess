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
    realignerPieces();
    initialiserPieces();
    initialiserJoueurs();
    lastMove = Cube{0, 0, 0};  // Initialisation du dernier mouvement
}


/*
 *
 * Les coordonnées {x,y} → {cube.x,cube.y,cube.z} sont d'abord passées à la création de chaque Case.
 *
 * Lors de l'initialisation des pièces, on recherche simplement la Case correspondante avec ces mêmes
 * coordonnées, qu'on n'a pas besoin de redonner à la Case (elle les connaît déjà).
 *
 * On ne « donne » ces coords aux pièces qu'au moment où on crée la Piece et/ou où on
 * appelle p->setPositionCube(...).
 *
 *
 */

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
                case 0: p = new Roi(c, cc, this);       break;
                case 1: p = new Pion(c, cc, this);      break;
                case 2: p = new Cavalier(c, cc, this);  break;
                case 3: p = new Fou(c, cc, this);       break;
                case 4: p = new Tour(c, cc, this);      break;
                case 5: p = new Dame(c, cc, this);      break;
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
            //cout << "N° " << compteur << ", " << couleur << " " << p->getTypeName() << " " << cc << ", ligne/colonne " << x << "/" << y << " ->(" << c.x << ", " << c.y << ", " <<  c.z << ")" << endl;
            // fin debug



            // je place le pointeur de la piece dans la liste du jeu
            pieces.push_back(p);

            // on associe la piece avec la case
            ca->setPiece(p);
            p->setPositionCube(ca->getCubePos());



            // debug
            cout << "Coord. Piece:" << p->getTypeName() << "(" << p->getPositionCube().x << "," << p->getPositionCube().y << "," << p->getPositionCube().z << ")" << endl;
            cout << "Coord. Case:" << ca->getPiece()->getTypeName() <<  "(" << ca->getCubePos().x << "," << ca->getCubePos().y << "," << ca->getCubePos().z << ")" << endl << endl;



        } // colonne
    } // ligne




   //realignerPieces();




//initialiserEchiquier();
    //initialiserJoueurs();


}




void Model::initialiserJoueurs()
{
    // Les trois couleurs possibles et un engine RNG
    vector<Couleur> cols = { BLANC, ROUGE, NOIR };
    static mt19937_64 rng{ random_device{}() };
    shuffle(cols.begin(), cols.end(), rng);

    // Liste de prénoms pour IA (ajoutez les vôtres)
    vector<string> botNames = {
            "Alice", "Bob", "Charlie", "Diane", "Eve", "Frank", "Mickael"
    };
    shuffle(botNames.begin(), botNames.end(), rng);

    // Construction du vecteur players
    players.clear();
    players.push_back({ "Humain", cols[0], true });      // toujours premier (le joueur)
    players.push_back({ botNames[0], cols[1], false });  // IA1
    players.push_back({ botNames[1], cols[2], false });  // IA2

    // Tour de jeu initial: on commence toujours
    currentPlayerIdx = 0;
}


// a la creation on initalise tout
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
// Lier les frontières entre half-boards (cross-group)
// ——————————————————————————————————————————
// Regrouper les cases par Side
    array<vector<Case*>,3> bySide;
    for (Case* c : cases)
        bySide[c->getSide()].push_back(c);

// Pour chaque paire de côtés adjacents (White→Red, Red→Black, Black→White)
    for (int s = 0; s < 3; ++s) {
        auto& cur = bySide[s];
        auto& nxt = bySide[(s + 1) % 3];

        // Trier chaque vecteur pour isoler les 8 cases de l'arête :
        // On ordonne d'abord par "distance au joueur" (row % 4), puis par "half-col" (col % 4).
        auto comp = [](Case* a, Case* b){
            auto ga = a->getGridPos(), gb = b->getGridPos();
            int rowA = ga.y % 4, rowB = gb.y % 4;
            if (rowA != rowB) return rowA < rowB;
            int colA = ga.x % 4, colB = gb.x % 4;
            return colA < colB;
        };
        sort(cur.begin(), cur.end(), comp);
        sort(nxt.begin(), nxt.end(), comp);

        // Les 8 dernières de cur (farthest row) vers 8 premières de nxt (nearest row)
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
    //if (!p) return;
    if (!p || !p->mouvementValide(dest)) return;   // garde-fou
    
    // Calculer le mouvement effectué
    Cube move = {
        dest.x - p->getPositionCube().x,
        dest.y - p->getPositionCube().y,
        dest.z - p->getPositionCube().z
    };
    
    // Mettre à jour le dernier mouvement
    setLastMove(move);
    
    // Gérer la capture si nécessaire
    if (auto captured = getPieceAtCube(dest)) {
        removePiece(captured);
    }
    
    // Déplacer la pièce
    deplacerPiece(p, dest);
    
    // Passer au joueur suivant
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
    auto gridToPixel = [](const Cube& cube)->Vector2f
    {
        const float WIDTH = 1000.f, HEIGHT = 1000.f;  // Échiquier 1000x1000
        const float OFFSET_X = 50.f, OFFSET_Y = 50.f; // Décalage pour centrer dans une fenêtre 1100x1100
        Vector2f mid(WIDTH/2.f + OFFSET_X, HEIGHT/2.f + OFFSET_Y);
        float size = WIDTH/2.f;
        float side = size/2.f;
        float height = sqrt(size*size - side*side);

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

        // Convertir les coordonnées cube en coordonnées grille
        Vector2i g = Hex::cubeVersGrille(cube);

        for(int zone = 0; zone < 6; zone++) {
            auto [ix, iy] = intervals[zone];
            if (g.x >= ix.x && g.x < ix.y && g.y >= iy.x && g.y < iy.y) {
                float rx = (g.x%4 + 0.5f)/4.f;
                float ry = (g.y%4 + 0.5f)/4.f;
                Vector2f s1 = v123[zone]*0.5f;
                Vector2f s2 = v123[(zone+2)%6]*0.5f;
                Vector2f corner = mid + v123[(zone+4)%6];
                Vector2f U = vabc[(zone+1)%6]*ry - s1*ry + s2;
                return corner + s1*ry + U*rx;
            }
        }
        return mid; // fallback
    };

    for (Piece* p : pieces) {
        if (!p) continue;

        // 1. Calcul de la position pixel actuelle de la pièce
        Vector2f centre = gridToPixel(p->getPositionCube());

        // 2. Recherche de la case contenant ce point
        Case* caseTrouvee = nullptr;
        for (Case* c : cases) {
            if (c && c->contientPoint(centre)) {
                caseTrouvee = c;
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

void Model::movePiece(Piece* piece, const Cube& destination) {
    if (!piece) return;

    // On met à jour la position de la pièce
    piece->setPositionCube(destination);
}

void Model::nextPlayer() {
    // On passe au joueur suivant en boucle
    currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
}
