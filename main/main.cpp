#include <SFML/Graphics.hpp>
#include "Model.h"
#include "View.h"
#include "Controller.h"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1200u, 900u}), "YaltaChess");
    window.setFramerateLimit(144);

    Model model;
    View view(window, model);
    Controller controller(model, view);

    while (window.isOpen()) {
        controller.processEvents(window);
        model.update();
        view.render();
    }

    return 0;
}
