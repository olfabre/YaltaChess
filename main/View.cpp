#include "View.h"
#include <cmath>
#include <stdexcept>
#include "Model.h"
#include "cases/Case.h"
#include "ResourceManager.h"
#include <array>
using namespace sf;
using namespace std;
namespace {
    void drawOutlinedSprite(RenderTarget& target,
                            const Sprite& sprite,
                            Color outlineColor,
                            float thickness)
    {
        // dessine 8 copies décalées pour simuler un liseré
        array<Vector2f,8> offsets = {
                Vector2f(-thickness, -thickness),
                Vector2f(-thickness,  0.f),
                Vector2f(-thickness,  thickness),
                Vector2f( 0.f,       -thickness),
                Vector2f( 0.f,        thickness),
                Vector2f( thickness, -thickness),
                Vector2f( thickness,  0.f),
                Vector2f( thickness,  thickness)
        };
        for (auto& off : offsets) {
            Sprite outline = sprite;
            outline.setColor(outlineColor);
            outline.move(off);
            target.draw(outline);
        }
        target.draw(sprite);
    }
}


YaltaChessView::YaltaChessView(RenderWindow &win, const Model &mod)
        : window(win), model(mod)
        {
            // Charge la police (unique, tirée de ton dossier de ressources)
            // Charge la police (SFML 3)
            // Charger la police Google font
            // SFML 3 : charger la police
            // Charge la police SFML 3 depuis le répertoire de l'exécutable
            auto execPath = filesystem::current_path();
            auto fontPath = execPath / "Roboto-Regular.ttf";
            if (!coordFont.openFromFile(fontPath.string()))
                throw runtime_error("Impossible de charger Roboto-Regular.ttf");

            // Initialise tous les labels
            initBorderLabels();

}


void YaltaChessView::initBorderLabels()
{
    const float WIDTH    = 1000.f;
    const float OFFSET   = 50.f;
    const float OUTSET   = 25.f;  // distance label → bordure

    // Étiquettes par côté (horaire)
    const vector<vector<string>> labels = {
            /* 0 (num.)   */ { "8","7","6","5","9","10","11","12" },
            /* 1 (lettres)*/ { "l","k","j","i","e","f","g","h"       },
            /* 2 (num.)   */ { "12","11","10","9","4","3","2","1"    },
            /* 3 (lettres)*/ { "h","g","f","e","d","c","b","a"       },
            /* 4 (num.)   */ { "1","2","3","4","5","6","7","8"       },
            /* 5 (lettres)*/ { "a","b","c","d","i","j","k","l"       }
    };

    Vector2f mid(WIDTH/2.f + OFFSET, WIDTH/2.f + OFFSET);
    float size   = WIDTH/2.f;
    float height = sqrt(size*size - (size/2.f)*(size/2.f));

    // Sommets du hexagone (flat-top)
    vector<Vector2f> v123 = {
            {-size*0.5f, -height}, { size*0.5f, -height},
            { size,        0      }, { size*0.5f,  height},
            {-size*0.5f,  height}, {-size,       0      }
    };

    for (int k = 0; k < 6; ++k)
    {
        const auto& sideLabels = labels[k];
        int count = int(sideLabels.size());

        // Extrémités de l’arête k
        Vector2f A   = mid + v123[k];
        Vector2f B   = mid + v123[(k+1)%6];
        Vector2f dir = B - A;

        // Angle « naturel » de l’arête
        float baseAngle = atan2(dir.y, dir.x) * 180.f / 3.14159265f + 90.f;

        for (int j = 0; j < count; ++j)
        {
            // position sur l’arête
            float t   = (j + 0.5f) / float(count);
            Vector2f pos = A + dir * t;

            // décale vers l’extérieur de OUTSET px
            Vector2f out = pos - mid;
            float len = sqrt(out.x*out.x + out.y*out.y);
            if (len > 0.f) {
                out /= len;
                pos += out * OUTSET;
            }

            // création du texte
            Text txt(coordFont, sideLabels[j], 18);
            txt.setFillColor(Color::Black);

            // centre l’origine du texte
            auto b = txt.getLocalBounds();
            txt.setOrigin(
                    Vector2f{
                            b.position.x + b.size.x/2.f,
                            b.position.y + b.size.y/2.f
                    }
            );

            // override angles pour côtés lettres
            float angleDeg = baseAngle;
            if      (k == 1) angleDeg = 240.f;
            else if (k == 3) angleDeg =   0.f;
            else if (k == 5) angleDeg = 120.f;

            txt.setRotation(degrees(angleDeg));
            txt.setPosition(pos);
            borderLabels.push_back(txt);
        }
    }
}



// 1) Ce helper instantie les mêmes v123, vabc, intervals que Model
Vector2f YaltaChessView::gridToPixel(const Vector2i& g) const {
    const float W = 1000.f, O = 50.f;
    // Mid, size, v123, vabc, intervals… recopier ici
    // puis la boucle for zone=0..5 identique :
    //   si interval[zone] contient (g.x,g.y), calculer :
    //     float rx1 = (g.x%4)/4.f, ry1 = (g.y%4)/4.f;
    //     float mid_r_x = (rx1 + (g.x%4+1)/4.f)/2, idem mid_r_y
    //     Vector2f s1 = v123[z]*0.5f, s2 = v123[(z+2)%6]*0.5f;
    //     Vector2f corner = mid + v123[(z+4)%6];
    //     Vector2f U1 = vabc[(z+1)%6]*ry1 - s1*ry1 + s2;
    //     Vector2f midU = vabc[(z+1)%6]*mid_r_y - s1*mid_r_y + s2;
    //     return corner + s1*mid_r_y + midU*mid_r_x;
    // (identique à ce qu’on fait dans Model pour construire les cases).
    // …
    // le return « bouche-trou » pour supprimer le warning :
    return { 100.f, 100.f };
}



void YaltaChessView::draw()
{
    const float BOARD_SIZE   = 1000.f;
    const float OFFSET       = 50.f;  // ta translation originale
    const float BORDER_WIDTH = 50.f;  // épaisseur de la bordure blanche

    // Calcul du centre
    Vector2f mid(OFFSET + BOARD_SIZE/2.f,
                     OFFSET + BOARD_SIZE/2.f);

    // Les 6 sommets du hexagone (flat-top) autour du board
    float size   = BOARD_SIZE/2.f;
    float side   = size/2.f;
    float height = sqrt(size*size - side*side);
    array<Vector2f,6> v = {
            Vector2f(-size*0.5f, -height),
            Vector2f( size*0.5f, -height),
            Vector2f( size,        0      ),
            Vector2f( size*0.5f,  height),
            Vector2f(-size*0.5f,  height),
            Vector2f(-size,       0      )
    };

    // 1) Fond noir
    window.clear(Color::Black);

    // 2) Bordure blanche : hexagone plus grand de BORDER_WIDTH vers l’extérieur
    ConvexShape whiteBorder;
    whiteBorder.setPointCount(6);
    for (int i = 0; i < 6; ++i)
    {
        // direction unitaire
        Vector2f dir = v[i];
        float len = sqrt(dir.x*dir.x + dir.y*dir.y);
        if (len != 0) dir /= len;

        // point : sommet board + déplacement
        Vector2f pt = mid + v[i] + dir * BORDER_WIDTH;
        whiteBorder.setPoint(i, pt);
    }
    whiteBorder.setFillColor(Color::White);
    window.draw(whiteBorder);

    // 3) Contour noir autour de la bordure blanche
    ConvexShape outline;
    outline.setPointCount(6);
    for (int i = 0; i < 6; ++i)
        outline.setPoint(i, whiteBorder.getPoint(i));
    outline.setFillColor(Color::Transparent);
    outline.setOutlineColor(Color::Black);
    outline.setOutlineThickness(2.f);
    window.draw(outline);

    // 4) Dessiner l’échiquier (cases)
    for (auto c : model.getCases())
        window.draw(*c);

    // 5) Dessiner les labels
    for (auto& txt : borderLabels)
        window.draw(txt);

    // piece
    for (auto p : model.getPieces())
    {
        // 2.a) choisir la bonne texture
        string key =
                p->getTypeName() + "_" +
                (p->getCouleur()==BLANC ? "White"
                                        : p->getCouleur()==NOIR  ? "Black"
                                                                 : "White");
        auto& tex = ResourceManager::get(key);
        Sprite spr(tex);
        // centre du sprite
        auto ts = ResourceManager::get(key).getSize();
        //spr.setOrigin(ts.x/2.f, ts.y/2.f);
        spr.setOrigin({ ts.x/2.f, ts.y/2.f });

        // 2.b) positionner
        Vector2f pos = gridToPixel(p->getPosition());
        spr.setPosition(pos);

        // 2.c) si rouge, sprite.setColor({195,83,51});
        if (p->getCouleur()==ROUGE)
            spr.setColor({195,83,51});
        // 2.d) ajouter le liseré (voir la fonction drawOutlinedSprite plus haut)

        drawOutlinedSprite(window, spr,
                           (p->getCouleur()==BLANC? Color::Black : Color{246,243,232}),
                           1.5f);
    }



    window.display();
}