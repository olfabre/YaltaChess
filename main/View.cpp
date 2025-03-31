#include "View.h"
#include "Model.h"
#include "cases/Case.h"

View::View(sf::RenderWindow &win, const Model &mod)
    : window(win), model(mod) {}

void View::draw()
{
    window.clear(sf::Color::Black);

    // Dessiner l'échiquier
    const auto &cases = model.getCases();
    for (const auto &c : cases)
    {
        if (c != nullptr)
        {
            window.draw(*c);
        }
    }

    window.display();
}