#include "pieces/Pion.h"
#include <iostream>
#include "Controller.h"
#include "View.h"
#include "HexagonalCubique.h"
#include "CubeToLabel.h"
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
    // Gestion du survol de la souris
    if (event.is<sf::Event::MouseMoved>()) {
        auto const* mouseMoved = event.getIf<sf::Event::MouseMoved>();
        if (!mouseMoved) return;

        // Vérifie si c'est le tour du joueur humain
        auto const& players = model.getPlayers();
        if (!players[model.getCurrentPlayerIdx()].isHuman) {
            hoveredCase = nullptr;
            view.setHoveredCase(nullptr);
            return;
        }

        // Convertit la position de la souris en coordonnées monde
        Vector2i pixel{ mouseMoved->position.x, mouseMoved->position.y };
        Vector2f world = view.getWindow().mapPixelToCoords(pixel);

        // Cherche la case sous le curseur
        hoveredCase = nullptr;
        for (Case* c : model.getCases()) {
            if (c->contientPoint(world) && c->estOccupee()) {
                if (c->getPiece()->getCouleur() == players[model.getCurrentPlayerIdx()].color) {
                    hoveredCase = c;
                }
                break;
            }
        }
        view.setHoveredCase(hoveredCase);
    }

    // Gestion des clics
    auto const* mouseBtn = event.getIf<sf::Event::MouseButtonPressed>();
    if (!mouseBtn || mouseBtn->button != sf::Mouse::Button::Left) return;

    // Convertit la position du clic en coordonnées monde
    Vector2i pixel(mouseBtn->position.x, mouseBtn->position.y);
    Vector2f world = view.getWindow().mapPixelToCoords(pixel);

    // Cherche la case cliquée
    Case* clickedCase = nullptr;
    for (Case* c : model.getCases()) {
        if (c->contientPoint(world)) {
            clickedCase = c;
            break;
        }
    }
    if (!clickedCase) return;

    // Affiche les coordonnées cube et le label de la case cliquée
    Cube cubePos = clickedCase->getCubePos();
    std::cout << "Case cliquée - Coordonnées cube : ("
              << cubePos.x << ", " << cubePos.y << ", " << cubePos.z << ")"
              << " → Label : " << cubeToLabel(cubePos) << std::endl;

    // Récupère la couleur du joueur courant
    Couleur couleurCourante = model.getPlayers()[model.getCurrentPlayerIdx()].color;

    // Si on a déjà une pièce sélectionnée
    if (selectedCase) {
        // Si on clique sur la même case, on désélectionne
        if (clickedCase == selectedCase) {
            selectedCase = nullptr;
            view.setSelectedCase(nullptr);
            view.setHighlightedCases({});
            return;
        }

        // Vérifie si la case de destination est occupée par une pièce du joueur courant
        if (clickedCase->estOccupee() && clickedCase->getPiece()->getCouleur() == couleurCourante) {
            return; // On ne peut pas déplacer une pièce sur une case occupée par une pièce de même couleur
        }

        // Sinon on déplace la pièce vers la nouvelle case
        Piece* pieceToMove = selectedCase->getPiece();
        if (pieceToMove) {
            // On déplace la pièce
            model.movePieceCube(pieceToMove, clickedCase->getCubePos());

            // On met à jour le message d'événement
            string message = string("Le joueur ") +
                             (pieceToMove->getCouleur() == BLANC ? "Blanc" :
                              pieceToMove->getCouleur() == NOIR ? "Noir" : "Rouge") +
                             " a déplacé son " + pieceToMove->getTypeName() +
                             " de " + cubeToLabel(selectedCase->getCubePos()) +
                             " vers " + cubeToLabel(clickedCase->getCubePos());
            view.setEventMessage(message);

            // On réinitialise la sélection
            selectedCase = nullptr;
            view.setSelectedCase(nullptr);
            view.setHighlightedCases({});
        }
        return;
    }

    // Si on n'a pas de pièce sélectionnée, on vérifie si on clique sur une pièce du joueur courant
    if (clickedCase->estOccupee()) {
        Piece* clickedPiece = clickedCase->getPiece();
        if (clickedPiece && clickedPiece->getCouleur() == couleurCourante) {
            selectedCase = clickedCase;
            view.setSelectedCase(selectedCase);
            view.setHighlightedCases({selectedCase});
        }
    }
}

// fin dela selection des cases


