#ifndef INTRO_H
#define INTRO_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class Intro {
private:
    sf::RenderWindow& window;
    sf::Texture introTexture;
    std::unique_ptr<sf::Sprite> introSprite;
    sf::Clock clock;
    bool isIntroComplete;

public:
    Intro(sf::RenderWindow& win);
    bool initialize();
    void play();
    bool isComplete() const { return isIntroComplete; }
};

#endif 