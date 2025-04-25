#include "Controller.h"
#include "View.h"
#include <SFML/Window/Event.hpp>

using namespace sf;
using namespace std;

Controller::Controller(Model &m, YaltaChessView &v) : model(m), view(v) {}




void Controller::handleEvent(const sf::Event& event)
{

    // 1) Check for a MouseMoved event:
    if (event.is<sf::Event::MouseMoved>()) {
        // 2) Get the MouseMoved data safely
        auto const* mouseMoved = event.getIf<sf::Event::MouseMoved>();
        if (!mouseMoved)
            return;

        // 3) Pull out your players vector before using it
        auto const& players = model.getPlayers();

        // Only proceed if it's the human’s turn
        if (!players[model.getCurrentPlayerIdx()].isHuman) {
            hoveredCase = nullptr;
            view.setHoveredCase(nullptr);
            return;
        }

        // 4) Use the `position` member, not `.x`/`.y` on the old union
        Vector2i pixel{ mouseMoved->position.x,
                        mouseMoved->position.y };
        Vector2f world = view.getWindow().mapPixelToCoords(pixel);

        // on cherche la *case* sous le curseur
                hoveredCase = nullptr;
               for (Case* c : model.getCases()) {
                        if (c->contientPoint(world) && c->estOccupee()) {
                                if (c->getPiece()->getCouleur() == players[model.getCurrentPlayerIdx()].color)
                                        hoveredCase = c;
                                break;
                            }
                    }
                view.setHoveredCase(hoveredCase);
    }

    // … autres événements (clic, touches…) …
}