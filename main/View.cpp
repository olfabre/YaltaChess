#include "View.h"
#include <cmath>
#include <stdexcept>
#include "Model.h"
#include "cases/Case.h"
using namespace sf;
using namespace std;

YaltaChessView::YaltaChessView(RenderWindow &win, const Model &mod)
        : window(win), model(mod)
        {
            // Charge la police (unique, tirée de ton dossier de ressources)
            // Charge la police (SFML 3)
            // Charger la police Google font
            // SFML 3 : charger la police
            // Charge la police SFML 3 depuis le répertoire de l'exécutable
            auto execPath = std::filesystem::current_path();
            auto fontPath = execPath / "Roboto-Regular.ttf";
            if (!coordFont.openFromFile(fontPath.string()))
                throw std::runtime_error("Impossible de charger Roboto-Regular.ttf");

            // Initialise tous les labels
            initBorderLabels();

}


void YaltaChessView::initBorderLabels()
{
    const float WIDTH    = 1000.f;
    const float OFFSET   = 50.f;
    const float OUTSET   = 25.f;  // distance label → bordure

    // Étiquettes par côté (horaire)
    const std::vector<std::vector<std::string>> labels = {
            /* 0 (num.)   */ { "8","7","6","5","9","10","11","12" },
            /* 1 (lettres)*/ { "l","k","j","i","e","f","g","h"       },
            /* 2 (num.)   */ { "12","11","10","9","4","3","2","1"    },
            /* 3 (lettres)*/ { "h","g","f","e","d","c","b","a"       },
            /* 4 (num.)   */ { "1","2","3","4","5","6","7","8"       },
            /* 5 (lettres)*/ { "a","b","c","d","i","j","k","l"       }
    };

    sf::Vector2f mid(WIDTH/2.f + OFFSET, WIDTH/2.f + OFFSET);
    float size   = WIDTH/2.f;
    float height = std::sqrt(size*size - (size/2.f)*(size/2.f));

    // Sommets du hexagone (flat-top)
    std::vector<sf::Vector2f> v123 = {
            {-size*0.5f, -height}, { size*0.5f, -height},
            { size,        0      }, { size*0.5f,  height},
            {-size*0.5f,  height}, {-size,       0      }
    };

    for (int k = 0; k < 6; ++k)
    {
        const auto& sideLabels = labels[k];
        int count = int(sideLabels.size());

        // Extrémités de l’arête k
        sf::Vector2f A   = mid + v123[k];
        sf::Vector2f B   = mid + v123[(k+1)%6];
        sf::Vector2f dir = B - A;

        // Angle « naturel » de l’arête
        float baseAngle = std::atan2(dir.y, dir.x) * 180.f / 3.14159265f + 90.f;

        for (int j = 0; j < count; ++j)
        {
            // position sur l’arête
            float t   = (j + 0.5f) / float(count);
            sf::Vector2f pos = A + dir * t;

            // décale vers l’extérieur de OUTSET px
            sf::Vector2f out = pos - mid;
            float len = std::sqrt(out.x*out.x + out.y*out.y);
            if (len > 0.f) {
                out /= len;
                pos += out * OUTSET;
            }

            // création du texte
            sf::Text txt(coordFont, sideLabels[j], 18);
            txt.setFillColor(sf::Color::Black);

            // centre l’origine du texte
            auto b = txt.getLocalBounds();
            txt.setOrigin(
                    sf::Vector2f{
                            b.position.x + b.size.x/2.f,
                            b.position.y + b.size.y/2.f
                    }
            );

            // override angles pour côtés lettres
            float angleDeg = baseAngle;
            if      (k == 1) angleDeg = 240.f;
            else if (k == 3) angleDeg =   0.f;
            else if (k == 5) angleDeg = 120.f;

            txt.setRotation(sf::degrees(angleDeg));
            txt.setPosition(pos);
            borderLabels.push_back(txt);
        }
    }
}

void YaltaChessView::draw()
{
    const float BOARD_SIZE   = 1000.f;
    const float OFFSET       = 50.f;  // ta translation originale
    const float BORDER_WIDTH = 50.f;  // épaisseur de la bordure blanche

    // Calcul du centre
    sf::Vector2f mid(OFFSET + BOARD_SIZE/2.f,
                     OFFSET + BOARD_SIZE/2.f);

    // Les 6 sommets du hexagone (flat-top) autour du board
    float size   = BOARD_SIZE/2.f;
    float side   = size/2.f;
    float height = std::sqrt(size*size - side*side);
    std::array<sf::Vector2f,6> v = {
            sf::Vector2f(-size*0.5f, -height),
            sf::Vector2f( size*0.5f, -height),
            sf::Vector2f( size,        0      ),
            sf::Vector2f( size*0.5f,  height),
            sf::Vector2f(-size*0.5f,  height),
            sf::Vector2f(-size,       0      )
    };

    // 1) Fond noir
    window.clear(sf::Color::Black);

    // 2) Bordure blanche : hexagone plus grand de BORDER_WIDTH vers l’extérieur
    sf::ConvexShape whiteBorder;
    whiteBorder.setPointCount(6);
    for (int i = 0; i < 6; ++i)
    {
        // direction unitaire
        sf::Vector2f dir = v[i];
        float len = std::sqrt(dir.x*dir.x + dir.y*dir.y);
        if (len != 0) dir /= len;

        // point : sommet board + déplacement
        sf::Vector2f pt = mid + v[i] + dir * BORDER_WIDTH;
        whiteBorder.setPoint(i, pt);
    }
    whiteBorder.setFillColor(sf::Color::White);
    window.draw(whiteBorder);

    // 3) Contour noir autour de la bordure blanche
    sf::ConvexShape outline;
    outline.setPointCount(6);
    for (int i = 0; i < 6; ++i)
        outline.setPoint(i, whiteBorder.getPoint(i));
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::Black);
    outline.setOutlineThickness(2.f);
    window.draw(outline);

    // 4) Dessiner l’échiquier (cases)
    for (auto c : model.getCases())
        window.draw(*c);

    // 5) Dessiner les labels
    for (auto& txt : borderLabels)
        window.draw(txt);

    window.display();
}