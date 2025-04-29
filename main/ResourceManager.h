#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
using namespace sf;
using namespace std;

struct ResourceManager {
    static map<string,Texture> textures;
    static map<string, Texture> maskTextures;

    static void loadAll();

    // on libère explicitement avant la destruction de la fenêtre
    static void unloadAll() {
        textures.clear();
        maskTextures.clear();
    }

    // textures des masks générés (silhouette blanche)
    //static std::map<std::string, Texture> maskTextures;

    static const Texture& get(const string& key){
        return textures.at(key);
    }


    static const Texture& getMask(const string& key) {
        return maskTextures.at(key);
    }
};
