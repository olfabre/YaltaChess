#include "Controller.h"
#include "Model.h"
#include "View.h"

Controller::Controller(Model &m, View &v) : model(m), view(v) {}

void Controller::handleEvent(const sf::Event &event)
{
    // À implémenter selon les besoins
}