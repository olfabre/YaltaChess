#include "Intro.h"
#include <iostream>
#include <filesystem>

Intro::Intro(sf::RenderWindow& win) 
    : window(win), isIntroComplete(false) {
}

bool Intro::initialize() {
    // Obtenir le chemin du dossier d'exécution
    std::filesystem::path execPath = std::filesystem::current_path();
    std::filesystem::path imagePath = execPath / "intro.png";
    
    std::cout << "Tentative de chargement de l'image : " << imagePath << std::endl;

    // Charger l'image d'intro
    if (!introTexture.loadFromFile(imagePath.string())) {
        std::cerr << "Erreur : Impossible de charger l'image " << imagePath << std::endl;
        return false;
    }
    std::cout << "Image chargée avec succès. Taille : " 
              << introTexture.getSize().x << "x" << introTexture.getSize().y << std::endl;

    // Créer le sprite avec la texture
    introSprite = std::make_unique<sf::Sprite>(introTexture);
    
    // Calculer le facteur d'échelle pour adapter l'image à la fenêtre
    float scaleX = static_cast<float>(window.getSize().x) / introTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / introTexture.getSize().y;
    float scale = std::min(scaleX, scaleY); // Garder les proportions
    
    // Appliquer l'échelle
    introSprite->setScale(sf::Vector2f(scale, scale));
    
    // Centrer l'image
    float posX = (window.getSize().x - introTexture.getSize().x * scale) / 2.f;
    float posY = (window.getSize().y - introTexture.getSize().y * scale) / 2.f;
    introSprite->setPosition(sf::Vector2f(posX, posY));
    
    std::cout << "Image redimensionnée avec un facteur d'échelle de : " << scale << std::endl;
    std::cout << "Position de l'image : (" << posX << ", " << posY << ")" << std::endl;
    std::cout << "Taille de la fenêtre : " << window.getSize().x << "x" << window.getSize().y << std::endl;
    
    return true;
}

void Intro::play() {
    // Afficher l'image d'intro
    window.clear();
    window.draw(*introSprite);
    window.display();

    // Attendre 5 secondes
    if (clock.getElapsedTime().asSeconds() >= 5.0f) {
        isIntroComplete = true;
        std::cout << "Intro terminée" << std::endl;
    }
} 