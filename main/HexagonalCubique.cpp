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
static const array<Cube,3> ADV = {
        /* BLANC */ Cube{-1,  0, +1},
        /* ROUGE */ Cube{+1, -1,  0},
        /* NOIR  */ Cube{ 0, +1, -1}
};

// Les deux cases diagonales adjacentes au vecteur d’avance
static const array<array<Cube,2>,3> CAP = {{
                                                   /* BLANC */ { Cube{-1, +1, 0}, Cube{ 0, -1, +1} },
                                                   /* ROUGE */ { Cube{+1,  0,-1}, Cube{ 0, -1, +1} },
                                                   /* NOIR  */ { Cube{-1, +1, 0}, Cube{+1,  0,-1} }
                                           }};

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

    vector<Cube> movesPion(const Cube pos,const Model& model,Couleur c)
    {
        vector<Cube> res;
        int idx = (c==BLANC)?0 : (c==ROUGE)?1 : 2;

        // a) avance simple
        Cube fwd = pos + ADV[idx];
        if (model.getCaseAtCube(fwd) && !model.getPieceAtCube(fwd))
            res.push_back(fwd);

        // b) captures
        for (Cube d : CAP[idx]) {
            Cube dst = pos + d;
            if (auto p = model.getPieceAtCube(dst); p && p->getCouleur()!=c)
                res.push_back(dst);
        }
        // (avance double, promo, en-passant : à ajouter)
        return res;
    }

}