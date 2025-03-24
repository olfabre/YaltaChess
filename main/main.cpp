#include <SFML/Graphics.hpp>
#include "Model.h"
#include "View.h"
#include "Controller.h"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "YaltaChess");
    window.setFramerateLimit(144);

    Model model;
    View view(window);
    Controller controller(model, view);

    while (window.isOpen()) {
        controller.processEvents(window);  // Gestion des événements
        model.update();                    // Mise à jour des données
        view.render();                     // Rendu graphique
    }

    return 0;
}
