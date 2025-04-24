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
            auto fontPath = execPath / "PressStart2P-Regular.ttf";
            if (!coordFont.openFromFile(fontPath.string()))
                throw std::runtime_error("Impossible de charger PressStart2P-Regular.ttf");

            // Initialise tous les labels
            initBorderLabels();

}


void YaltaChessView::initBorderLabels()
{
    const float WIDTH    = 1000.f;
    const float OFFSET   = 50.f;
    const float OUTSET   = 25.f;      // distance label → bordure

    // Étiquettes par côté (dans l'ordre horaire)
    const std::vector<std::vector<std::string>> labels = {
            /* 0 (num.)   */ { "8","7","6","5","9","10","11","12" },
            /* 1 (lettres)*/ { "l","k","j","i","e","f","g","h"       },
            /* 2 (num.)   */ { "12","11","10","9","4","3","2","1"    },
            /* 3 (lettres)*/ { "h","g","f","e","d","c","b","a"       },
            /* 4 (num.)   */ { "1","2","3","4","5","6","7","8"       },
            /* 5 (lettres)*/ { "a","b","c","d","i","j","k","l"       }
    };

    // Centre de l’hexagone
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

        // Angle « nature » de l’arête → vertical
        float baseAngle = std::atan2(dir.y, dir.x) * 180.f / 3.14159265f + 90.f;

        for (int j = 0; j < count; ++j)
        {
            // position initiale au bord
            float t = (j + 0.5f) / float(count);
            sf::Vector2f pos = A + dir * t;

            // calcul du vecteur vers l’extérieur
            sf::Vector2f out = pos - mid;
            float len = std::sqrt(out.x*out.x + out.y*out.y);
            if (len > 0.f) {
                out /= len;
                pos += out * OUTSET;   // on décale de 20 pixels vers l’extérieur
            }

            // création du texte
            sf::Text txt(coordFont, sideLabels[j], 18);
            txt.setFillColor(sf::Color::Yellow);

            // centrer l’origine du texte
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
    window.clear(sf::Color::Black);

    // 1) dessiner les cases
    for (auto c : model.getCases())
        window.draw(*c);

    // 2) dessiner les labels décalés de 20px
    for (auto& txt : borderLabels)
        window.draw(txt);

    window.display();
}