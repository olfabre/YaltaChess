#include <SFML/Graphics.hpp>
#include "Model.h"
#include "View.h"
#include "Controller.h"

int main()
{
    // Création de la fenêtre avec les nouvelles spécifications SFML 3
    sf::VideoMode mode;
    mode.size = {800, 600}; // Définition de la taille en utilisant Vector2
    sf::RenderWindow window(mode, "Yalta Chess");
    window.setFramerateLimit(60);

    // Création des composants MVC
    Model model;
    View view(window, model);
    Controller controller(model, view);

    // Boucle principale
    while (window.isOpen())
    {
        // Gestion des événements avec SFML 3
        if (auto event = window.pollEvent())
        {
            if (event->type == sf::Event::Closed)
            {
                window.close();
            }
            // Ajout du traitement des événements par le controller
            controller.handleEvent(*event);
        }

        // Mise à jour et affichage
        view.draw();
    }

    return 0;
}