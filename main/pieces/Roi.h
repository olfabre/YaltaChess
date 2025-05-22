#ifndef ROI_H
#define ROI_H
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include "Piece.h"
#include <vector>

using namespace sf;
using namespace std;

class Model;  // forward declaration


// Classe Roi héritant de Piece
class Roi : public Piece {
private:
    Model* modelPtr;

public:
    Roi(Cube pos, Couleur coul, Model* modelPtr);
    bool mouvementValide(Cube nouvellePos) const override;
    void dessiner(sf::RenderWindow& window) const override;


    vector<Cube> getLegalMoves(const Model& model) const override;

    string getTypeName() const override;

};

#endif
