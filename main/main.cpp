#include <SFML/Graphics.hpp>
#include "Model.h"
#include "View.h"
#include "Controller.h"
using namespace sf;
using namespace std;
int main()
{
    RenderWindow window(VideoMode({1100u, 1100u}), "Yalta Chess");
    window.setFramerateLimit(60);

    Model model;
    View view(window, model);
    Controller controller(model, view);

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
        view.draw();
    }
    return 0;
}
