#include "View.h"

View::View(sf::RenderWindow& window) : m_window(window) {}

void View::render() {
    m_window.clear(sf::Color::Black);  // Couleur de fond par défaut
    // Dessine les éléments graphiques ici
    m_window.display();
}
