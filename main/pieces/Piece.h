#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

enum Couleur { BLANC, NOIR, ROUGE };

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

    // Dessine graphiquement la pièce (SFML)
    virtual void dessiner(RenderWindow& window) const = 0;

    // Accesseurs
    Vector2i getPosition() const;
    void setPosition(Vector2i nouvellePos);
    Couleur getCouleur() const;
};

#endif