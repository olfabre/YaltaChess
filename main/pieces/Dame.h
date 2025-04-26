#ifndef DAME_H
#define DAME_H

#include "Piece.h"
#include <vector>


using namespace sf;
using namespace std;


class Model;  // forward declaration

// Classe Dame héritant de Piece
class Dame : public Piece {
public:
    Dame(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;


    // implémentation de la pure-virtual de Piece
    std::vector<sf::Vector2i> getLegalMoves(const Model& model) const override;

    // nom pour l’infrastructure (chargement texture, etc.)
    std::string getTypeName() const override;
};

#endif
