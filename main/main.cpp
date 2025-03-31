#include <SFML/Graphics.hpp>
#include "Model.h"
#include "View.h"
#include "Controller.h"

int main()
{
    // Fenêtre SFML 3
    sf::VideoMode mode;
    mode.size = {800u, 600u};
    sf::RenderWindow window(mode, "Yalta Chess");
    window.setFramerateLimit(60);

    // Composants MVC
    Model model;
    View view(window, model);
    Controller controller(model, view);

    // Boucle principale
    while (window.isOpen())
    {
        // Gestion correcte des événements SFML 3
        std::optional<sf::Event> event;
        while ((event = window.pollEvent()))
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else
            {
                controller.handleEvent(*event);
            }
        }

        view.draw();
    }

    return 0;
}
