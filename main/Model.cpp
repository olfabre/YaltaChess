#include "Model.h"
#include "pieces/Roi.h"
#include "pieces/Dame.h"
#include "pieces/Fou.h"
#include "pieces/Tour.h"
#include "pieces/Cavalier.h"
#include "pieces/Pion.h"

Model::Model() {
    initialiserEchiquierYalta();
}

void Model::initialiserEchiquierYalta() {
    std::vector<std::vector<sf::Vector2f>> coordCases = {
            {{400,400},{450,380},{500,400},{450,420}},
            {{500,400},{550,380},{600,400},{550,420}},
            {{345.f,825.f},{395.f,805.f},{445.f,825.f},{395.f,845.f}},
            // ... tes autres coordonnées
    };

    sf::Color couleurClaire = sf::Color(255,206,158);
    sf::Color couleurFoncee = sf::Color(209,139,71);

    int compteurCases = 0;

    for (const auto& points : coordCases) {
        bool estCaseClaire = compteurCases % 2 == 0;
        sf::Color couleurCase = estCaseClaire ? couleurClaire : couleurFoncee;
        echiquier.emplace_back(points, couleurCase);
        compteurCases++;
    }

    auto roiBlanc = std::make_unique<Roi>(sf::Vector2i(0,0), BLANC);
    echiquier[0].setPiece(roiBlanc.get());
    pieces.push_back(std::move(roiBlanc));
}

void Model::update() {
    // Logique métier ici...
}

const std::vector<Case>& Model::getEchiquier() const {
    return echiquier;
}
