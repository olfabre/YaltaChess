#ifndef ROI_H
#define ROI_H

#include "Piece.h"
#include <vector>

using namespace sf;
using namespace std;

class Model;  // forward declaration


// Classe Roi héritant de Piece
class Roi : public Piece {
public:
    Roi(Vector2i pos, Couleur coul);
    bool mouvementValide(Vector2i nouvellePos) const override;
    void dessiner(RenderWindow& window) const override;

    // Renvoie tous les déplacements valides (1 case, captures incluses)
    std::vector<sf::Vector2i> getLegalMoves(const Model& model) const override;

    // Nom de la pièce pour chargement de texture, etc.
    std::string getTypeName() const override;
};

#endif
