#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <array>
#include "Model.h"    // pour Model et Couleur


using namespace sf;
using namespace std;

// Structure représentant une case sur la grille hexagonale en coordonnées cubiques
struct Cube { int x, y, z; };

namespace Hex {

    // Conversion d'une case en coordonnées "offset odd-r" (grille 2D) vers les coordonnées cubiques
    inline Cube grilleVersCube(const Vector2i &g) {
        int q = g.x - (g.y - (g.y & 1)) / 2;
        int r = g.y;
        int x = q;
        int z = r;
        int y = -x - z;
        return {x, y, z};
    }

    // Conversion inverse : d'une position cubique vers la grille 2D "offset odd-r"
    inline Vector2i cubeVersGrille(const Cube &c) {
        int q = c.x;
        int r = c.z;
        int col = q + (r - (r & 1)) / 2;
        return {col, r};
    }

    // helper pour convertir grid → « a1, b1, … l12 »
    inline string toAlgebrique(Vector2i g) {
            static const char* files = "abcdefghijkl";
            char file = files[g.x];
            int  rank = 12 - g.y;
            return string(1, file) + to_string(rank);
        }

    // 6 directions possibles pour une tour (axes principaux)
    static constexpr array<Cube,6> directionsTour = {{
    {+1, -1,  0}, {+1,  0, -1}, { 0, +1, -1},
    {-1, +1,  0}, {-1,  0, +1}, { 0, -1, +1}
    }};

// 6 directions possibles pour un fou (diagonales hex)
    static constexpr std::array<Cube,6> directionsFou = {{
    {directionsTour[0].x + directionsTour[1].x,
     directionsTour[0].y + directionsTour[1].y,
     directionsTour[0].z + directionsTour[1].z },


     {directionsTour[1].x + directionsTour[2].x,
      directionsTour[1].y + directionsTour[2].y,
      directionsTour[1].z + directionsTour[2].z },

     { directionsTour[2].x + directionsTour[3].x,
       directionsTour[2].y + directionsTour[3].y,
       directionsTour[2].z + directionsTour[3].z },

     { directionsTour[3].x + directionsTour[4].x,
       directionsTour[3].y + directionsTour[4].y,
       directionsTour[3].z + directionsTour[4].z },

     { directionsTour[4].x + directionsTour[5].x,
       directionsTour[4].y + directionsTour[5].y,
       directionsTour[4].z + directionsTour[5].z },

     { directionsTour[5].x + directionsTour[0].x,
       directionsTour[5].y + directionsTour[0].y,
       directionsTour[5].z + directionsTour[0].z }
     }};

    // 12 sauts possibles pour un cavalier en hex-grille
    inline vector<Cube> sautsCavalier() {
        vector<Cube> sauts;
        for (int i = 0; i < 6; ++i) {
            int v1 = (i + 1) % 6;
            int v2 = (i + 5) % 6;
            sauts.push_back({
            directionsTour[i].x*2 + directionsTour[v1].x,
            directionsTour[i].y*2 + directionsTour[v1].y,
            directionsTour[i].z*2 + directionsTour[v1].z
             });

            sauts.push_back({
            directionsTour[i].x*2 + directionsTour[v2].x,
            directionsTour[i].y*2 + directionsTour[v2].y,
            directionsTour[i].z*2 + directionsTour[v2].z
             });
        }
        return sauts;
    }


    // ----- Helpers pour tous els types de pièces -----

    inline vector<Vector2i> movesTour(
            const Vector2i& pos,
            const Model& model,
            Couleur couleur)
    {
        vector<Vector2i> res;
        Cube cur = grilleVersCube(pos);
        for (auto& d : directionsTour) {
            Cube nxt = cur;
            while (true) {
                nxt = { nxt.x + d.x, nxt.y + d.y, nxt.z + d.z };
                auto g = cubeVersGrille(nxt);
                if (auto c = model.getCaseAt(g)) {
                    if (!model.isOccupied(g)) {
                        res.push_back(g);
                    } else {
                        if (model.getPieceAt(g)->getCouleur() != couleur)
                            res.push_back(g);
                        break;
                    }
                } else break;
            }
        }
        return res;
    }

    inline vector<Vector2i> movesFou(
            const Vector2i& pos,
            const Model& model,
            Couleur couleur)
    {
        vector<Vector2i> res;
        Cube cur = grilleVersCube(pos);
        for (auto& d : directionsFou) {
            Cube nxt = cur;
            while (true) {
                nxt = { nxt.x + d.x, nxt.y + d.y, nxt.z + d.z };
                auto g = cubeVersGrille(nxt);
                if (auto c = model.getCaseAt(g)) {
                    if (!model.isOccupied(g)) {
                        res.push_back(g);
                    } else {
                        if (model.getPieceAt(g)->getCouleur() != couleur)
                            res.push_back(g);
                        break;
                    }
                } else break;
            }
        }
        return res;
    }

    inline vector<Vector2i> movesDame(
            const Vector2i& pos,
            const Model& model,
            Couleur couleur)
    {
        auto r = movesTour(pos, model, couleur);
        auto f = movesFou (pos, model, couleur);
        r.insert(r.end(), f.begin(), f.end());
        return r;
    }

    inline vector<Vector2i> movesCavalier(
            const Vector2i& pos,
            const Model& model,
            Couleur couleur)
    {
        vector<Vector2i> res;
        Cube cur = grilleVersCube(pos);
        static const auto& jumps = sautsCavalier();
        for (auto& j : jumps) {
            Cube nxt{ cur.x + j.x, cur.y + j.y, cur.z + j.z };
            auto g = cubeVersGrille(nxt);
            if (auto c = model.getCaseAt(g)) {
                if (!model.isOccupied(g) ||
                    model.getPieceAt(g)->getCouleur() != couleur)
                    res.push_back(g);
            }
        }
        return res;
    }

    inline vector<Vector2i> movesRoi(
            const Vector2i& pos,
            const Model& model,
            Couleur couleur)
    {
        vector<Vector2i> res;
        Cube cur = grilleVersCube(pos);
        for (auto& d : directionsTour) {
            Cube nxt{cur.x+d.x, cur.y+d.y, cur.z+d.z};
            auto g = cubeVersGrille(nxt);
            if (auto c = model.getCaseAt(g)) {
                if (!model.isOccupied(g) ||
                    model.getPieceAt(g)->getCouleur() != couleur)
                    res.push_back(g);
            }
        }
        for (auto& d : directionsFou) {
            Cube nxt{cur.x+d.x, cur.y+d.y, cur.z+d.z};
            auto g = cubeVersGrille(nxt);
            if (auto c = model.getCaseAt(g)) {
                if (!model.isOccupied(g) ||
                    model.getPieceAt(g)->getCouleur() != couleur)
                    res.push_back(g);
            }
        }
        return res;
    }

    // indice de la direction "avant" (dans directionsTour) pour chaque couleur
    // Couleur BLANC=0 -> axis 5  (grid (0,+1))
    //        NOIR =1 -> axis 1  (grid (0,-1))
    //        ROUGE=2 -> axis 0  (grid (+1,0))
    static constexpr int pawnDirIdx[3] = {
                5,  // BLANC
                1,  // NOIR
                0   // ROUGE
        };

    inline vector<Vector2i> movesPion(
            const Vector2i& pos,
            const Model& model,
            Couleur couleur)
    {
        vector<Vector2i> res;
        Cube cur = grilleVersCube(pos);

        // un pas "avant"
        Cube forward = directionsTour[pawnDirIdx[couleur]];
        Cube one = { cur.x+forward.x, cur.y+forward.y, cur.z+forward.z };
        auto g1 = cubeVersGrille(one);
        if (auto c = model.getCaseAt(g1))
            if (!model.isOccupied(g1))
                res.push_back(g1);

        // captures diagonales autour de "forward"
        for (auto& d : directionsFou) {
            int dot = d.x*forward.x + d.y*forward.y + d.z*forward.z;
            if (dot > 0) {
                Cube cap{cur.x+d.x, cur.y+d.y, cur.z+d.z};
                auto g2 = cubeVersGrille(cap);
                if (auto p2 = model.getPieceAt(g2))
                    if (p2->getCouleur() != couleur)
                        res.push_back(g2);
            }
        }
        return res;
    }






}