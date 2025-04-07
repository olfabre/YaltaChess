#include "View.h"
#include "Model.h"
#include "cases/Case.h"
using namespace sf;
using namespace std;

YaltaChessView::YaltaChessView(RenderWindow &win, const Model &mod)
        : window(win), model(mod) {}

void YaltaChessView::draw()
{
    window.clear(Color::Black);

    for (auto c : model.getCases())
        window.draw(*c);

    window.display();
}
