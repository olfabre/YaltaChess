#include "HexagonalCubique.h"
#include "Model.h"
#include <array>
#include <vector>
#include <iostream>
#include "CubeToLabel.h"

using std::array;
using std::vector;


// ───────────────── utilitaires bas niveau ───────────────────────────
inline Cube operator+(Cube a, Cube b){ return {a.x+b.x, a.y+b.y, a.z+b.z}; }

static const Cube DIRECTIONS[6] = {                    // les 6 directions cubiques
        {+1,-1,0},{+1,0,-1},{0,+1,-1},
        {-1,+1,0},{-1,0,+1},{0,-1,+1}
};
static int indexDirection(Cube v){                    // 0‥5 → pour les diagonales
    for(int i=0;i<6;++i) if(DIRECTIONS[i].x==v.x && DIRECTIONS[i].y==v.y && DIRECTIONS[i].z==v.z) return i;
    return -1;
}

// ───────────────── centre "réel" du plateau ─────────────────────────
static double CENTRE_X=0,CENTRE_Y=0,CENTRE_Z=0;   // centre géométrique (double)
static bool centreInitialise=false;

static void initialiserCentre(const Model& model)
{
    if (centreInitialise) return;
    long long somme_x=0, somme_y=0, somme_z=0; size_t nombre=0;
    for (const auto& c : model.getCases()){      // Model::getCases() existe déjà
        Cube q = c->getCubePos();
        somme_x+=q.x; somme_y+=q.y; somme_z+=q.z; ++nombre;
    }
    CENTRE_X = double(somme_x)/nombre; CENTRE_Y = double(somme_y)/nombre; CENTRE_Z = double(somme_z)/nombre;
    centreInitialise = true;
}
inline double distanceAuCentre(Cube c){
    double dx=c.x-CENTRE_X, dy=c.y-CENTRE_Y, dz=c.z-CENTRE_Z;
    return dx*dx + dy*dy + dz*dz;                // distance euclidienne²
}


namespace Hex {

    vector<Cube> mouvementsCavalier(const Cube position, const Model& model, Couleur couleur) {
        vector<Cube> resultat;
        
        // Le Cavalier se déplace en L : 2 cases dans une direction, puis 1 case perpendiculairement
        for (int i = 0; i < 6; i++) {
            // Direction principale (2 cases)
            Cube direction1 = DIRECTIONS[i];
            Cube positionIntermediaire = position + direction1 + direction1;
            
            // Directions perpendiculaires (1 case)
            Cube direction2 = DIRECTIONS[(i + 1) % 6];
            Cube direction3 = DIRECTIONS[(i + 5) % 6];
            
            // Vérifier les deux mouvements en L possibles
            for (const Cube& directionPerpendiculaire : {direction2, direction3}) {
                Cube destination = positionIntermediaire + directionPerpendiculaire;
                
                // Vérifier si on est toujours sur l'échiquier
                if (!model.getCaseAtCube(destination)) continue;
                
                // Vérifier si la case est occupée
                if (auto piece = model.getPieceAtCube(destination)) {
                    // Si la pièce est de couleur différente, on peut la capturer
                    if (piece->getCouleur() != couleur) {
                        resultat.push_back(destination);
                    }
                    continue;
                }
                
                // La case est vide, on peut y aller
                resultat.push_back(destination);
            }
        }
        
        return resultat;
    }

    vector<Cube> mouvementsTour(const Cube position, const Model& model, Couleur couleur) {
        vector<Cube> resultat;
        
        // La Tour se déplace en ligne droite dans les 6 directions hexagonales
        for (const Cube& direction : DIRECTIONS) {
            Cube positionActuelle = position;
            while (true) {
                positionActuelle = positionActuelle + direction;
                
                // Vérifier si on est toujours sur l'échiquier
                if (!model.getCaseAtCube(positionActuelle)) break;
                
                // Vérifier si la case est occupée
                if (auto piece = model.getPieceAtCube(positionActuelle)) {
                    // Si la pièce est de couleur différente, on peut la capturer
                    if (piece->getCouleur() != couleur) {
                        resultat.push_back(positionActuelle);
                    }
                    break; // On ne peut pas aller plus loin dans cette direction
                }
                
                // La case est vide, on peut y aller
                resultat.push_back(positionActuelle);
            }
        }
        
        return resultat;
    }

    vector<Cube> mouvementsFou(const Cube position, const Model& model, Couleur couleur) {
        vector<Cube> resultat;
        
        // Le Fou se déplace en diagonale dans les 6 directions hexagonales
        // Pour chaque direction, on crée une diagonale en combinant deux directions adjacentes
        for (int i = 0; i < 6; i++) {
            Cube direction1 = DIRECTIONS[i];
            Cube direction2 = DIRECTIONS[(i + 1) % 6];
            Cube diagonale = direction1 + direction2;
            
            Cube positionActuelle = position;
            while (true) {
                positionActuelle = positionActuelle + diagonale;
                
                // Vérifier si on est toujours sur l'échiquier
                if (!model.getCaseAtCube(positionActuelle)) break;
                
                // Vérifier si la case est occupée
                if (auto piece = model.getPieceAtCube(positionActuelle)) {
                    // Si la pièce est de couleur différente, on peut la capturer
                    if (piece->getCouleur() != couleur) {
                        resultat.push_back(positionActuelle);
                    }
                    break; // On ne peut pas aller plus loin dans cette direction
                }
                
                // La case est vide, on peut y aller
                resultat.push_back(positionActuelle);
            }
        }
        
        return resultat;
    }

    vector<Cube> mouvementsDame(const Cube position, const Model& model, Couleur couleur) {
        vector<Cube> resultat;
        
        // La Dame combine les mouvements de la Tour et du Fou
        vector<Cube> deplacementsTour = mouvementsTour(position, model, couleur);
        vector<Cube> deplacementsFou = mouvementsFou(position, model, couleur);
        
        resultat.insert(resultat.end(), deplacementsTour.begin(), deplacementsTour.end());
        resultat.insert(resultat.end(), deplacementsFou.begin(), deplacementsFou.end());
        
        return resultat;
    }

    vector<Cube> mouvementsRoi(const Cube position, const Model& model, Couleur couleur) {
        vector<Cube> resultat;
        
        // Le Roi se déplace d'une case dans toutes les directions
        for (const Cube& direction : DIRECTIONS) {
            Cube destination = position + direction;
            
            // Vérifier si on est toujours sur l'échiquier
            if (!model.getCaseAtCube(destination)) continue;
            
            // Vérifier si la case est occupée
            if (auto piece = model.getPieceAtCube(destination)) {
                // Si la pièce est de couleur différente, on peut la capturer
                if (piece->getCouleur() != couleur) {
                    resultat.push_back(destination);
                }
                continue;
            }
            
            // La case est vide, on peut y aller
            resultat.push_back(destination);
        }
        
        return resultat;
    }

    vector<Cube> mouvementsPion(const Cube position, const Model& model, Couleur couleur) {
        vector<Cube> mouvements;
        for (const auto& c : model.getCases()) {      // Utilisation de const auto& pour les unique_ptr
            if (c->estOccupee() && c->getPiece()->getCouleur() == couleur) {
                // ... existing code ...
            }
        }
        return mouvements;
    }

}