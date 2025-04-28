#include <SFML/Graphics.hpp>
#include "Intro.h"
#include "ResourceManager.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"
#include "HexagonalCubique.h"
#include <iostream>

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

    // ─── DÉBUT DU DEBUG ROUND-TRIP ─────────────────────────────
    for (Case* casePtr : model.getCases()) {
        sf::Vector2i g = casePtr->getGridPos();
        Cube cu = Hex::grilleVersCube(g);
        Vector2i back = Hex::cubeVersGrille(cu);
        if (back != g) {
            cout << "Erreur conversion: grid("
                      << g.x << "," << g.y << ") -> cube("
                      << cu.x << "," << cu.y << "," << cu.z
                      << ") -> back(" << back.x << "," << back.y
                      << ")\n";
        }
    }
    // ─── FIN DU DEBUG ────────────────────────────────────────────



    YaltaChessView YaltaChessView(window, model);
    Controller controller(model, YaltaChessView);

    // ─── TEST DES VOISINS D’UNE CASE ─────────────────────────────
    {
        auto g0 = model.getCases()[0]->getGridPos();
        Cube   c0 = Hex::grilleVersCube(g0);
        cout << "Voisins de (" << g0.x << "," << g0.y << ") :\n";
        for (auto& d : Hex::directionsTour) {
            Cube  n  = { c0.x+d.x, c0.y+d.y, c0.z+d.z };
            auto gv = Hex::cubeVersGrille(n);
            cout << "  dir("<<d.x<<","<<d.y<<","<<d.z<<") -> ("
                 << gv.x << "," << gv.y << ")\n";
        }
    }
    // ─── FIN DU TEST ────────────────────────────────────────────


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
