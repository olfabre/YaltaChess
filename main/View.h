#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include "Model.h"

class View {
private:
    sf::RenderWindow& m_window;
    Model& m_model;

public:
    View(sf::RenderWindow& window, Model& model);
    void render();
};

#endif
