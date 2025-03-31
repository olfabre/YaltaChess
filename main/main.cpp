#include <SFML/Graphics.hpp>
#include "Model.h"
#include "View.h"
#include "Controller.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1100u, 1100u}), "Yalta Chess");
    window.setFramerateLimit(60);

    Model model;
    View view(window, model);
    Controller controller(model, view);

    while (window.isOpen())
    {
        std::optional<sf::Event> event;
        while ((event = window.pollEvent()))
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else
                controller.handleEvent(*event);
        }
        view.draw();
    }
    return 0;
}
