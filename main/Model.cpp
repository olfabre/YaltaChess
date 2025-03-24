#include "Model.h"
#include "pieces/Roi.h"
// inclure ici les autres pièces nécessaires (Dame, Fou, etc.)

Model::Model() {
    // Initialisation des cases de l'échiquier (12x8 = 96 cases)
    for (int x = 0; x < 12; ++x) {
        std::vector<Case> ligne;
        for (int y = 0; y < 8; ++y) {
            ligne.emplace_back(sf::Vector2i(x, y));
        }
        echiquier.push_back(std::move(ligne));
    }

    // Exemple : placer un Roi Blanc
    auto roiBlanc = std::make_unique<Roi>(sf::Vector2i(4, 0), BLANC);
    getCase(sf::Vector2i(4, 0)).setPiece(roiBlanc.get());
    pieces.push_back(std::move(roiBlanc));

    // Ajouter d'autres pièces ici...
}

Case& Model::getCase(sf::Vector2i pos) {
    return echiquier[pos.x][pos.y];
}

const std::vector<std::vector<Case>>& Model::getEchiquier() const {
    return echiquier;
}

void Model::update() {
    // Logique métier (déplacements, règles du jeu, etc.)
}
