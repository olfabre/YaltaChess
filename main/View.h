#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

class View {
public:
    View(sf::RenderWindow& window);
    void render();
private:
    sf::RenderWindow& m_window;
};

#endif // VIEW_H
