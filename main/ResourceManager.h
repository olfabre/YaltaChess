#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
using namespace sf;
using namespace std;

struct ResourceManager {
    static map<string,Texture> textures;

    static void loadAll() {
        // charge une fois pour toutes
        for (auto color : {"White","Black"}) {
            for (auto name : {"Pion","Tour","Fou","Cavalier","Dame","Roi"}) {
                string key = string(name) + "_" + color;
                Texture tex;
                if (!tex.loadFromFile(key + ".png"))
                    throw runtime_error("Impossible de charger " + key + ".png");
                textures[key] = move(tex);
            }
        }
    }

    // on libère explicitement avant la destruction de la fenêtre
    static void unloadAll() {
        textures.clear();
    }


    static const Texture& get(const string& key){
        return textures.at(key);
    }
};
