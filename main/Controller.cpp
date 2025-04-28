#include <iostream>
#include "Controller.h"
#include "View.h"
#include "HexagonalCubique.h"
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



    // --- Clic pour sélection / déplacement ---
    if (event.is<sf::Event::MouseButtonPressed>()) {
        auto const* mb = event.getIf<sf::Event::MouseButtonPressed>();
        if (!mb || mb->button != Mouse::Button::Left) return;

        // pixel → monde → case
        Vector2i pixel{ mb->position.x, mb->position.y };
        Vector2f world = view.getWindow().mapPixelToCoords(pixel);
        Case* clickedCase = nullptr;
        for (Case* c : model.getCases()) {
            if (c->contientPoint(world)) {
                clickedCase = c;
                break;
            }
        }
        if (!clickedCase) return;

        // position logique
        Vector2i grid = clickedCase->getGridPos();
        auto const& players = model.getPlayers();
        int cur = model.getCurrentPlayerIdx();

        // 1) Sélection de la pièce
        if (!selectedPiece) {
            Piece* p = model.getPieceAt(grid);
            if (p && p->getCouleur() == players[cur].color) {
                selectedPiece = p;
                legalMoves = p->getLegalMoves(model);

                       // ——— DEBUG : affiche les coups légaux


                cout
                        << p->getTypeName()
                        << " en " << Hex::toAlgebrique(grid)
                        << " -> legalMoves:";
                for (auto& mv : legalMoves)
                    cout << " " <<  Hex::toAlgebrique(mv);
                cout << "\n";



                // construire la liste de Case* à surligner (sélection + coups légaux)
                vector<Case*> highlights;
                // 1.a) la case où se trouvait la pièce sélectionnée
                highlights.push_back(clickedCase);
                // 1.b) les cases de destination légales
                for (auto& mv : legalMoves) {
                    for (Case* c : model.getCases()) {
                        if (c->getGridPos() == mv) {
                            highlights.push_back(c);
                            break;
                        }
                    }
                }
                view.setHighlightedCases(highlights);
            }
        }

            // 2) Deuxième clic : déplacement ou annulation
        else {
            if (find(legalMoves.begin(), legalMoves.end(), grid) != legalMoves.end()) {
                model.movePiece(selectedPiece, grid);
            }
            // reset quoi qu’il arrive
            selectedPiece = nullptr;
            legalMoves.clear();
            view.clearHighlights();
            view.setHoveredCase(nullptr);
        }
    }
}