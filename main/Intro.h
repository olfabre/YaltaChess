#ifndef INTRO_H
#define INTRO_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <memory>
using namespace sf;
using namespace std;

class Intro {
private:
    RenderWindow& window;
    Texture introTexture;
    unique_ptr<Sprite> introSprite;
    Clock clock;
    bool isIntroComplete;
    Font font;
    unique_ptr<Text> introText;
    Music music;

public:
    Intro(RenderWindow& win);
    bool initialize();
    void play();
    bool isComplete() const { return isIntroComplete; }
};

#endif 