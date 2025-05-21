#include "HexagonalCubique.h"
#include "Model.h"
#include <iostream>

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
        return movesCavalier(pos, model, couleur);
    }

    vector<Cube> movesFou(const Cube pos, const Model& model, Couleur couleur) {
        return movesCavalier(pos, model, couleur);
    }

    vector<Cube> movesDame(const Cube pos, const Model& model, Couleur couleur) {
        return movesCavalier(pos, model, couleur);
    }

    vector<Cube> movesRoi(const Cube pos, const Model& model, Couleur couleur) {
        return movesCavalier(pos, model, couleur);
    }

    vector<Cube> movesPion(const Cube pos, const Model& model, Couleur couleur) {
        return movesCavalier(pos, model, couleur);
    }

}