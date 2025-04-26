#ifndef PIECE_H
#define PIECE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace sf;
using namespace std;

enum Couleur { BLANC, NOIR, ROUGE };

class Model;

// Classe abstraite représentant une pièce du jeu Yalta
class Piece {
protected:
    Vector2i position; // Position sur l'échiquier
    Couleur couleur;       // Couleur de la pièce (joueur)

public:
    Piece(Vector2i pos, Couleur coul);
    virtual ~Piece() = default;

    // Vérifie la validité du déplacement spécifique à chaque pièce
    virtual bool mouvementValide(Vector2i nouvellePos) const = 0;


    // retourne toutes les destinations valides selon le model
    virtual vector<Vector2i> getLegalMoves(const Model& model) const = 0;

    // Dessine graphiquement la pièce (SFML)
    virtual void dessiner(RenderWindow& window) const = 0;

    // Accesseurs
    Vector2i getPosition() const;
    void setPosition(Vector2i nouvellePos);
    Couleur getCouleur() const;

    virtual string getTypeName() const = 0;
};

#endif