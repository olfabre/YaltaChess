#include "HexagonalCubique.h"
#include "Model.h"
#include <iostream>

const std::array<Cube,3> ADV = {
        Cube{ 0,+1,-1},   // White  (side « bas »)
        Cube{-1, 0,+1},   // Red    (haut-gauche)
        Cube{+1,-1, 0}    // Black  (haut-droit)
};
const std::array<std::array<Cube,2>,3> CAP = {{
       /* White  */ { Cube{+1, 0,-1}, Cube{-1,+1, 0} },
       /* Red    */ { Cube{ 0,+1,-1}, Cube{-1, 0,+1} },
        /* Black  */ { Cube{+1,-1, 0}, Cube{ 0,-1,+1} }
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
        return movesTour(pos, model, couleur);
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

    vector<Cube> Hex::movesPion(const Cube pos, const Model& model, Couleur c)
    {
        vector<Cube> res;
        int idx = (c==BLANC)?0 : (c==ROUGE)?1 : 2;

        // avance simple
        Cube fwd = pos + ADV[idx];
        if (auto ca = model.getCaseAtCube(fwd); ca && !model.getPieceAtCube(fwd))
            res.push_back(fwd);

        // captures
        for (Cube d : CAP[idx]) {
            Cube dst = pos + d;
            if (auto p = model.getPieceAtCube(dst); p && p->getCouleur()!=c)
                res.push_back(dst);
        }

        // TODO : double-pas initial, promotion, en-passant

        return res;
    }

}