#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "HexagonalCubique.h"    // pour Cube, CubeHash
#include "cases/Case.h"
#include <unordered_map>
#include "pieces/Piece.h"

using namespace sf;
using namespace std;

class Piece;

// Modèle de données pour un joueur
struct PlayerInfo {
    string name;    // "Humain" ou prénom aléatoire
    Couleur    color;    // BLANC, ROUGE ou NOIR
    bool       isHuman;  // true pour vous, false pour IA
};

class Model
{
private:
    // … vos membres existants …
    vector<PlayerInfo> players;
    int currentPlayerIdx = 0;  // index dans players du joueur dont c'est le tour
    vector<Case *> cases;
    vector<Piece*> pieces; // mes instances de Pion/ Tour/ Fou / Cavalier / Dame / Roi.
    static constexpr float WIDTH = 800.f;
    static constexpr float HEIGHT = 800.f;
    Cube lastMove;  // Stocke le dernier mouvement effectué

    //void ajouterCase(const vector<Vector2f>& points, bool estBlanc);
    /*void ajouterCase(const std::vector<sf::Vector2f>& points,
                        bool estBlanc,
                        sf::Vector2i gridPos);
                        */
    void ajouterCase(const vector<Vector2f>& pts, bool estBlanc, const Cube& cubePos, Side side);

    // accès O(1) à la case par cube
    std::unordered_map<Cube, Case*, CubeHash> caseMap;

    void initialiserEchiquier();
    void initialiserPieces();
    void initialiserJoueurs();

    // Supprime p de `pieces` et libère la mémoire
    void removePiece(Piece* p);

public:
    Model();
    ~Model();
    void realignerPieces();
    const vector<PlayerInfo>& getPlayers() const { return players; }
    Case* getCaseAtCube(const Cube& c) const;
    void deplacerPiece(Piece* piece, const Cube& destination);

    // Retourne la Case* correspondant à une position grille (ou nullptr)
    //Case* getCaseAt(const sf::Vector2i& pos) const;

    int getCurrentPlayerIdx() const { return currentPlayerIdx; }

    const vector<Case *> &getCases() const { return cases; }
    const auto& getPieces() const { return pieces; }
    // Renvoie la pièce à la position grille donnée (ou nullptr)

    Piece* getPieceAtCube(const Cube&) const;
    // Déplace p vers dest, gère capture et passe au joueur suivant

    void movePieceCube(Piece* p, const Cube& dest);
    // Vrai si une pièce occupe la case
    bool isOccupied(sf::Vector2i pos) const;
    
    // Retourne le dernier mouvement effectué
    Cube getLastMove() const { return lastMove; }
    // Met à jour le dernier mouvement
    void setLastMove(const Cube& move) { lastMove = move; }

    void movePiece(Piece* piece, const Cube& destination);
    void nextPlayer();
};

#endif
