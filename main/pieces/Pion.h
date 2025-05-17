#ifndef PION_H
#define PION_H
#include "../HexagonalCubique.h" // Inclure pour utiliser les fonctions de Hex
#include "Piece.h"
#include <vector>

using namespace sf;
using namespace std;

class Model;  // forward declaration

// Classe Pion héritant de Piece
class Pion : public Piece {
public:
    //Pion(Cube pos, Couleur coul);
    Pion(Cube pos, Couleur coul, Model* modelPtr);
    bool mouvementValide(Cube nouvellePos) const override;
    void dessiner(sf::RenderWindow& window) const override;


    vector<Cube> getLegalMoves(const Model& model) const override;

    string getTypeName() const override;

private:
    Model* modelPtr;    // <— on stocke le pointeur vers le modèle


};

#endif
