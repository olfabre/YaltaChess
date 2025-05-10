#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <array>
#include <string>           // pour std::string utilisé dans toAlgebrique
#include "Couleur.h"        // pour enum Couleur

class Model;               // forward-déclaration de Model



using namespace sf;
using namespace std;

// Structure représentant une case sur la grille hexagonale en coordonnées cubiques
struct Cube { int x, y, z; };

// global namespace
inline bool operator==(const Cube &a, const Cube &b) {
         return a.x==b.x && a.y==b.y && a.z==b.z;
    }
struct CubeHash {
         size_t operator()(const Cube& c) const noexcept {
                 return std::hash<int>()(c.x)
                      ^ (std::hash<int>()(c.y)<<1)
                      ^ (std::hash<int>()(c.z)<<2);
             }
     };

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
    // Corrigé pour correspondre à la disposition réelle de l'échiquier Yalta
    inline string toAlgebrique(Vector2i g) {
        static const string files = "abcdefghijkl";
        char file;
        int rank;

        // Calcul de la notation de base (orientation BLANC) selon les zones de l'échiquier
        if (g.x < 4) {
            // Zone Red (haut-gauche)
            file = files[g.x];
            rank = g.y + 1;
        }
        else if (g.y < 4) {
            // Zone Black bas-droite (rangées inférieures)
            int offsetX = (g.x >= 5) ? 1 : 0;
            int fileIndex = g.x + (3 - g.y) - offsetX;
            file = files[fileIndex];
            rank = g.x - 3;
        }
        else if (g.y < 8) {
            // Zone Black centrale
            file = files[g.x];
            rank = 12 - g.y;
        }
        else {
            // Zone White (bas)
            file = files[g.x];
            rank = 12 - g.y;
        }
        if (g.y >= 8) {
            // inversion 180°
        }


        return string(1, file) + to_string(rank);
    }

    // 6 poinst cardiaux d’un hexagone en coords cubiques  (E, NE, NW, W, SW, SE)
    static constexpr array<Cube,6> DIR = {
            Cube{+1,-1, 0},   // 0 : Est
            Cube{+1, 0,-1},   // 1 : Nord-Est
            Cube{ 0,+1,-1},   // 2 : Nord-Ouest
            Cube{-1,+1, 0},   // 3 : Ouest
            Cube{-1, 0,+1},   // 4 : Sud-Ouest
            Cube{ 0,-1,+1}    // 5 : Sud-Est
    };

    inline bool interieurEchiquier(const Cube& c)
    {
        Vector2i g = cubeVersGrille(c);
        return g.x >= 0 && g.x < 12 && g.y >= 0 && g.y < 12;
    }



    inline vector<Cube> movesCavalier(const Cube pos,const Model& model,Couleur couleur) {
        vector<Cube> res{ {0, 0, 0} };
        return res;
    }

    inline vector<Cube> movesTour(const Cube pos,const Model& model,Couleur couleur)
    {

        vector<Cube> res{ {0, 0, 0} };
        return res;
    }

    inline vector<Cube> movesFou(const Cube pos,const Model& model,Couleur couleur)
    {
        vector<Cube> res{ {0, 0, 0} };
        return res;
    }


    inline vector<Cube> movesDame(const Cube pos,const Model& model,Couleur couleur)
    {
        vector<Cube> res{ {0, 0, 0} };
        return res;
    }




    inline vector<Cube> movesRoi(const Cube pos,const Model& model,Couleur couleur)
    {
        vector<Cube> res{ {0, 0, 0} };
        return res;
    }

    inline vector<Cube> movesPion(const Cube pos,const Model& model,Couleur couleur)
    {
        vector<Cube> res{ {0, 0, 0} };
        return res;
    }






}