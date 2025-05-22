#include "HexagonalCubique.h"
#include "Model.h"
#include <array>
#include <vector>
using std::array;
using std::vector;

// ───────────────── utilitaire ────────────────────────────
inline Cube operator+(Cube a, Cube b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }




// ──────────── directions correctes (testées) ─────────────
// 0 = BLANC (bas)  1 = ROUGE (haut-gauche)  2 = NOIR (haut-droit)
static const Cube D[6] = {
        {+1,-1,0},{+1,0,-1},{0,+1,-1},
        {-1,+1,0},{-1,0,+1},{0,-1,+1}
};

// Les deux cases diagonales adjacentes au vecteur d’avance
static int dirIndex(Cube v){
    for(int i=0;i<6;++i) if(D[i].x==v.x&&D[i].y==v.y&&D[i].z==v.z) return i;
    return -1;
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

    vector<Cube> movesPion(const Cube pos,const Model& model,Couleur)
    {
        Case* cur = model.getCaseAtCube(pos);      // position actuelle
        if(!cur) return {};
        const int side = cur->getSide();           // 0 = bas, 1 = gauche, 2 = droite

        // 2.1  vecteurs “avant” pour chaque side  (deux branches)
        Cube dA, dB;
        switch(side){
            case 0: dA={-1,0,+1}; dB={+1,-1,0};  break;   // bas
            case 1: dA={+1,-1,0}; dB={ 0,+1,-1}; break;   // gauche
            case 2: dA={ 0,+1,-1}; dB={-1,0,+1}; break;   // droite
            default: return {};
        }

        // 2.2  choisir la branche selon la coordonnée clef
        Cube fwd;
        if      (side==0) fwd = (pos.z >  6 ? dB : dA);
        else if (side==1) fwd = (pos.x >  4 ? dA : dB);
        else              fwd = (pos.y < -6 ? dA : dB);

        // 2.3  diagonales = directions adjacentes dans D
        int k = dirIndex(fwd);                   // 0..5
        Cube cap1 = D[(k+5)%6], cap2 = D[(k+1)%6];

        vector<Cube> res;

        // a) avance simple
        Cube step = pos + fwd;
        if(model.getCaseAtCube(step) && !model.getPieceAtCube(step))
            res.push_back(step);

        // b) captures
        for(Cube d : {cap1,cap2}){
            Cube dst = pos + d;
            if(auto p = model.getPieceAtCube(dst); p && p->getCouleur()!=cur->getPiece()->getCouleur())
                res.push_back(dst);
        }
        return res;      // (double-pas, promotion : à coder plus tard)
    }

}