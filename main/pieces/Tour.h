#ifndef TOUR_H
#define TOUR_H
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include "Piece.h"
#include <vector>

using namespace sf;
using namespace std;

class Model;  // forward declaration

// Classe Tour héritant de Piece
class Tour : public Piece {
public:
    Tour(Cube pos, Couleur coul);
    bool mouvementValide(Cube nouvellePos) const override;
    void dessiner(sf::RenderWindow& window) const override;


    vector<Cube> getLegalMoves(const Model& model) const override;

    string getTypeName() const override;

};

#endif