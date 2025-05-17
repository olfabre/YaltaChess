#include <iostream>
#include "Controller.h"
#include "View.h"
#include "HexagonalCubique.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>  // pour Mouse::Button
#include <algorithm>
#include <cmath>

using namespace sf;
using namespace std;

sf::Vector2f rotateAroundCenter2(const sf::Vector2f& point, const sf::Vector2f& center, float angleRad) {
    float dx = point.x - center.x;
    float dy = point.y - center.y;
    float cosA = std::cos(angleRad);
    float sinA = std::sin(angleRad);
    return sf::Vector2f{
            center.x + dx * cosA - dy * sinA,
            center.y + dx * sinA + dy * cosA
    };
}

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
        const float W = 1000.f;
        const float O = 50.f;
        sf::Vector2f mid(W/2.f + O, W/2.f + O);
        const float angle = -M_PI / 3; // INVERSE de ton affichage (+60° -> -60°)
        world = rotateAroundCenter2(world, mid, angle);

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