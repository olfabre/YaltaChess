#include "ResourceManager.h"
using namespace sf;
using namespace std;

map<string,Texture> ResourceManager::textures;
map<string,Texture> ResourceManager::maskTextures;


void ResourceManager::loadAll() {
    for (auto color : {"White","Black"}) {
        for (auto name : {"Pion","Tour","Fou","Cavalier","Dame","Roi"}) {
            string key = string(name) + "_" + color;


            // 1) chargement de la texture originale
            Texture tex;
            if (!tex.loadFromFile(key + ".png"))
                throw runtime_error("Impossible de charger " + key + ".png");
            textures[key] = move(tex);

            // 2) génération du mask à partir du canal alpha
            Image img = textures[key].copyToImage();
            Image maskImg = img; // même taille
            Vector2u sz = img.getSize();
            for (unsigned y = 0; y < sz.y; ++y) {
                for (unsigned x = 0; x < sz.x; ++x) {
                    Color px = img.getPixel({x,y});
                    if (px.a > 0)
                        maskImg.setPixel({x,y}, Color(255,255,255, px.a));
                    else
                        maskImg.setPixel({x,y}, Color::Transparent);
                }
            }
            Texture maskTex;
            maskTex.loadFromImage(maskImg);
            maskTextures[key] = move(maskTex);
        }
    }
}