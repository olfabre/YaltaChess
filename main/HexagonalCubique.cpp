#include "HexagonalCubique.h"
#include "Model.h"

namespace Hex {

    vector<Cube> movesCavalier(const Cube pos,const Model& model,Couleur couleur) {
        vector<Cube> res{ {0, 0, 0} };
        return res;
    }

    vector<Cube> movesTour(const Cube pos,const Model& model,Couleur couleur)
    {

        vector<Cube> res{ {0, 0, 0} };
        return res;
    }

    vector<Cube> movesFou(const Cube pos,const Model& model,Couleur couleur)
    {
        vector<Cube> res{ {0, 0, 0} };
        return res;
    }


    vector<Cube> movesDame(const Cube pos,const Model& model,Couleur couleur)
    {
        vector<Cube> res{ {0, 0, 0} };
        return res;
    }




    vector<Cube> movesRoi(const Cube pos,const Model& model,Couleur couleur)
    {
        vector<Cube> res{ {0, 0, 0} };
        return res;
    }






    vector<Cube> movesPion(const Cube pos, const Model& model, Couleur couleur)
    {
        Case* currentCase = model.getCaseAtCube(pos);
        Side side = currentCase ? currentCase->getSide() : Side::White;

        Cube fwd, capL, capR;

        if (couleur == BLANC) {
            if (side == Side::White)      { fwd = DIR[4]; capL = DIR[5]; capR = DIR[3]; }
            else if (side == Side::Red)   { fwd = DIR[0]; capL = DIR[1]; capR = DIR[5]; }
            else if (side == Side::Black) { fwd = DIR[2]; capL = DIR[3]; capR = DIR[1]; }
        } else if (couleur == ROUGE) {
            if (side == Side::Red)        { fwd = DIR[0]; capL = DIR[1]; capR = DIR[5]; }
            else if (side == Side::Black) { fwd = DIR[2]; capL = DIR[3]; capR = DIR[1]; }
            else if (side == Side::White) { fwd = DIR[4]; capL = DIR[5]; capR = DIR[3]; }
        } else if (couleur == NOIR) {
            if (side == Side::Black)      { fwd = DIR[2]; capL = DIR[3]; capR = DIR[1]; }
            else if (side == Side::White) { fwd = DIR[4]; capL = DIR[5]; capR = DIR[3]; }
            else if (side == Side::Red)   { fwd = DIR[0]; capL = DIR[1]; capR = DIR[5]; }
        }

        vector<Cube> res;

        // Avance simple
        Cube one{ pos.x + fwd.x, pos.y + fwd.y, pos.z + fwd.z };
        if (Hex::interieurEchiquier(one) && !model.getPieceAtCube(one))
            res.push_back(one);

        // Prises
        for (Cube d : { capL, capR }) {
            Cube tgt{ pos.x + d.x, pos.y + d.y, pos.z + d.z };
            if (!Hex::interieurEchiquier(tgt)) continue;
            auto q = model.getPieceAtCube(tgt);
            if (q && q->getCouleur() != couleur) res.push_back(tgt);
        }
        return res;
    }





}