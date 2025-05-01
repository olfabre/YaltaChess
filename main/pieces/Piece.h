#ifndef PIECE_H
#define PIECE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../HexagonalCubique.h"   // pour struct Cube, operator==, CubeHash
#include "../Couleur.h"

using namespace sf;
using namespace std;

// Forward declarations
class Model;
class Case;

// Classe abstraite représentant une pièce du jeu Yalta
class Piece {
protected:
    Cube positionCube; // Position cubique sur l'échiquier
    Couleur couleur;   // Couleur de la pièce (joueur)



public:
    Piece(Cube pos, Couleur coul);
    virtual ~Piece() = default;

    // Vérifie la validité du déplacement spécifique à chaque pièce
    virtual bool mouvementValide(Vector2i nouvellePos) const = 0;

    // retourne toutes les destinations valides selon le model
    virtual vector<Cube> getLegalMoves(const Model&) const = 0;

    // Dessine graphiquement la pièce (SFML)
    virtual void dessiner(RenderWindow& window) const = 0;

    // Accesseurs
    Vector2i getPosition() const;
    void setPosition(Vector2i nouvellePos);
    Couleur getCouleur() const;

    virtual string getTypeName() const = 0;


    // Nousveaux accesseurs
    const Cube& getPositionCube() const { return positionCube; }
    void setPositionCube(const Cube& c) { positionCube = c; }

    // Si besoin de compatibilité IHM :
    Vector2i getPosition() const { return Hex::cubeVersGrille(positionCube); }
};

#endif