#include "Case.h"

Case::Case(sf::Vector2f pos, bool blanc) : position(pos), estBlanc(blanc), piece(nullptr)
{
    // Création de la forme
    forme = sf::RectangleShape(sf::Vector2f(TAILLE_CASE, TAILLE_CASE));
    forme.setPosition(sf::Vector2f(pos.x, pos.y));

    // Couleurs
    if (blanc)
    {
        forme.setFillColor(sf::Color(238, 238, 210));
    }
    else
    {
        forme.setFillColor(sf::Color(118, 150, 86));
    }

    // Contour et rotation
    forme.setOutlineThickness(1.f);
    forme.setOutlineColor(sf::Color::Black);
    forme.setOrigin(sf::Vector2f(TAILLE_CASE / 2.f, TAILLE_CASE / 2.f));
    forme.setRotation(sf::degrees(45.f));
}

Case::~Case() {}

void Case::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Dessiner uniquement la forme
    target.draw(forme, states);
}

bool Case::contientPoint(sf::Vector2f point) const
{
    auto bounds = forme.getGlobalBounds();
    // Modification de la méthode contains
    return bounds.contains(point);
}

void Case::surbrillance(bool actif)
{
    if (actif)
    {
        forme.setFillColor(sf::Color(247, 247, 105));
    }
    else
    {
        forme.setFillColor(estBlanc ? sf::Color(238, 238, 210) : sf::Color(118, 150, 86));
    }
}