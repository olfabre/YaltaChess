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
    }  // je passe la souris au dessus de mes pieces






    if (event.is<sf::Event::MouseButtonPressed>()) {
        auto const* mouseBtn = event.getIf<sf::Event::MouseButtonPressed>();
        if (!mouseBtn || mouseBtn->button != sf::Mouse::Button::Left)
            return;

        sf::Vector2i pixel(mouseBtn->position.x, mouseBtn->position.y);
        sf::Vector2f world = view.getWindow().mapPixelToCoords(pixel);

        // On récupère la couleur du joueur qui doit jouer
        auto const& players = model.getPlayers();
        Couleur couleurCourante = players[model.getCurrentPlayerIdx()].color;

        Case* clickedCase = nullptr;
        for (Case* c : model.getCases()) {
            // On vérifie : la case contient un point ET une pièce du joueur courant
            if (c->contientPoint(world) && c->estOccupee() && c->getPiece()->getCouleur() == couleurCourante) {
                clickedCase = c;
                break;
            }
        }

        if (!clickedCase) return;

        // Sélection / désélection logique classique
        if (selectedCase == clickedCase) {
            selectedCase = nullptr;
        } else {
            selectedCase = clickedCase;
        }

        std::vector<Case*> toHighlight;
        if (selectedCase)
            toHighlight.push_back(selectedCase);
        view.setHighlightedCases(toHighlight);

        // affichage infos de la case sélectionnée
        if (selectedCase) {
            const Cube& cube = selectedCase->getCubePos();
            int side = selectedCase->getSide();

            // Ici, on utilise le side comme "couleur" (0, 1, 2)
            int couleur = selectedCase->getPiece()->getCouleur();
            std::string typePiece = "Aucune";

            typePiece = selectedCase->getPiece()->getTypeName();
            std::cout << "Case sélectionnée : "
                      << "cube(" << cube.x << "," << cube.y << "," << cube.z << ") "
                      << "couleur=" << couleur
                      << " side=" << side
                    << " type=" << typePiece
                      << std::endl;
        }
        // === fin affcichage

    }
    // fin dela selection des cases





}