#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include "Model.h"
#include "View.h"

class Controller {
public:
    Controller(Model& model, View& view);
    void processEvents(sf::RenderWindow& window);
private:
    Model& m_model;
    View& m_view;
};

#endif // CONTROLLER_H
