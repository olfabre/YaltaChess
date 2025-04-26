#ifndef PION_H
#define PION_H

#include "Piece.h"
#include <vector>

using namespace sf;
using namespace std;

class Model;  // forward declaration

// Classe Pion héritant de Piece
class Pion : public Piece {
public:
    Pion(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;

    // génération des coups légaux
    std::vector<sf::Vector2i> getLegalMoves(const Model& model) const override;

    // nom pour l’infrastructure
    std::string getTypeName() const override;
};

#endif
