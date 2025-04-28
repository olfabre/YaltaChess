#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "cases/Case.h"
#include "Piece.h"

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
    int currentPlayerIdx;  // index dans players du joueur dont c'est le tour
    vector<Case *> cases;
    vector<Piece*> pieces; // mes instances de Pion/ Tour/ Fou / Cavalier / Dame / Roi.
    static constexpr float WIDTH = 800.f;
    static constexpr float HEIGHT = 800.f;

    //void ajouterCase(const vector<Vector2f>& points, bool estBlanc);
    /*void ajouterCase(const std::vector<sf::Vector2f>& points,
                        bool estBlanc,
                        sf::Vector2i gridPos);
                        */
    void ajouterCase(const std::vector<sf::Vector2f>& points,
                        bool estBlanc,
                        sf::Vector2i gridPos,
                        Side side);
    void initialiserJoueurs();

    // Supprime p de `pieces` et libère la mémoire
    void removePiece(Piece* p);

public:
    Model();
    ~Model();
    const vector<PlayerInfo>& getPlayers() const { return players; }

    // Retourne la Case* correspondant à une position grille (ou nullptr)
    Case* getCaseAt(const sf::Vector2i& pos) const;

    int getCurrentPlayerIdx() const { return currentPlayerIdx; }
    void initialiserEchiquier();
    const vector<Case *> &getCases() const { return cases; }
    const auto& getPieces() const { return pieces; }
    // Renvoie la pièce à la position grille donnée (ou nullptr)
    Piece* getPieceAt(sf::Vector2i pos) const;
    // Déplace p vers dest, gère capture et passe au joueur suivant
    void movePiece(Piece* p, sf::Vector2i dest);
    // Vrai si une pièce occupe la case
    bool isOccupied(sf::Vector2i pos) const;


};

#endif
