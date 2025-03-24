#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

enum Couleur { BLANC, NOIR, ROUGE };

// Classe abstraite représentant une pièce du jeu Yalta
class Piece {
protected:
    sf::Vector2i position; // Position sur l'échiquier
    Couleur couleur;       // Couleur de la pièce (joueur)

public:
    Piece(sf::Vector2i pos, Couleur coul);
    virtual ~Piece() = default;

    // Vérifie la validité du déplacement spécifique à chaque pièce
    virtual bool mouvementValide(sf::Vector2i nouvellePos) const = 0;

    // Dessine graphiquement la pièce (SFML)
    virtual void dessiner(sf::RenderWindow& window) const = 0;

    // Accesseurs
    sf::Vector2i getPosition() const;
    void setPosition(sf::Vector2i nouvellePos);
    Couleur getCouleur() const;
};

#endif