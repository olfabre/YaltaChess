#include "View.h"

void View::draw()
{
    window.clear(sf::Color(49, 46, 43)); // Fond sombre

    // Dessiner toutes les cases
    for (const auto &c : model.getCases())
    {
        window.draw(*c);
    }

    window.display();
}