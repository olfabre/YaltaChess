#include "Case.h"

// Implémentation du constructeur
Case::Case(const sf::Vector2f &pos, bool blanc)
    : position(pos), estBlanc(blanc), piece(nullptr)
{
    forme.setSize({TAILLE_CASE, TAILLE_CASE});
    forme.setPosition(pos);
    forme.setFillColor(estBlanc ? sf::Color(235, 235, 208) : sf::Color(119, 148, 85));
}

// Implémentation du destructeur
Case::~Case()
{
    // rien à détruire ici (pour l'instant)
}

// Dessin de la case
void Case::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(forme, states);
}

// Vérifie si un point est dans la case
bool Case::contientPoint(const sf::Vector2f &point) const
{
    return forme.getGlobalBounds().contains(point);
}

// Activation de la surbrillance
void Case::surbrillance(bool actif)
{
    forme.setOutlineThickness(actif ? 3.f : 0.f);
    forme.setOutlineColor(sf::Color::Yellow);
}
