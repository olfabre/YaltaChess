#include <iostream>
#include "Controller.h"
#include "View.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>  // pour Mouse::Button

using namespace sf;
using namespace std;

Controller::Controller(Model &m, YaltaChessView &v) : model(m), view(v) {}




void Controller::handleEvent(const sf::Event& event)
{

    // 1) Check MouseMoved event
    if (event.is<sf::Event::MouseMoved>()) {
        // Récupère l’événement MouseMoved
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
    //sf::Vector2i grid = clickedCase->getGridPos();
    // … autres événements (clic, touches…) …

    // 2) Check MouseButtonPressed event for selection / déplacement
    if (event.is<sf::Event::MouseButtonPressed>()) {
                auto const* mb = event.getIf<sf::Event::MouseButtonPressed>();
                if (!mb) return;

                        // on ne gère que le clic gauche
                                if (mb->button == Mouse::Button::Left) {
                        // coords pixel → monde
                                Vector2i pixel{ mb->position.x, mb->position.y };
                        Vector2f world = view.getWindow().mapPixelToCoords(pixel);
                                // trouver la case cliquée
                                        Case* clickedCase = nullptr;
                        for (Case* c : model.getCases()) {
                                if (c->contientPoint(world)) {
                                        clickedCase = c;
                                        break;
                                    }
                            }
                        if (!clickedCase)
                                return; // clic hors plateau

                                // récupérer la position logique (grille)
                                        sf::Vector2i grid = clickedCase->getGridPos();
                        // → ici : interroger model.getPieceAt(grid), sélectionner la pièce, etc.

                                    // ————— DEBUG : affiche dans la console
                                    std::cout << "DEBUG click gridPos = ("<< grid.x << "," << grid.y << ")" << std::endl;
                                    hoveredCase = clickedCase;
                                    view.setHoveredCase(clickedCase);

                                }
            }




}