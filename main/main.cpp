#include "constants.h"
#include <SFML/Graphics.hpp>
#include "Intro.h"
#include "ResourceManager.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"
#include "HexagonalCubique.h"
#include <iostream>
#include "GameLogger.h"

using namespace sf;
using namespace std;

// Création du logger en tant que variable globale
GameLogger logger;

int main()
{
    //RenderWindow window(VideoMode({1100u, 1100u}), "Yalta Chess");
    RenderWindow window(VideoMode({static_cast<unsigned int>(WINDOW_WIDTH), static_cast<unsigned int>(WINDOW_HEIGHT)}), "Yalta Chess");

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

    // Ajout du logger au modèle
    model.addObserver(&logger);

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
