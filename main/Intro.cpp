#include "Intro.h"
#include <iostream>
#include <filesystem>
using namespace sf;
using namespace std;

Intro::Intro(RenderWindow& win)
    : window(win),
    isIntroComplete(false) {
}

bool Intro::initialize() {






    // Obtenir le chemin du dossier d'exécution
    filesystem::path execPath = filesystem::current_path();
    filesystem::path imagePath = execPath / "intro.png";
    
    cout << "Tentative de chargement de l'image : " << imagePath << endl;

    // Charger l'image d'intro
    if (!introTexture.loadFromFile(imagePath.string())) {
        cerr << "Erreur : Impossible de charger l'image " << imagePath << endl;
        return false;
    }
    cout << "Image chargée avec succès. Taille : "
              << introTexture.getSize().x << "x" << introTexture.getSize().y << endl;

    // Créer le sprite avec la texture
    introSprite = make_unique<Sprite>(introTexture);
    
    // Calculer le facteur d'échelle pour adapter l'image à la fenêtre
    float scaleX = static_cast<float>(window.getSize().x) / introTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / introTexture.getSize().y;
    float scale = min(scaleX, scaleY); // Garder les proportions
    
    // Appliquer l'échelle
    introSprite->setScale(Vector2f(scale, scale));
    
    // Centrer l'image
    float posX = (window.getSize().x - introTexture.getSize().x * scale) / 2.f;
    float posY = (window.getSize().y - introTexture.getSize().y * scale) / 2.f;
    introSprite->setPosition(Vector2f(posX, posY));
    
    cout << "Image redimensionnée avec un facteur d'échelle de : " << scale << endl;
    cout << "Position de l'image : (" << posX << ", " << posY << ")" << endl;
    cout << "Taille de la fenêtre : " << window.getSize().x << "x" << window.getSize().y << endl;


    // Charger la police Google font
    filesystem::path fontPath = execPath / "PressStart2P-Regular.ttf";
    if (!font.openFromFile(fontPath)) { // CORRIGE loadFromFile -> openFromFile
        cerr << "Erreur : Impossible de charger la police " << fontPath << endl;
        return false;
    }

    introText = make_unique<Text>(font, "2025 | Olivier Fabre", 20);
    introText->setFillColor(Color::Yellow);

     // Centrer le texte
    FloatRect textRect = introText->getLocalBounds();
    introText->setOrigin(textRect.position + textRect.size / 2.0f);
    //introText->setPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y - 100));
    introText->setPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 350)); // texte centré


    // Charger la musique
    filesystem::path musicPath = filesystem::current_path() / "retro.ogg";  // Mets ton fichier ici

    if (!music.openFromFile(musicPath)) {
        cerr << "Erreur : Impossible de charger la musique " << musicPath << endl;
        return false;
    }

    music.setLooping(true);  // Activer la boucle
    music.play();         // Lancer la musique



    return true;
}

void Intro::play() {
    // Afficher l'image d'intro
    window.clear();
    window.draw(*introSprite);
    window.draw(*introText);
    window.display();

    // Attendre 7 secondes

    // en période de dev, je mets moins longtemps
    //float tpAttente = 7.0f; // prod
    float tpAttente = 7.0f; // dev
    if (clock.getElapsedTime().asSeconds() >= tpAttente) {
        isIntroComplete = true;
        cout << "Intro terminée" << endl;
    }
} 