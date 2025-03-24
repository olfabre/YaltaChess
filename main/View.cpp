#include "View.h"

View::View(sf::RenderWindow& window, Model& model)
        : m_window(window), m_model(model) {}

void View::render() {
    m_window.clear(sf::Color(40, 32, 40));

    for(const auto& caseEchiquier : m_model.getEchiquier()) {
        caseEchiquier.dessiner(m_window);
    }

    m_window.display();
}
