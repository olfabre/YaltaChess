#ifndef CAVALIER_H
#define CAVALIER_H

#include "Piece.h"
#include <vector>


using namespace sf;
using namespace std;


class Model;  // forward declaration

// Classe Cavalier héritant de Piece
class Cavalier : public Piece {
public:
    Cavalier(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;

    // implémentation de la pure-virtual de Piece
    std::vector<sf::Vector2i> getLegalMoves(const Model& model) const override;

    std::string getTypeName() const override;

};

#endif
