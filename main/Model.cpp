#include "Model.h"
#include <cmath>

Model::Model()
{
    initialiserEchiquier();
}

Model::~Model()
{
    for (auto &c : cases)
    {
        delete c;
    }
}

void Model::initialiserEchiquier()
{
    // Branche verticale (vers le bas)
    for (int i = 0; i < 8; i++)
    {
        for (int j = -3; j <= 3; j++)
        {
            float x = CENTRE_X + (j * TAILLE_CASE);
            float y = CENTRE_Y + (i * TAILLE_CASE);
            bool estBlanc = ((i + j) % 2 == 0);
            ajouterCase(x, y, estBlanc);
        }
    }

    // Branche gauche (vers le haut-gauche)
    for (int i = 1; i < 8; i++)
    {
        for (int j = -3; j <= 3; j++)
        {
            float x = CENTRE_X - (i * TAILLE_CASE * 0.866f) + (j * TAILLE_CASE * 0.5f);
            float y = CENTRE_Y - (i * TAILLE_CASE * 0.5f) + (j * TAILLE_CASE * 0.866f);
            bool estBlanc = ((i + j) % 2 == 0);
            ajouterCase(x, y, estBlanc);
        }
    }

    // Branche droite (vers le haut-droit)
    for (int i = 1; i < 8; i++)
    {
        for (int j = -3; j <= 3; j++)
        {
            float x = CENTRE_X + (i * TAILLE_CASE * 0.866f) + (j * TAILLE_CASE * 0.5f);
            float y = CENTRE_Y - (i * TAILLE_CASE * 0.5f) + (j * TAILLE_CASE * 0.866f);
            bool estBlanc = ((i + j) % 2 == 0);
            ajouterCase(x, y, estBlanc);
        }
    }
}

void Model::ajouterCase(float x, float y, bool estBlanc)
{
    cases.push_back(new Case(sf::Vector2f(x, y), estBlanc));
}