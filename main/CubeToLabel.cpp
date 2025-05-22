#include <iostream>
#include <map>
#include <string>
#include "Model.h"

// Comparateur pour Cube
struct CubeCompare {
    bool operator()(const Cube& a, const Cube& b) const {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    }
};

// Fonction de conversion cube → label
std::string cubeToLabel(const Cube& c) {
    // Table de correspondance directe entre coordonnées cube et labels
    static const std::map<Cube, std::string, CubeCompare> cubeToLabelMap = {
        {{4, -4, 0}, "A1"}, {{4, -5, 1}, "A2"}, {{3, -5, 2}, "A3"}, {{3, -6, 3}, "A4"},
        {{3, -3, 0}, "A5"}, {{2, -2, 0}, "A6"}, {{1, -1, 0}, "A7"}, {{0, 0, 0}, "A8"},
        {{5, -5, 0}, "B1"}, {{5, -6, 1}, "B2"}, {{4, -6, 2}, "B3"}, {{4, -7, 3}, "B4"},
        {{3, -4, 1}, "B5"}, {{2, -3, 1}, "B6"}, {{1, -2, 1}, "B7"}, {{0, -1, 1}, "B8"},
        {{6, -6, 0}, "C1"}, {{6, -7, 1}, "C2"}, {{5, -7, 2}, "C3"}, {{5, -8, 3}, "C4"},
        {{2, -4, 2}, "C5"}, {{1, -3, 2}, "C6"}, {{0, -2, 2}, "C7"}, {{-1, -1, 2}, "C8"},
        {{7, -7, 0}, "D1"}, {{7, -8, 1}, "D2"}, {{6, -8, 2}, "D3"}, {{6, -9, 3}, "D4"},
        {{2, -5, 3}, "D5"}, {{1, -4, 3}, "D6"}, {{0, -3, 3}, "D7"}, {{-1, -2, 3}, "D8"},
        {{-1, -10, 11}, "E1"}, {{0, -11, 11}, "E2"}, {{1, -12, 11}, "E3"}, {{2, -13, 11}, "E4"},
        {{6, -17, 11}, "E9"}, {{6, -16, 10}, "E10"}, {{7, -16, 9}, "E11"}, {{7, -15, 8}, "E12"},
        {{-1, -9, 10}, "F1"}, {{0, -10, 10}, "F2"}, {{1, -11, 10}, "F3"}, {{2, -12, 10}, "F4"},
        {{5, -16, 11}, "F9"}, {{5, -15, 10}, "F10"}, {{6, -15, 9}, "F11"}, {{6, -14, 8}, "F12"},
        {{0, -9, 9}, "G1"}, {{1, -10, 9}, "G2"}, {{2, -11, 9}, "G3"}, {{3, -12, 9}, "G4"},
        {{4, -15, 11}, "G9"}, {{4, -14, 10}, "G10"}, {{5, -14, 9}, "G11"}, {{5, -13, 8}, "G12"},
        {{0, -8, 8}, "H1"}, {{1, -9, 8}, "H2"}, {{2, -10, 8}, "H3"}, {{3, -11, 8}, "H4"},
        {{3, -14, 11}, "H9"}, {{3, -13, 10}, "H10"}, {{4, -13, 9}, "H11"}, {{4, -12, 8}, "H12"},
        {{0, -7, 7}, "I5"}, {{0, -6, 6}, "I6"}, {{1, -6, 5}, "I7"}, {{1, -5, 4}, "I8"},
        {{8, -15, 7}, "I9"}, {{7, -14, 7}, "I10"}, {{6, -13, 7}, "I11"}, {{5, -12, 7}, "I12"},
        {{-1, -6, 7}, "J5"}, {{-1, -5, 6}, "J6"}, {{0, -5, 5}, "J7"}, {{0, -4, 4}, "J8"},
        {{8, -14, 6}, "J9"}, {{7, -13, 6}, "J10"}, {{6, -12, 6}, "J11"}, {{5, -11, 6}, "J12"},
        {{-2, -5, 7}, "K5"}, {{-2, -4, 6}, "K6"}, {{-1, -4, 5}, "K7"}, {{-1, -3, 4}, "K8"},
        {{9, -14, 5}, "K9"}, {{8, -13, 5}, "K10"}, {{7, -12, 5}, "K11"}, {{6, -11, 5}, "K12"},
        {{-3, -4, 7}, "L5"}, {{-3, -3, 6}, "L6"}, {{-2, -3, 5}, "L7"}, {{-2, -2, 4}, "L8"},
        {{9, -13, 4}, "L9"}, {{8, -12, 4}, "L10"}, {{7, -11, 4}, "L11"}, {{6, -10, 4}, "L12"}
    };

    auto it = cubeToLabelMap.find(c);
    if (it != cubeToLabelMap.end()) {
        return it->second;
    }
    
    // Si les coordonnées ne sont pas trouvées, retourner une chaîne vide
    return "";
}

// Fonction pour tester la conversion sur toutes les cases
void testCubeToLabel(const Model& model) {
    std::cout << "Test de conversion des coordonnées cube en labels :\n";
    for (const auto& c : model.getCases()) {
        Cube cubePos = c->getCubePos();
        std::cout << "(" << cubePos.x << "," << cubePos.y << "," << cubePos.z << ")"
                  << " → " << cubeToLabel(cubePos) << "\n";
    }
} 