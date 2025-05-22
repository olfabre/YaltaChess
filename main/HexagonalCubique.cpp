#include "HexagonalCubique.h"
#include "Model.h"
#include <iostream>
#include <array>
#include <vector>
using std::array;
using std::vector;


//struct Cube { int x, y, z; };
inline Cube operator+(Cube a, Cube b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}



// 1)  Vecteurs du pion (Yalta 3J)
static const array<Cube,3> ADV = {
        /* Blanc */ Cube{ 0, +1, -1},
        /* Rouge */ Cube{-1,  0, +1},
        /* Noir  */ Cube{+1, -1,  0}
};
static const array<array<Cube,2>,3> CAP = {{
        /* Blanc */ { Cube{+1, 0,-1}, Cube{-1,+1, 0} },
        /* Rouge */ { Cube{ 0,+1,-1}, Cube{-1, 0,+1} },
      /* Noir  */ { Cube{+1,-1, 0}, Cube{ 0,-1,+1} }
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

    vector<Cube> movesPion(const Cube pos, const Model& model, Couleur c)
    {
        vector<Cube> res;
        int idx = (c == BLANC) ? 0 : (c == ROUGE) ? 1 : 2;

        // a) avance simple
        Cube fwd = pos + ADV[idx];
        if (model.getCaseAtCube(fwd) && !model.getPieceAtCube(fwd))
            res.push_back(fwd);

        // b) captures diagonales
        for (Cube d : CAP[idx]) {
            Cube dst = pos + d;
            if (auto p = model.getPieceAtCube(dst); p && p->getCouleur() != c)
                res.push_back(dst);
        }
        return res;         // (avance double, promo, en-passant : à venir)
    }

}