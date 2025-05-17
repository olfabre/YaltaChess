#include "HexagonalCubique.h"
#include "Model.h"
#include <iostream>

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
        // Récupérer la case actuelle pour déterminer son côté (White, Red, Black)
        Case* currentCase = model.getCaseAtCube(pos);
        Side side = currentCase ? currentCase->getSide() : Side::White;

        // AJOUT DEBUG :
        std::cout << "Pion couleur=" << couleur << " pos=(" << pos.x << "," << pos.y << "," << pos.z
                  << ") side=" << side << std::endl;

        // Définir les directions en fonction de la couleur du pion et du côté du plateau
        Cube fwd = {0,0,0};  // Avance
        Cube capL = {0,0,0}; // Capture gauche
        Cube capR = {0,0,0}; // Capture droite

        // Directions de base (hexagones adjacents) définies dans HexagonalCubique.h
        // DIR[0] = {1, -1, 0}   // Nord-Est
        // DIR[1] = {0, -1, 1}   // Nord-Ouest
        // DIR[2] = {-1, 0, 1}   // Ouest
        // DIR[3] = {-1, 1, 0}   // Sud-Ouest
        // DIR[4] = {0, 1, -1}   // Sud-Est
        // DIR[5] = {1, 0, -1}   // Est

        // Pour chaque combinaison couleur/côté, définir les directions appropriées
        if (couleur == BLANC) {
            if (side == Side::White) {
                // Sur le côté blanc, le pion blanc avance vers le haut
                fwd = DIR[1];  // Nord-Ouest
                capL = DIR[0]; // Nord-Est (capture à gauche)
                capR = DIR[2]; // Ouest (capture à droite)
            }
            else if (side == Side::Red) {
                // Sur le côté rouge, le pion blanc avance vers la droite
                fwd = DIR[3];  // Sud-Ouest
                capL = DIR[2]; // Ouest (capture à gauche)
                capR = DIR[4]; // Sud-Est (capture à droite)
            }
            else if (side == Side::Black) {
                // Sur le côté noir, le pion blanc avance vers la gauche
                fwd = DIR[5];  // Est
                capL = DIR[4]; // Sud-Est (capture à gauche)
                capR = DIR[0]; // Nord-Est (capture à droite)
            }
        }
        else if (couleur == ROUGE) {
            if (side == Side::Red) {
                // Sur le côté rouge, le pion rouge avance vers le haut
                fwd = DIR[3];  // Sud-Ouest
                capL = DIR[2]; // Ouest (capture à gauche)
                capR = DIR[4]; // Sud-Est (capture à droite)
            }
            else if (side == Side::Black) {
                // Sur le côté noir, le pion rouge avance vers la droite
                fwd = DIR[5];  // Est
                capL = DIR[4]; // Sud-Est (capture à gauche)
                capR = DIR[0]; // Nord-Est (capture à droite)
            }
            else if (side == Side::White) {
                // Sur le côté blanc, le pion rouge avance vers la gauche
                fwd = DIR[1];  // Nord-Ouest
                capL = DIR[0]; // Nord-Est (capture à gauche)
                capR = DIR[2]; // Ouest (capture à droite)
            }
        }
        else if (couleur == NOIR) {
            if (side == Side::Black) {
                // Sur le côté noir, le pion noir avance vers le haut
                fwd = DIR[5];  // Est
                capL = DIR[4]; // Sud-Est (capture à gauche)
                capR = DIR[0]; // Nord-Est (capture à droite)
            }
            else if (side == Side::White) {
                // Sur le côté blanc, le pion noir avance vers la droite
                fwd = DIR[1];  // Nord-Ouest
                capL = DIR[0]; // Nord-Est (capture à gauche)
                capR = DIR[2]; // Ouest (capture à droite)
            }
            else if (side == Side::Red) {
                // Sur le côté rouge, le pion noir avance vers la gauche
                fwd = DIR[3];  // Sud-Ouest
                capL = DIR[2]; // Ouest (capture à gauche)
                capR = DIR[4]; // Sud-Est (capture à droite)
            }
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