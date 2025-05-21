#ifndef CUBETOLABEL_H
#define CUBETOLABEL_H

#include <string>
#include "Model.h"

// Convertit les coordonnées cube en label (ex: (4,-4,0) -> "A1")
std::string cubeToLabel(const Cube& c);

// Teste la conversion sur toutes les cases du modèle
void testCubeToLabel(const Model& model);

#endif // CUBETOLABEL_H 