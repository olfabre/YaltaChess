#include "Controller.h"

Controller::Controller(Model& model, View& view) : m_model(model), m_view(view) {}

void Controller::processEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}
