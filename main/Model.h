#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Piece.h"
#include "cases/Case.h"
using namespace sf;
using namespace std;

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

    void ajouterCase(const vector<Vector2f>& points, bool estBlanc);
    void initialiserJoueurs();

public:
    Model();
    ~Model();
    const vector<PlayerInfo>& getPlayers() const { return players; }
    int getCurrentPlayerIdx() const { return currentPlayerIdx; }
    void initialiserEchiquier();
    const vector<Case *> &getCases() const { return cases; }
    const auto& getPieces() const { return pieces; }
};

#endif
