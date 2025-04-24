#include <SFML/Graphics.hpp>
#include "Intro.h"
#include "ResourceManager.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode({1100u, 1100u}), "Yalta Chess");
    window.setFramerateLimit(60);

    // Initialisation de l'intro
    Intro intro(window);
    if (!intro.initialize()) {
        return -1;
    }

    // Boucle d'intro
    while (window.isOpen() && !intro.isComplete()) {
        optional<Event> event;
        while ((event = window.pollEvent())) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }
        intro.play();
    }

    // Chargement des textures de pièces (PNG)
    ResourceManager::loadAll();   // chargé une seule fois


    // Initialisation du jeu
    Model model;
    YaltaChessView YaltaChessView(window, model);
    Controller controller(model, YaltaChessView);

    // Boucle principale du jeu
    while (window.isOpen())
    {
        optional<Event> event;
        while ((event = window.pollEvent()))
        {
            if (event->is<Event::Closed>())
                window.close();
            else
                controller.handleEvent(*event);
        }
        YaltaChessView.draw();
    }

    // **IMPORTANT** : on vide le cache de textures
    ResourceManager::unloadAll();


    return 0;
}
