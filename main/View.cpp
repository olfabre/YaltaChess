#include "View.h"

View::View(sf::RenderWindow& window, Model& model)
        : m_window(window), m_model(model) {}

void View::render() {
    m_window.clear();

    // Dessiner les cases
    for (const auto& ligne : m_model.getEchiquier()) {
        for (const auto& caseEchiquier : ligne) {
            caseEchiquier.dessiner(m_window);

            // Dessiner la pièce si présente
            if (caseEchiquier.estOccupee()) {
                caseEchiquier.getPiece()->dessiner(m_window);
            }
        }
    }

    m_window.display();
}
