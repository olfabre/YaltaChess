#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include "Model.h"

class View {
public:
    View(sf::RenderWindow& window, Model& model);
    void render();
private:
    sf::RenderWindow& m_window;
    Model& m_model;
};

#endif
