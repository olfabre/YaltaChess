#include "pieces/Pion.h"
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






    auto const* mouseBtn = event.getIf<sf::Event::MouseButtonPressed>();
    if (!mouseBtn || mouseBtn->button != sf::Mouse::Button::Left)
        return;

    sf::Vector2i pixel(mouseBtn->position.x, mouseBtn->position.y);
    sf::Vector2f world = view.getWindow().mapPixelToCoords(pixel);

    // On cherche la case cliquée (appartenant au joueur courant)
    Case* clickedCase = nullptr;


    // On récupère la couleur du joueur courant
    Couleur couleurCourante = model.getPlayers()[model.getCurrentPlayerIdx()].color;


    for (Case* c : model.getCases()) {
        // On veut uniquement une case avec une pièce du joueur courant
        if (c->contientPoint(world) && c->estOccupee() && c->getPiece()->getCouleur() == couleurCourante) {
            clickedCase = c;
            break;
        }
    }


    if (!clickedCase) return;

    // --- Sélection / désélection ---
    if (selectedCase == clickedCase) {
        selectedCase = nullptr;
        legalMoveCases.clear();
        view.setSelectedCase(nullptr);
        view.setHighlightedCases({});
        return;
    }
    selectedCase = clickedCase;
    legalMoveCases.clear();



// Surligner uniquement si c'est un pion
    if (selectedCase->getPiece() && selectedCase->getPiece()->getTypeName() == "Pion") {
        auto* pion = dynamic_cast<Pion*>(selectedCase->getPiece());
        if (pion) {
            auto legalMoves = pion->getLegalMoves(model);
            for (const auto& cube : legalMoves) {
                Case* targetCase = model.getCaseAtCube(cube);
                if (targetCase && targetCase != selectedCase)
                    legalMoveCases.push_back(targetCase);
            }
        }
    }
// On passe toutes les cases à surligner à la vue : coups légaux + sélection
    std::vector<Case*> highlightCases = legalMoveCases;
    if (selectedCase) {
        highlightCases.push_back(selectedCase); // toujours ajouter la sélection
    }

    view.setSelectedCase(selectedCase);
    view.setHighlightedCases(highlightCases);
    view.setHighlightedCases(highlightCases);


    // === AJOUT : affichage infos de la case sélectionnée + type de pièce ===
    if (selectedCase && selectedCase->getPiece()) {
        auto* piece = selectedCase->getPiece();
        Cube cubeCase = selectedCase->getCubePos();
        Cube cubePiece = piece->getPositionCube();
        std::cout << "[Controller] Case : cube("
                  << cubeCase.x << "," << cubeCase.y << "," << cubeCase.z << ")"
                  << " | Piece: " << piece->getTypeName()
                  << " | posPiece: cube("
                  << cubePiece.x << "," << cubePiece.y << "," << cubePiece.z << ")"
                  << " | couleur=" << piece->getCouleur()
                  << std::endl;
    }


}

// fin dela selection des cases


