#include <iostream>
#include "Controller.h"
#include "View.h"
#include "HexagonalCubique.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>  // pour Mouse::Button
#include <algorithm>

using namespace sf;
using namespace std;

Controller::Controller(Model &m, YaltaChessView &v) : model(m), view(v) {}



// gestion des évènements côté interface
void Controller::handleEvent(const sf::Event& event)
{

    // Quand je passe la souris sur mes cases -> hover
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



    // Quand je clique sur une pièce
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
        if (!clickedCase) return; // quand je reclic

        // position logique
        //Vector2i grid = clickedCase->getGridPos();
        Cube cube = clickedCase->getCubePos();
        auto const& players = model.getPlayers();
        int cur = model.getCurrentPlayerIdx();

        // Quand je sélectionne la pièce
        if (!selectedPiece) {
            //Piece* p = model.getPieceAt(grid);
            Piece* p = model.getPieceAtCube(cube);
            if (p && p->getCouleur() == players[cur].color) {
                selectedPiece = p;
                legalMoves = p->getLegalMoves(model);
                auto cpos = p->getPositionCube();



                // ——— DEBUG : affiche les coorodonnées cube
                cout << "cube(" << cpos.x << "," << cpos.y << "," << cpos.z << ")";
                cout << "\n";



                // construire la liste de Case* à surligner (sélection + coups légaux)
                vector<Case*> highlights;
                // 1.a) la case où se trouvait la pièce sélectionnée
                highlights.push_back(clickedCase);
                // 1.b) les cases de destination légales
                for (const Cube& mv : legalMoves) {
                        for (Case* c : model.getCases()) {
                          if (c->getCubePos() == mv) {
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
            if (std::find(legalMoves.begin(), legalMoves.end(), cube) != legalMoves.end()) {
                model.movePieceCube(selectedPiece, cube);
            }
            // reset quoi qu’il arrive
            selectedPiece = nullptr;
            legalMoves.clear();
            view.clearHighlights();
            view.setHoveredCase(nullptr);
        }
    }
}