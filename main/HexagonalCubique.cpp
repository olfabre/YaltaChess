#include "HexagonalCubique.h"
#include "Model.h"
#include <array>
#include <vector>
#include <iostream>
#include "CubeToLabel.h"

using std::array;
using std::vector;


// ───────────────── utilitaires bas niveau ───────────────────────────
inline Cube operator+(Cube a, Cube b){ return {a.x+b.x, a.y+b.y, a.z+b.z}; }

static const Cube DIR[6] = {                    // les 6 directions cube
        {+1,-1,0},{+1,0,-1},{0,+1,-1},
        {-1,+1,0},{-1,0,+1},{0,-1,+1}
};
static int dirIndex(Cube v){                    // 0‥5 → pour les diagonales
    for(int i=0;i<6;++i) if(DIR[i].x==v.x && DIR[i].y==v.y && DIR[i].z==v.z) return i;
    return -1;
}

// ───────────────── centre “réel” du plateau ─────────────────────────
static double CX=0,CY=0,CZ=0;   // centre géométrique (double)
static bool centreInit=false;

static void initCentre(const Model& model)
{
    if (centreInit) return;
    long long sx=0, sy=0, sz=0; size_t n=0;
    for (const Case* c : model.getCases()){      // Model::getCases() existe déjà
        Cube q = c->getCubePos();
        sx+=q.x; sy+=q.y; sz+=q.z; ++n;
    }
    CX = double(sx)/n; CY = double(sy)/n; CZ = double(sz)/n;
    centreInit = true;
}
inline double dist2Centre(Cube c){
    double dx=c.x-CX, dy=c.y-CY, dz=c.z-CZ;
    return dx*dx + dy*dy + dz*dz;                // distance euclidienne²
}


namespace Hex {

    vector<Cube> movesCavalier(const Cube pos, const Model& model, Couleur couleur) {
        vector<Cube> res;
        // Vérifier toutes les cases du plateau
        for (int x = -8; x <= 8; x++) {
            for (int y = -8; y <= 8; y++) {
                for (int z = -8; z <= 8; z++) {
                    Cube dest = {x, y, z};
                    // Vérifier si la case existe
                    if (auto c = model.getCaseAtCube(dest)) {
                        // Vérifier si la case est vide ou contient une pièce adverse
                        if (!model.getPieceAtCube(dest) || 
                            (model.getPieceAtCube(dest) && model.getPieceAtCube(dest)->getCouleur() != couleur)) {
                            res.push_back(dest);
                        }
                    }
                }
            }
        }
        return res;
    }

    vector<Cube> movesTour(const Cube pos, const Model& model, Couleur couleur) {
        return {};    // la tour ne peut pas bouger → plus de plantage
    }

    vector<Cube> movesFou(const Cube pos, const Model& model, Couleur couleur) {
        return movesFou(pos, model, couleur);
    }

    vector<Cube> movesDame(const Cube pos, const Model& model, Couleur couleur) {
        return movesDame(pos, model, couleur);
    }

    vector<Cube> movesRoi(const Cube pos, const Model& model, Couleur couleur) {
        return movesRoi(pos, model, couleur);
    }

    vector<Cube> movesPion(const Cube pos, const Model& model, Couleur)
    {
        Case* cur = model.getCaseAtCube(pos);
        if(!cur) return {};

        initCentre(model);

        // 1) trouver l’unique direction qui augmente le plus la distance au centre
        Cube bestDir{0,0,0};                // initial : invalide
        double bestDist = -1.0;
        for (Cube d : DIR){
            Cube nxt = pos + d;
            if (!model.getCaseAtCube(nxt)) continue; // hors plateau
            double d2 = dist2Centre(nxt);
            if (d2 > bestDist){ bestDist = d2; bestDir = d; }
        }
        if (bestDist < 0) return {};        // impossible (devrait jamais arriver)

        // 2) diagonales de prise = directions voisines
        int k = dirIndex(bestDir);
        Cube cap1 = DIR[(k+5)%6], cap2 = DIR[(k+1)%6];

        vector<Cube> res;

        // a) avance simple (si la case est vide)
        Cube step = pos + bestDir;
        if (model.getCaseAtCube(step) && !model.getPieceAtCube(step))
            res.push_back(step);

        // b) captures
        for (Cube d : {cap1,cap2}){
            Cube dst = pos + d;
            if (auto p = model.getPieceAtCube(dst); p && p->getCouleur()!=cur->getPiece()->getCouleur())
                res.push_back(dst);
        }

        // DEBUG ► supprime ou commente ces 2 lignes si tu ne veux plus de traces
        std::cout << "[Pawn " << cubeToLabel(pos) << "] moves = ";
        for(Cube c : res) std::cout << cubeToLabel(c) << ' '; std::cout << '\n';

        return res;   // (double-pas, promotion … viendront plus tard)
    }


}