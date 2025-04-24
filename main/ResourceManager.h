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

    static const sf::Texture& get(const std::string& key){
        return textures.at(key);
    }


    static const sf::Texture& getMask(const std::string& key) {
        return maskTextures.at(key);
    }
};
