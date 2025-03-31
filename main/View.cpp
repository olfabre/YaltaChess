#include "View.h"
#include "Model.h"
#include "cases/Case.h"

View::View(sf::RenderWindow &win, const Model &mod)
        : window(win), model(mod) {}

void View::draw()
{
    window.clear(sf::Color::Black);

    for (auto c : model.getCases())
        window.draw(*c);

    window.display();
}
